#include <omp.h>
#include <stdio.h>

int main() {
    int i;
    int sharedVar = 0;

    #pragma omp parallel private(i)
    {
        i = omp_get_thread_num();
        printf("Thread %d: sharedVar = %d   private i = %d\n", omp_get_thread_num(), sharedVar, i);
    }
    return 0;
}