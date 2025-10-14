#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* worker(void* arg){
    printf("Worker thread started!\n");
    printf("Hello this is worker\n");
    printf("Worker thread finished!\n");
    return NULL;
}

int main(){
    pthread_t thread;
    printf("Main thread started!\n");
    if(pthread_create(&thread, NULL, worker, NULL) != 0){
        perror("Thread Creation failed!\n");
        return 1;
    }
    pthread_join(thread, NULL);
    printf("Main thread finished!\n");
    return 0;
}