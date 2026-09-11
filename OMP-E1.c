#include <omp.h>
#include <stdio.h>

int NUM_THREADS = 3;
int NUM_ITERATIONS = 16;

int main() {

    omp_set_num_threads(NUM_THREADS);

    int chunkSize = (NUM_ITERATIONS + NUM_THREADS - 1) / NUM_THREADS;

    #pragma omp parallel for schedule(static, chunkSize)
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        printf("Thread %d is executing iteration %d\n",
               omp_get_thread_num(), i);
    }

    return 0;
}