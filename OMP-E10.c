/*
1. All threads will wait at the barrier until all threads have reached it. 
2. After that, they will continue executing the code after the barrier.
3. This helps to ensure synchronization among threads and can be useful in 
   scenarios where certain computations must be completed before proceeding to the next step.
*/ 

#include <stdio.h>
#include <omp.h>

int main(void) {
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Thread %d before barrier\n", tid);

        #pragma omp barrier
        printf("Thread %d after barrier\n", tid);
    }
}