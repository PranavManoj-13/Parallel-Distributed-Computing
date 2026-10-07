#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 500000000  // total data points

// ==================== Sensor Data Generation ====================
void generate_sensor_data(float *data, float base, float scale, float freq) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        data[i] = base + scale * sinf(i * freq);
    }
}

// ==================== CPU Fusion Function ====================
void fuse_cpu(float *lidar, float *radar, float *camera, float *fused) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        fused[i] = 0.4f * lidar[i] + 0.35f * radar[i] + 0.25f * camera[i];
        fused[i] += 0.5f * sinf(fused[i] * 0.01f);
    }
}

// ==================== Simulated GPU Fusion Function ====================
void fuse_gpu_simulated(float *lidar, float *radar, float *camera, float *fused) {
    // Simulate GPU by parallelizing with fine-grained loop scheduling
    #pragma omp parallel for schedule(dynamic, 256)
    for (int i = 0; i < N; i++) {
        fused[i] = 0.4f * lidar[i] + 0.35f * radar[i] + 0.25f * camera[i];
        fused[i] += 0.5f * sinf(fused[i] * 0.01f);
    }
}

// ==================== MAIN FUNCTION ====================
int main() {
    static float *lidar, *radar, *camera, *fused;
    lidar = (float*)malloc(N * sizeof(float));
    radar = (float*)malloc(N * sizeof(float));
    camera = (float*)malloc(N * sizeof(float));
    fused = (float*)malloc(N * sizeof(float));

    printf("\n=== AUTONOMOUS VEHICLE SENSOR FUSION (CPU vs GPU Simulation) ===\n");
    printf("Total sensor points: %d\n", N);

    // --- Data Initialization ---
    double t0 = omp_get_wtime();
    generate_sensor_data(lidar, 50.0f, 5.0f, 0.001f);
    generate_sensor_data(radar, 60.0f, 3.0f, 0.002f);
    generate_sensor_data(camera, 100.0f, 10.0f, 0.0005f);
    double t1 = omp_get_wtime();
    printf("Sensor data generated in %.3f sec\n\n", t1 - t0);

    printf("Threads\tCPU_Time(s)\tCPU_Spd\tEff(%%)\tGPU_Time(s)\tGPU_Spd\tEff(%%)\tCPU->GPU_Spd\n");
    printf("-----------------------------------------------------------------------------------\n");

   double baseline_cpu = 0.0, baseline_gpu = 0.0;

    // --- Scalability Test ---
    for (int p = 1; p <= 16; p *= 2) {
        omp_set_num_threads(p);

        // CPU Fusion
        double start_cpu = omp_get_wtime();
        fuse_cpu(lidar, radar, camera, fused);
        double end_cpu = omp_get_wtime();
        double cpu_time = end_cpu - start_cpu;

   if (p == 1) baseline_cpu = cpu_time;
        double cpu_speedup = baseline_cpu / cpu_time;
        double cpu_efficiency = (cpu_speedup / p) * 100.0;

        // GPU Simulation Fusion
        double start_gpu = omp_get_wtime();
        fuse_gpu_simulated(lidar, radar, camera, fused);
        double end_gpu = omp_get_wtime();
        double gpu_time = end_gpu - start_gpu;
       if (p == 1) baseline_gpu = gpu_time;
        double gpu_speedup = baseline_gpu / gpu_time;
        double gpu_efficiency = (gpu_speedup / p) * 100.0;

        // --- Speedup between CPU and GPU ---
        double cpu_to_gpu_speedup = cpu_time / gpu_time;

        printf("%2d\t%.3f\t\t%.2f\t%.2f\t%.3f\t\t%.2f\t%.2f\t%.2f\n",
               p, cpu_time, cpu_speedup, cpu_efficiency,
               gpu_time, gpu_speedup, gpu_efficiency, cpu_to_gpu_speedup);
    }

    // Print sample fused data
    printf("\nSample fused distances: ");
    for (int i = 0; i < 8; i++) printf("%.2f ", fused[i]);
    printf("\n");

    free(lidar);
    free(radar);
    free(camera);
    free(fused);
    return 0;
}