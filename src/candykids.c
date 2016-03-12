// Filename: candykids.c
// Created by Ivan Jonathan Hoo and Raymond Chan
// Copyright (c) 2016 Ivan Jonathan Hoo and Raymond Chan. All rights reserved.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "bbuff.h"
#include "stats.h"




#define ARG_COUNT 3
#define ERR_MSG "Error, you entered an invalid argument\n"


// 1. Extract arguments
// 2. Initialize modules
// 3. Launch candy-factory threads
// 4. Launch kid threads
// 5. Wait for requested time
// 6. Stop candy-factory threads
// 7. Wait until no more candy
// 8. Stop kid threads
// 9. Print statistics
// 10. Cleanup any allocated memory


void launch_threads(int count, pthread_t *thread, void* (*thread_function)(void*));

void* factory_thread(void* arg);
void* kid_thread(void* arg);
//void* (*thread_function[2])(void*);


_Bool stop_thread = false;

int main(int argc, char *argv[]){
	
	//1. Extract Arguments
	int Factories = 0, Kids = 0, Seconds = 0;
	int *array[3] = {&Factories, &Kids, &Seconds};	

	for(int i = 1; i <= ARG_COUNT; i++){
		sscanf(argv[i], "%d", array[i-1]);
	}
	
		if(argc != 4 || Factories <= 0 || Kids <= 0 || Seconds <= 0){
		printf(ERR_MSG);
		exit(1);
	}
		
	//2. Initialize Modules
	

	//3. Launch candy-factory threads
	
	pthread_t *factory_thread_IDs = malloc(Factories *(sizeof(pthread_t)));
	launch_threads(Factories, factory_thread_IDs, (void*)factory_thread);
	
	//4. Launch Kid threads
	pthread_t *kid_thread_IDs = malloc(Kids *(sizeof(pthread_t)));
	launch_threads(Kids, kid_thread_IDs, (void*)kid_thread);
	
	// 5. Wait for requested time
	for(int i=0; i<Seconds; i++) {
		printf("Time: %ds\n", i+1);
		sleep(1);
	}
	// 6. Stop candy-factory threads
	//Wait, sleep the main thread and allow the factory threads to produce for Seconds and come back to join it
	sleep(Seconds);
	stop_thread = true;
	
	for(int i=0; i<Factories; i++) {
		pthread_join(factory_thread_IDs[i], NULL);
	}


	//8. Stop kid threads

	for(int i=0; i<Kids; i++) {
		pthread_cancel(kid_thread_IDs[i]);
		pthread_join(kid_thread_IDs[i], NULL);
	}
	
	// 10. Cleanup any allocated memory
	free(factory_thread_IDs);
	free(kid_thread_IDs);
	printf("Closing\n");
	
	return 0;
}

void launch_threads(int count, pthread_t *thread, void* (*thread_function)(void*)){


	int err = 0;
	pthread_t id;
	
	for(int i=0; i<count; i++) {
		err = pthread_create(&id, NULL, thread_function, (void*)i);
		if(err != 0){
			printf("gg\n");
		}
		thread[i] = id;
	}
}


void* factory_thread(void* arg)
{
	int i = (int)arg;
	printf("In factory thread ");
	printf("%d\n", i); 
	// mutex here 
	int time_wait;
	while(!stop_thread){
		time_wait = rand()%4;
		printf("Factory %d ships candy & waits %ds\n", i, time_wait);
		// allocate new candy items
		candy_t *candy = malloc(sizeof(candy_t));
		candy->factory_number = i;
		candy->time_stamp_in_ms = 1337;//current_time_in_ms() piece of shit won't work, have to wait for arvin reply
		bbuff_blocking_insert(candy);
		sleep(time_wait);
	}
	printf("Candy-factory %d done\n", i);
	// Need a signal handler
	// When the thread finishes, print the message such as the following (for thread 0): “Candy-factory 0 done"
	
	return NULL;
}

void* kid_thread(void* arg){
	printf("In kid thread\n");
	//mutex here
	int time_wait;
	for(;;){
	time_wait = rand()%2;
		bbuff_blocking_extract();
		// process item into the stats module
				sleep(time_wait);
	}
	return NULL;
}

/*
double current_time_in_ms(void){
	struct timespec now;
	clock_gettime (CLOCK_REALTIME, &now);

	return now.tv_sec* 1000.0 + now.tv_nsec/1000000.0;
}
*/


