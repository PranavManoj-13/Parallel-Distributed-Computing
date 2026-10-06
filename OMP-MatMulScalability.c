#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

int main(void) {
    static float A[N][N], B[N][N], C[N][N];
    double start, end;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = (float)(i + j);
            B[i][j] = (float)(i - j);
            C[i][j] = 0.0f;
        }
    }

    printf("Threads\tTime (s)\tSpeedup\tEfficiency(%)\n");

    double baseline = 0.0;

    for(int p=1;p<=8;p *= 2) {
        omp_set_num_threads(p);
        start = omp_get_wtime();
    
        #pragma omp parallel for collapse(2) schedule(static)
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                float sum = 0.0f;
                for(int k = 0; k < N; k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        }

        end = omp_get_wtime();
        double time = end - start;

        if (p == 1) {
            baseline = time;
        }
        double speedup = baseline / time;
        double efficiency = (speedup / p) * 100.0;

        printf("%d\t%.6f\t%.2f\t%.2f\n", p, time, speedup, efficiency);
    }
}