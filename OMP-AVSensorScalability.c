#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 1000000

void generateLIDARData(float *lidar) {
    #pragma omp parallel for schedule(static)
    for(int i = 0; i < N; i++) {
        lidar[i] = 50.0f + 5.0f * sinf(i * 0.001f);
    }
}

void generateRadarData(float *radar) {
    #pragma omp parallel for schedule(static)
    for(int i=0;i<N;i++) {
        radar[i] = 60.0f + 3.0f * cosf(i * 0.002f);
    }
}

void generateCameraData(float *camera) {
    #pragma omp parallel for schedule(static)
    for(int i=0;i<N;i++) {
        camera[i] = 70.0f + 2.0f * sinf(i * 0.003f);
    }
}

void fuseSensors(float *lidar, float *radar, float *camera, float *fused) {
    #pragma omp parallel for schedule(static)
    for(int i=0;i<N;i++) {
        fused[i] = 0.4f * lidar[i] + 0.35f * radar[i] + 0.25f * camera[i];
        fused[i] += 0.5f * sinf(i * 0.01f); // Adding some noise
    }
}

int main() {
    float *lidar = (float *)malloc(N * sizeof(float));
    float *radar = (float *)malloc(N * sizeof(float));
    float *camera = (float *)malloc(N * sizeof(float));
    float *fused = (float *)malloc(N * sizeof(float));

    if (!lidar || !radar || !camera || !fused) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    double baselineTime = 0.0;
    printf("\nAutonomous Vehicle Sensor Fusion Scalability Study\n");
    printf("Data points per sensor: %d\n", N);
    printf("---------------------------------------------------\n");
    printf("Threads\tTime (s)\tSpeedup\tEfficiency\n");

    for (int p = 1; p <= 16; p++) {
        omp_set_num_threads(p);
        double startTime = omp_get_wtime();

        generateLIDARData(lidar);
        generateRadarData(radar);
        generateCameraData(camera);
        fuseSensors(lidar, radar, camera, fused);

        double endTime = omp_get_wtime();
        double elapsedTime = endTime - startTime;

        if (p == 1) {
            baselineTime = elapsedTime;
        }

        double speedup = baselineTime / elapsedTime;
        double efficiency = (speedup / p) * 100;

        printf("%d\t%.6f\t%.2f\t%.2f\n", p, elapsedTime, speedup, efficiency);
    }

    printf("\nSample Fused Data: [%.2f, %.2f, %.2f, %.2f, %.2f]\n", fused[0], fused[1], fused[2], fused[3], fused[4]);

    free(lidar);
    free(radar);
    free(camera);
    free(fused);

    return 0;
}