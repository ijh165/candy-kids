#include "bbuff.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>

#define BUFFER_SIZE 10

//variables
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
	sem_init(&fullbuffers, 0, 0);
	sem_init(&emptybuffers, 0, BUFFER_SIZE);
	sem_init(&mutex, 0, 1);
	return;
}

void bbuff_blocking_insert(void* item)
{
	sem_wait(&emptybuffers);
	sem_wait(&mutex);

	buff[BUFFER_SIZE - avail_slots] = item;
	avail_slots--;

	sem_post(&mutex);
	sem_post(&fullbuffers);

	return;
}

void* bbuff_blocking_extract(void)
{
	sem_wait(&fullbuffers);
	sem_wait(&mutex);
	
	int idx = BUFFER_SIZE - (avail_slots+1);
	void* item_ptr = buff[idx];
	buff[idx] = NULL;
	avail_slots++;

	sem_post(&mutex);
	sem_post(&emptybuffers);

	return item_ptr;
}

_Bool bbuff_is_empty(void)
{
	return (avail_slots == BUFFER_SIZE);
}
