/***

3, (40 points) Measure the cost of a process switching. A possible measurement strategy (on a single-processor machine) is provided below as a hint:

Your test program starts with a main process which then creates two pipes with a read file descriptor and a write file descriptor in each pipe

***/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

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
		close(fd[1]);
		close(gd[0]);
		
		read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Received strings: %c\n", readbuffer[0]);
		

		write(gd[1], (const void *)"C", (strlen((const void *)"C")+1));
		 
	}
	else{
		close(fd[0]);
		close(gd[1]);
		write(fd[1], (const void *)"R", (strlen((const void *)"R")+1));
		

		read(gd[0], (readbuffer+1), sizeof((readbuffer+1)));
		printf("Received string: %c\n", readbuffer[1]);
	}
	return 0;
}


