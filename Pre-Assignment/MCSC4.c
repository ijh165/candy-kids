/***
4. (40 points) Measure the cost of a thread switching. A possible measurement strategy (
on a single-processor machine) is provided below as a hint:

Two threads alternate using a shared integer num (set to be 0 initially), a mutex lock and two condition variables. Thread #1 keeps waiting for num to become 1 and then 
changing it to 0. Thread #1 keeps waiting for num to become 0 and changing it to 1.

Figure out the rest ....

***/

#include <unistd.h>
#include <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t condVar1;
pthread_cond_t condVar2;
int shared_integer = 0;
pthread_t tid[2];
_Bool first_time_in = 1;
void* doSomeThing(void *arg);
void* doSomeThing2(void *arg);
int main(int argc, char *argv[]){

	//pthread_mutex_init(&lock, NULL);
printf("Hello\n");
        pthread_create(&(tid[0]), NULL, &doSomeThing, NULL); 
	//shared_integer = 1;       
        pthread_create(&(tid[1]), NULL, &doSomeThing2, NULL);
	    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
	return 0;
}

void* doSomeThing(void *arg)
{
	//int initial_val = shared_integer;
	pthread_mutex_lock(&lock);
	printf("Enter first thread, val of shared_integer: %d\n", shared_integer);

	while(shared_integer == 0){
		printf("looping in first thread\n");
		//if(first_time_in == 1){
		//	first_time_in = 0;
		//	break;
		//}
		pthread_cond_wait(&condVar1, &lock);
	}	
	if(shared_integer == 1){
		shared_integer = 0;
	}
	else{
		shared_integer = 1;
	}
	printf("Exit first thread, val of shared_integer: %d\n", shared_integer);
	pthread_cond_signal(&condVar2);
	pthread_mutex_unlock(&lock);

}
void* doSomeThing2(void *arg)
{
	//int initial_val = shared_integer;
	pthread_mutex_lock(&lock);

	printf("Enter second thread, val of shared_integer: %d\n", shared_integer);
	while(shared_integer==1){

		printf("looping in second thread\n");
		pthread_cond_wait(&condVar2, &lock);
	}

	if(shared_integer == 1){
		shared_integer = 0;
	}
	else{
		shared_integer = 1;
	}
	printf("Exit second thread, val of shared_integer: %d\n", shared_integer);
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&condVar1);
}
