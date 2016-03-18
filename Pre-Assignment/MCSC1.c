/***

1. (10 points) Measure the cost of a minimal function call in C/C++ (e.g., X seconds). The minimal cost can be emulated by measuring a bare function call that neither takes any parameter nor does anything inside the function

***/
#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>


void minimal_function(void);
double timespec_to_ms(struct timespec *ts)
{
	return ts-> tv_sec *1000.0 + ts-> tv_nsec/1000000.0;
}
int main(int argc, char *argv[]){
	/* #1 */
	struct timespec start_time, end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	for(int i = 0; i<1000000; i++){	
	minimal_function();
	}	
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	
	printf("%fms\n", (timespec_to_ms(&end_time)-timespec_to_ms(&start_time))/1000000);
	return 0;
}

void minimal_function(void){
	return;
}

