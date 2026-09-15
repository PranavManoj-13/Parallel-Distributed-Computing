#include <stdio.h>
#include <omp.h>

static int counter = 0;
#pragma omp threadprivate(counter)

int main(void) {
    #pragma omp parallel
    {
        counter = omp_get_thread_num();
        printf("Thread %d: counter = %d\n", omp_get_thread_num(), counter);
    }

    printf("\n");

    #pragma omp parallel
    {
        printf("Thread %d: counter = %d\n", omp_get_thread_num(), counter);
    }

    printf("\n");

    #pragma omp parallel
    {
        counter = omp_get_thread_num() + 10;
        printf("Thread %d: counter = %d\n", omp_get_thread_num(), counter);
    }
}