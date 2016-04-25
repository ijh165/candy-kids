/***

3, (40 points) Measure the cost of a process switching. A possible measurement strategy (on a single-processor machine) is provided below as a hint:

Your test program starts with a main process which then creates two pipes with a read file descriptor and a write file descriptor in each pipe

***/

#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>


#include <string.h>
#include <pthread.h>
#include <stdlib.h>


double timespec_to_ms(struct timespec *ts)
{
	return ts-> tv_sec *1000.0 + ts-> tv_nsec/1000000.0;
}

//struct timespec end_time;

int main(int argc, char *argv[]){
	int fd[2], gd[2];
	pid_t childpid;
	char readbuffer[2];
	pipe(fd);
	pipe(gd);
	if((childpid = fork()) == -1){
		exit(1);
	}
	else if(childpid == 0){
	    struct timespec start_time1;

		close(fd[1]);
		close(gd[0]);
		double tmp1, tmp2;
		read(fd[0], &tmp1, sizeof(tmp1));
		clock_gettime(CLOCK_MONOTONIC_RAW, &start_time1);
        tmp2 = timespec_to_ms(&start_time1);
		printf("Received strings: %f\n", tmp2-tmp1);
		//	printf("Received strings: %f\n", tmp2);


		write(gd[1], (const void *)"C", (strlen((const void *)"C")+1));

	}
	else{
		close(fd[0]);
		close(gd[1]);
		struct timespec start_time;
		clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
		double tmp = timespec_to_ms(&start_time);
		//printf("Received string: %f\n", tmp);
		write(fd[1], &tmp, sizeof(tmp));


		read(gd[0], (readbuffer+1), sizeof((readbuffer+1)));
		//printf("Received string: %c\n", readbuffer[1]);
	}

	return 0;
}

