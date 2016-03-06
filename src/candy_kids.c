// Filename: candy_kids.c
// Created by Ivan Jonathan Hoo and Raymond Chan
// Copyright (c) 2016 Ivan Jonathan Hoo and Raymond Chan. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define ARGC_ERR_MSG "Too few or too many arguments, exiting program"
#define ARGV_ERR_MSG "Invalid arguments, exiting program"

void validate_args(char** argv)
{
	for(int i=1; i<=3; i++) {
		for(int j=0; j<strlen(argv[i]); j++) {
			if(!isdigit(argv[i][j])) {
				perror(ARGV_ERR_MSG);
				exit(-1);
			}
		}
	}
}

int main(int argc, char** argv)
{
	// 1. Extract arguments
	// 2. Initialize modules
	// 3. Launch candy-factory threads
	// 4. Launch kid threads
	// 5. Wait for requested time
	// 6. Stop candy-factory threads
	// 7. Wait until no more candy
	// 8. Stop kid threads
	// 9. Print statistics
	// 10. Cleanup any allocated memory

	if(argc!=4) {
		perror(ARGC_ERR_MSG);
		exit(-1);
	}

	validate_args(argv);

	return 0;
}