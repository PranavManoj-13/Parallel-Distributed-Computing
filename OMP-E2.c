#include <omp.h>
#include <stdio.h>

void doWork(int i) {
    printf("Task %d executed by thread %d\n", i, omp_get_thread_num());
}

int main() {
    int NUM_TASKS = 10;

    printf("Program starts in sequential mode.\n");
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < NUM_TASKS; i++) {
                #pragma omp task
                doWork(i);
            }
        }
    }

    printf("Back to sequential execution by master thread.\n");
    return 0;
}
