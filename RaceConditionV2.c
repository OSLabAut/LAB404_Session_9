#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define EXPERIMENT_NUM 1  

int shared = 0;           
sem_t s;                  
int total_operations = 1000;  

void* incrementer(void* arg) {
    int thread_id = *(int*)arg;
    for(int i = 0; i < total_operations; i++) {
        sem_wait(&s);     
        int temp = shared;
        //usleep(rand() % 1000); 
        shared = temp + 1;
        sem_post(&s);     
    }
    printf("Thread %d finished. Shared = %d\n", thread_id, shared);
    return NULL;
}

void* decrementer(void* arg) {
    int thread_id = *(int*)arg;
    for(int i = 0; i < total_operations; i++) {
        sem_wait(&s);
        int temp = shared;
       // usleep(rand() % 1000);
        shared = temp - 1;
        sem_post(&s);
    }
    printf("Thread %d finished. Shared = %d\n", thread_id, shared);
    return NULL;
}

int main() {
    printf(" Experiment #%d - Race Condition Killer Lab\n", EXPERIMENT_NUM);
    printf("Total operations: %d | Expected: shared = %d\n\n", total_operations, 0);
    
    srand(time(NULL));
    sem_init(&s, 0, 1);
    
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    
    pthread_create(&t1, NULL, incrementer, &id1);
    pthread_join(t2, NULL);

    pthread_create(&t2, NULL, decrementer, &id2);
    
    pthread_join(t1, NULL);
    
  
    
    printf("\n Final result: shared = %d\n", shared);
    if(shared == 0) {
        printf(" Semaphore worked perfectly!\n");
    } else {
        printf(" Race Condition detected!\n");
    }
    
    sem_destroy(&s);
    return 0;
}
