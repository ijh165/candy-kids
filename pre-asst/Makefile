#  Filename: Makefile
#  Created by Ivan Jonathan Hoo
#  Copyright (c) 2016 Ivan Jonathan Hoo. All rights reserved.

CC = gcc
CCFLAGS = -std=gnu99 -O0 -pthread -lrt -g -Wall -Werror

all: MCSC1 MCSC2 MCSC3 MCSC4

MCSC1:
	$(CC) $(CCFLAGS) -o MCSC1 MCSC1.c

MCSC2:
	$(CC) $(CCFLAGS) -o MCSC2 MCSC2.c

MCSC3:
	$(CC) $(CCFLAGS) -o MCSC3 MCSC3.c

MCSC4:
	$(CC) $(CCFLAGS) -o MCSC4 MCSC4.c

clean:
	rm -f core *.o MCSC1 MCSC2 MCSC3 MCSC4