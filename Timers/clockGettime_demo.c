#include <stdio.h>
#include <time.h>

void delay(void){
    for(volatile long i = 0; i < 10000000; i++);
}

int main(){
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    delay();
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Elapsed time: %.6f seconds\n", elapsedTime);
    return 0;
}