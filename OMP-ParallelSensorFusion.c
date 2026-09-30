#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define FRAMES 1000
#define SECTORS 4

int main(void) {
    static float lidar_dist[FRAMES][SECTORS];
    static float radar_dist[FRAMES][SECTORS];
    static float fused_dist[FRAMES][SECTORS];
    double local_sum = 0.0;
    omp_set_num_threads(8);

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp for collapse(2) schedule(dynamic)
        for(int f=0;f<FRAMES;f++) {
            for(int s=0;s<SECTORS;s++) {
                lidar_dist[f][s] = (float)(rand() % 100);
                radar_dist[f][s] = (float)(rand() % 100);
            }
        }

        #pragma omp single
        {
            printf("Initialization done using %d threads.\n", num_threads);
        }

        #pragma omp barrier

        #pragma omp for collapse(2) schedule(static)
        for(int f=0;f<FRAMES;f++) {
            for(int s=0;s<SECTORS;s++) {
                float ld = lidar_dist[f][s];
                float rd = radar_dist[f][s];
                fused_dist[f][s] = (ld < rd) ? ld : rd;
            }
        }

        #pragma omp for collapse(2) reduction(+:local_sum)
        for(int f=0;f<FRAMES;f++) {
            for(int s=0;s<SECTORS;s++) {
                local_sum += fused_dist[f][s];
            }
        }

        #pragma omp single
        {
            double avg = local_sum / (FRAMES * SECTORS);
            printf("Global average fused distance: %f\n", avg);
        }

        #pragma omp for
        for(int f=0;f<3;f++) {
            #pragma omp critical
            {
                printf("Thread %d printing frame %d (first 10 values): ", tid, f);
                for(int s=0;s<10;s++) {
                    printf("%0.2f ", fused_dist[f][s]);
                }
                printf("\n");
            }
        }
    }

    double end = omp_get_wtime();
    printf("Total execution time: %f seconds\n", end - start);
}