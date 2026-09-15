/*
1. It divides different blocks of code among different threads.
2. Each thread executes its own block of code independently.
*/

#include <stdio.h>
#include <omp.h>

int main(void) {
    int shared_var = 10;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            shared_var += 1;
            printf("Thread %d executed S1. Shared Variable = %d\n", omp_get_thread_num(), shared_var);
        }

        #pragma omp section
        {
            shared_var += 2;
            printf("Thread %d executed S2. Shared Variable = %d\n", omp_get_thread_num(), shared_var);
        }

        #pragma omp section
        {
            shared_var += 3;
            printf("Thread %d executed S3. Shared Variable = %d\n", omp_get_thread_num(), shared_var);
        }
    }
    printf("Final value of shared variable: %d\n", shared_var);
} 