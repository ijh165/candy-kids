#  Filename: Makefile
#  Created by Ivan Jonathan Hoo
#  Copyright (c) 2016 Ivan Jonathan Hoo. All rights reserved.

CC = gcc
CCFLAGS = -std=gnu99 -pthread -lrt -g -Wall -Werror

SRC = candy_kids.c
EXE = candy_kids

# all: candy_kids

# candy_kids: $(SRC)
# 	$(CC) $(CCFLAGS) $(SRC) -o $(EXE)

# clean:
# 	rm -f candy_kids *.o

all: candy_kids

# Compile all .c files to .o files
%.o : %.c
	$(CC) -c $(CCFLAGS) $<

candy_kids: candy_kids.o bbuff.o stats.o
	$(CC) $(CCFLAGS) -o $(EXE) candy_kids.o bbuff.o stats.o

clean:
	rm -f core *.o candy_kids