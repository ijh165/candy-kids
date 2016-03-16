/* Libraries */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

/* Defined types */

#define DATA_SIZE 100
#define NUM_THREADS 40
#define NUM_SWAPS 2000000 

/* Global data */

int ar[DATA_SIZE] = {};
pthread_t tid[NUM_THREADS];
pthread_mutex_t lock;

/* Functions */ 

void swap(int x, int y);
int rand_func(void);
void* doSomeThing(void *arg);
void initialize_ar(void);
void* check(void *arg);


int main(int argc, char *argv[]){
	initialize_ar();
	int err = 0;
	for(int i = 0; i<NUM_THREADS; i++){
		err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);	
	}
	
	    for (int i = 0; i < NUM_THREADS; i++){
       pthread_join(tid[i], NULL);
       }
       
       int check_thread_id = 0;
       pthread_t check_thread;
       check_thread_id = pthread_create(&check_thread, NULL, &check, NULL);
       pthread_cancel(check_thread_id);
       pthread_join(check_thread_id, NULL);
           pthread_mutex_destroy(&lock);
    return 0;

}


int rand_func(void){
	int x = 0;
	srand(time(NULL));
	return rand() % (99 + 1 - 0) + 0;
	
//printf("%d\n", x);
}

void* doSomeThing(void *arg)
{
pthread_mutex_lock(&lock);
	int x, y;
	for(int i = 0; i < NUM_SWAPS; i ++){
		x = rand_func();
		y = rand_func();
		swap(x, y);
	}
pthread_mutex_unlock(&lock);
	return NULL;
}

void swap(int x, int y){

	ar[x] = ar[x] + ar[y];
	ar[y] = ar[x] - ar[y];
	ar[x] = ar[x] - ar[y];
}

void initialize_ar(void){
	for(int i = 0; i<DATA_SIZE; i++){
		ar[i] = i;
	}
	//printf("%d\n", ar[99]);
}

void* check(void *arg){
int x =0;
	for(;;){
		sleep(1);
		printf("*\n");
		for (int i = 0; i < DATA_SIZE; i++) {
    			for (int j = i + 1; j < DATA_SIZE; j++) {
        			if (ar[i] == ar[j]) {
            			x++;
        			}
    			}
		}
		if(x>0){
			printf("Count Missing = %d\n", x);
		}
	}
	return NULL;
}	
