/***

2. (10 points) Measure the cost of a minimal system call in C/C++. Unlike a regular function call, a system call traps into the  operating system kernel. The minimal cost can be emulated by measuring the cost of getpid() which doesn't really do anything

***/
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	getpid();
	return 0;
}
