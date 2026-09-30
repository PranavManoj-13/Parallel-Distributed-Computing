#include <stdio.h>
#include <stdlib.h>
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

