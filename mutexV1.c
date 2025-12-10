#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *incrementer(void* arg);
void *decrementer(void* arg);

int shared = 1;                    
pthread_mutex_t mutex;             

int main() {
    
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, incrementer, NULL);
    pthread_create(&thread2, NULL, decrementer, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared is %d\n", shared);

    
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *incrementer(void* arg) {
    int x;

    pthread_mutex_lock(&mutex);    
    x = shared;
    printf("Thread1 reads the value as %d\n", x);

    x++;
    printf("Local updation by Thread1: %d\n", x);

    sleep(1);                      // ‌ preemption

    shared = x;
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);

    pthread_mutex_unlock(&mutex);  
    return NULL;
}

void *decrementer(void* arg) {
    int y;

    pthread_mutex_lock(&mutex);    
    y = shared;
    printf("Thread2 reads the value as %d\n", y);

    y--;
    printf("Local updation by Thread2: %d\n", y);

    sleep(1);

    shared = y;
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);

    pthread_mutex_unlock(&mutex);  
    return NULL;
}
