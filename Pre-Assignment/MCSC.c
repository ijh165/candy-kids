#include <unistd.h>
#include <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;
pthread_t tid[2];
int shared_integer = 0;
void minimal_function(void);
void* doSomeThing(void *arg)
{

	pthread_mutex_t lock;
		int tmp = shared_integer;
		//printf("%d\n", tmp);
	while(tmp == shared_integer){
			printf("aas\n");
		pthread_cond_wait(&cond, &lock);
	}	
	
	if(shared_integer == 1){
		shared_integer = 0;
	}
	else{
		shared_integer = 1;
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);

}


int main(int argc, char *argv[]){
	
	/* #1 */
	minimal_function();
	
	/* #2 */
	int i = getpid();	

	
	/* #3 */
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
	
	/* #4 */ 
	

    //int err;


        pthread_create(&(tid[0]), NULL, &doSomeThing, NULL);
        
        pthread_create(&(tid[1]), NULL, &doSomeThing, NULL);
        
		
	return 0;
}

void minimal_function(void){
}


