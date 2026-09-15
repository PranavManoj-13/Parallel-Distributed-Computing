/*
1. Only one thread executes the block at a time.
2. Protects shared variables.
*/

#include <stdio.h>
#include <omp.h>

int main(void) {
    int sum = 0;

    #pragma omp parallel
    {
        #pragma omp critical
        {
            sum += 1;
            printf("Thread %d: sum = %d\n", omp_get_thread_num(), sum);
        }
    }
}