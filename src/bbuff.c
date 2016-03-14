#define _POSIX_C_SOURCE 199309L

#include "bbuff.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>

void* buff[BUFFER_SIZE];
int avail_slots;

//Semaphores & Mutex
sem_t fullbuffers;
sem_t emptybuffers;
sem_t mutex;


double current_time_in_ms(void)
{
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}

void bbuff_init(void)
{
	avail_slots = BUFFER_SIZE;
	/*printf("Initializing buffer to size: %d\n", avail_slots);*/
	
	sem_init(&fullbuffers, 0, 0);
	sem_init(&emptybuffers, 0, BUFFER_SIZE);
	sem_init(&mutex, 0, 1);
	return;
}

void bbuff_blocking_insert(void* item)
{
	sem_wait(&emptybuffers);
	sem_wait(&mutex);
	if(avail_slots > 0){
		buff[BUFFER_SIZE - avail_slots] = item;
		avail_slots--;
		printf("avail_slots of buffer after insert: %d\n", avail_slots);
	}
	sem_post(&mutex);
	sem_post(&fullbuffers); 
	return;
}

void* bbuff_blocking_extract(void)
{
	void* item_ptr_returned = NULL;
	sem_wait(&fullbuffers);
	sem_wait(&mutex);
	if(avail_slots < 10) {
		void* item_ptr = buff[BUFFER_SIZE - (avail_slots+1)];
		item_ptr_returned = malloc(sizeof(*item_ptr));
		memcpy(item_ptr_returned, item_ptr, sizeof(*item_ptr));
		free(item_ptr);
		avail_slots++;
		printf("avail_slots of buffer after extract: %d\n", avail_slots);
	}
	sem_post(&mutex);
	sem_post(&emptybuffers); 
	return item_ptr_returned;
}

_Bool bbuff_is_empty(void)
{
	if(avail_slots == 10){
		return true;
	}
	return false;
}
