#include <omp.h>
#include <stdio.h>

int main() {
    int a = 2;
    int b = 3;
    int S = 0;

    #pragma omp parallel num_threads(2)
    {
        S = S + a * b;
        printf("Thread %d: S = %d\n", omp_get_thread_num(), S);
    }

    printf("Final S (Race Condition): %d\n", S);
    return 0;
}