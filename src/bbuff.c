
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include "bbuff.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <semaphore.h>



void* buff[BUFFER_SIZE];
int current_size;

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
	current_size = BUFFER_SIZE;
	printf("Initializing buffer to size: %d\n", current_size);
	
	sem_init(&fullbuffers, 0, 0);
	sem_init(&emptybuffers, 0, BUFFER_SIZE);
	sem_init(&mutex, 0, 1);
	return;
}
void bbuff_blocking_insert(void* item)
{
	sem_wait(&emptybuffers);
	sem_wait(&mutex);
	if(current_size > 0){
		buff[BUFFER_SIZE - current_size] = item;
		current_size--;
		printf("current size of buffer after insert: %d\n", current_size);
	}
	sem_post(&mutex);
	sem_post(&fullbuffers); 
	return;
}
void* bbuff_blocking_extract(void)
{
	sem_wait(&fullbuffers);
	sem_wait(&mutex);
	if(current_size != 10){
		free(buff[BUFFER_SIZE - (current_size+1)]);
		current_size++;
		printf("current size of buffer after extract: %d\n", current_size);
	}
	sem_post(&mutex);
	sem_post(&emptybuffers); 
	return NULL;
}
_Bool bbuff_is_empty(void)
{
	if(current_size == 10){
		return true;
	}
	return false;
}
