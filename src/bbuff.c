

#include <time.h>
#include "bbuff.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

//the buffer array
void* buff[BUFFER_SIZE];
int current_size;
/* Piece of shit doesn't work lol
//function to get current time
double current_time_in_ms(void)
{
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}
*/
void bbuff_init(void)
{
	current_size = BUFFER_SIZE;
	return;
}
void bbuff_blocking_insert(void* item)
{
	//semaphore
	if(current_size > 0){
		buff[BUFFER_SIZE - current_size] = item;
		current_size--;
	}
	return;
}
void* bbuff_blocking_extract(void)
{
	// semaphore
	if(current_size != 10){
		free(buff[BUFFER_SIZE - (current_size+1)]);
		current_size++;
	}
	return NULL;
}
_Bool bbuff_is_empty(void)
{
	if(current_size == 10){
		return true;
	}
	return false;
}
