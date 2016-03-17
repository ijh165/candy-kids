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
#include <stdint.h>
#include "bbuff.h"
#include "stats.h"

#define ARG_COUNT 3
#define INVALID_ARG_ERR "Invalid argument, exiting program!\n"
#define LAUNCH_THREAD_FAIL_ERR "Failed to launch thread, exiting program!\n"

//candy struct
typedef struct candy
{
	int factory_number;
	double time_stamp_in_ms;
} candy_t;

//stop thread flag
_Bool stop_thread = false;

//forward declarations
_Bool invalid_args(int argc, char* argv[]);
void launch_threads(int count, pthread_t* thread, void* (*thread_function)(void*));
void* factory_thread(void* arg);
void* kid_thread(void* arg);

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
int main(int argc, char* argv[])
{	
	//1. Extract Arguments

	int factories = 0, kids = 0, seconds = 0;
	int* array[3] = {&factories, &kids, &seconds};

	if(invalid_args(argc, argv)) {
		printf(INVALID_ARG_ERR);
		exit(1);
	}

	for(int i=1; i<=ARG_COUNT; i++){
		sscanf(argv[i], "%d", array[i-1]);
	}
	
	
	//2. Initialize Modules
	bbuff_init();
	stats_init(factories);


	//3. Launch candy-factory threads
	pthread_t* factory_thread_IDs = malloc(factories *(sizeof(pthread_t)));
	launch_threads(factories, factory_thread_IDs, (void*)factory_thread);
	

	//4. Launch kid threads
	pthread_t* kid_thread_IDs = malloc(kids *(sizeof(pthread_t)));
	launch_threads(kids, kid_thread_IDs, (void*)kid_thread);
	

	//5. Wait for requested time
	for(int i=0; i<seconds; i++) {
		sleep(1);
		printf("Time: %ds\n", i+1);
	}
	

	//6. Stop candy-factory threads
	//Wait, sleep the main thread and allow the factory threads to produce for seconds and come back to join it
	/*sleep(seconds);*/
	stop_thread = true;
	
	for(int i=0; i<factories; i++) {
		pthread_join(factory_thread_IDs[i], NULL);
	}

	
	//7. Wait until no more candy
	while(!bbuff_is_empty());
	
	
	//8. Stop kid threads
	for(int i=0; i<kids; i++) {
		pthread_cancel(kid_thread_IDs[i]);
		pthread_join(kid_thread_IDs[i], NULL);
	}


	//9. Print statistics
	stats_display();


	//10. Cleanup any allocated memory
	stats_cleanup();
	free(factory_thread_IDs);
	free(kid_thread_IDs);
	

	printf("Exiting program!\n");
	return 0;
}

_Bool invalid_args(int argc, char* argv[])
{
	if(argc != 4) {
		return true;
	}

	for(int i=1; i<=ARG_COUNT; i++) {
		if(atoi(argv[i])<1) {
			return true;
		}
	}

	return false;
}

void launch_threads(int count, pthread_t* thread, void* (*thread_function)(void*))
{
	int err = 0;
	pthread_t id;
	
	for(int i=0; i<count; i++) {
		err = pthread_create(&id, NULL, thread_function, (void*)(intptr_t)i);
		if(err != 0){
			printf(LAUNCH_THREAD_FAIL_ERR);
			exit(-1);
		}
		thread[i] = id;
	}
}


void* factory_thread(void* arg)
{
	int i = (intptr_t)arg;
	/*printf("In factory thread %d\n", i);*/
	// mutex here 
	int time_wait;
	while(!stop_thread) {
		time_wait = rand()%4;
		printf("\tFactory %d ships candy & waits %ds\n", i, time_wait);
		//allocate new candy items
		candy_t* candy_ptr = malloc(sizeof(candy_t));
		candy_ptr->factory_number = i;
		candy_ptr->time_stamp_in_ms = current_time_in_ms();
		//insert it to the buffer
		bbuff_blocking_insert(candy_ptr);
		//process item into the stats module
		stats_record_produced(i);
		//sleep
		sleep(time_wait);
	}
	// When the thread finishes, print the message such as the following (for thread 0): “Candy-factory 0 done"
	printf("Candy-factory %d done\n", i);
	
	pthread_exit(NULL);
}

void* kid_thread(void* arg)
{	
	int i = (intptr_t)arg;
	/*printf("In kid thread %d\n", i);*/
	//mutex here
	int time_wait;
	for(;;) {
		time_wait = rand()%2;
		//extract from buffer
		candy_t* candy_ptr = (candy_t*) bbuff_blocking_extract();
		printf("\tKid %d eats candy & sleeps %ds\n", i, time_wait);
		//process item into the stats module
		if(candy_ptr!=NULL) {
			stats_record_consumed(candy_ptr->factory_number, current_time_in_ms()-candy_ptr->time_stamp_in_ms);
		}
		//free the extracted item
		free(candy_ptr);
		//sleep
		sleep(time_wait);
	}

	pthread_exit(NULL);
}