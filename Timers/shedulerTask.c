#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

struct timespec A_startTime, B_startTime, C_startTime;

double time_diff(struct timespec* start, struct timespec* end){
    double elapsed = (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1e9;
    return elapsed;
}

void taskA(){ 
    printf("Task A executed (1 sec)\n"); 
}
void taskB(){
    printf("Task B executed (2 sec)\n"); 
}
void taskC(){ 
    printf("Task C executed (3 sec)\n"); 
}

void timer_handler(int signum) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    
    double elapsedA = time_diff(&A_startTime, &now);
    double elapsedB = time_diff(&B_startTime, &now);
    double elapsedC = time_diff(&C_startTime, &now);

    if (elapsedA >= 1.0) {
        taskA();
        A_startTime = now;
    }
    if (elapsedB >= 2.0) {
        taskB();
        B_startTime = now;
    }
    if (elapsedC >= 3.0) {
        taskC();
        C_startTime = now;
    }

}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    sa.sa_handler = &timer_handler;
    sigaction(SIGALRM, &sa, NULL);

    clock_gettime(CLOCK_MONOTONIC, &A_startTime);
    B_startTime = A_startTime;
    C_startTime = A_startTime;

    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    while (1)
        pause();
    return 0;
}
