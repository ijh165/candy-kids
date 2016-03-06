// Filename: candy_num_kids.c
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

#define ARGC_ERR_MSG "Usage: %s <#factories> <#kids> <#seconds>\n"
#define ARGV_ERR_MSG "Invalid arguments, should be integer\n"

void* factory_thread(void* arg)
{

	pthread_exit(NULL);
}

void* kid_thread(void* arg)
{

	pthread_exit(NULL);
}

pthread_t* launch_factory_threads(int num_factories)
{
	pthread_t* threadIDs = malloc(num_factories*sizeof(pthread_t));

	for(int i=0; i<num_factories; i++) {
		pthread_t id;
		pthread_create(&id, NULL, factory_thread, &i);
		threadIDs[i] = id;
	}

	return threadIDs;
}

pthread_t* launch_kid_threads(int num_kids)
{
	pthread_t* threadIDs = malloc(num_kids*sizeof(pthread_t));

	for(int i=0; i<num_kids; i++) {
		pthread_t id;
		pthread_create(&id, NULL, kid_thread, &i);
		threadIDs[i] = id;
	}

	return threadIDs;
}

int main(int argc, char** argv)
{
	// 1. Extract arguments

	if(argc != 4) {
		printf(ARGC_ERR_MSG, argv[0]);
		exit(-1);
	}

	int num_factories = atoi(argv[1]);
	int num_kids = atoi(argv[2]);
	int num_seconds = atoi(argv[3]);

	if(num_factories<=0 || num_kids<=0 || num_seconds<=0) {
		printf(ARGV_ERR_MSG);
		exit(-1);
	}


	// 2. Initialize modules
	bbuff_init();
	stats_init(0); //change this to number of producers (a.k.a. factories)
	

	// 3. Launch candy-factory threads
	pthread_t* factory_thread_IDs = launch_factory_threads(num_factories);


	// 4. Launch kid threads
	pthread_t* kid_thread_IDs = launch_kid_threads(num_factories);


	// 5. Wait for requested time

	for(int i=0; i<num_seconds; i++) {
		printf("Time: %ds\n", i+1);
		sleep(1);
	}


	// 6. Stop candy-factory threads

	for(int i=0; i<num_factories; i++) {
		pthread_join(factory_thread_IDs[i], NULL);
	}
	

	// 7. Wait until no more candy




	// 8. Stop kid threads

	for(int i=0; i<num_kids; i++) {
		pthread_join(kid_thread_IDs[i], NULL);
	}


	// 9. Print statistics




	// 10. Cleanup any allocated memory
	free(factory_thread_IDs);
	free(kid_thread_IDs);

	return 0;
}