#  Filename: Makefile
#  Created by Ivan Jonathan Hoo
#  Copyright (c) 2016 Ivan Jonathan Hoo. All rights reserved.

CC = gcc
CCFLAGS = -std=gnu99 -g -Wall -Werror

SRC = candy_kids.c
EXE = candy_kids

all: candy_kids

candy_kids: $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $(EXE)

clean:
	rm -f candy_kids *.o