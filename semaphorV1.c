#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t sem;
int shared=1;


void *increse_func(void* arg) {
	int x;
//sem_wait(&sem);
x=shared;//thread2 reads value of shared variable
printf("Thread1 reads the value as %d\n",x);
x++; //thread2 increments its value
printf("Local updation by Thread1: %d\n",x);
sleep(1); //thread2 is preempted by thread 1
shared=x; //thread2 updates the value of shared variable
printf("Value of shared variable updated by Thread1 is: %d\n",shared);
//sem_post(&sem);
return NULL;
}


void *decreas_func(void* arg)
{
int y;
//sem_wait(&sem);
y=shared;//thread2 reads value of shared variable
printf("Thread2 reads the value as %d\n",y);
y--; //thread2 increments its value
printf("Local updation by Thread2: %d\n",y);
sleep(1); //thread2 is preempted by thread 1
shared=y; //thread2 updates the value of shared variable
printf("Value of shared variable updated by Thread2 is: %d\n",shared);
//sem_post(&sem);
return NULL;
}



int main(){
	pthread_t pid1,pid2;
    
	//sem_init(&sem,0,1);

	
	int creation_check = pthread_create(&pid1,NULL,increse_func, NULL);

	
	int creation_check2 = pthread_create(&pid2,NULL,decreas_func, NULL);
	
	

	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);

	printf(" Final shared = %d\n", shared);  
    //sem_destroy(&sem);  
    


	return 0;

}

