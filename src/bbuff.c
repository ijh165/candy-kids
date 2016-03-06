#include "bbuff.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//the buffer array
void* buff[BUFFER_SIZE];

//function to get current time
double current_time_in_ms(void)
{
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}

void bbuff_init(void)
{
	//fill me
	return;
}

void bbuff_blocking_insert(void* item)
{
	//fill me
	return;
}

void* bbuff_blocking_extract(void)
{
	//fill me
	return NULL;
}

_Bool bbuff_is_empty(void)
{
	//fill me
	return false;
}