/***

2. (10 points) Measure the cost of a minimal system call in C/C++. Unlike a regular function call, a system call traps into the  operating system kernel. The minimal cost can be emulated by measuring the cost of getpid() which doesn't really do anything

***/
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
#include <stdio.h>
double timespec_to_ms(struct timespec *ts)
{
	return ts-> tv_sec *1000.0 + ts-> tv_nsec/1000000.0;
}
int main(int argc, char *argv[]){
	struct timespec start_time, end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	for(int i = 0; i<1000000; i++){
		syscall(SYS_getpid);
	}	
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	
	printf("%fms\n", (timespec_to_ms(&end_time)-timespec_to_ms(&start_time))/1000000);
	return 0;
}
