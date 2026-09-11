#include <omp.h>
#include <stdio.h>

int main(void) {
    int x = 5;
    int y = 10;

    #pragma omp parallel for ordered private(y) 
    for (int i = 0; i < 8; i++) {
        int threadID = omp_get_thread_num();

        #pragma omp ordered
        {
            y = threadID * 2;
            printf("Thread %d: x = %d, y = %d\n", threadID, x, y);
        }
    }

    printf("Final values: x = %d, y = %d\n", x, y);
    return 0;
}