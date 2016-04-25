#candy-kids
Multithreaded program to solve the producer-consumer problem where candy factories are the producer and kids are the consumer. A bounded-buffer with semaphores is used.

#Team Members
1. Ivan Jonathan Hoo, ihoo@sfu.ca
2. Raymond Chan, rca71@yahoo.com

#Files and Folders

1) The "src" folder contains the source code and Makefile for the solution to the candy-kids problem. Do the following to run the program.
- Run "make" command in terminal to build the executable "candykids"
- Run the command: ./candykids <#factories> <#kids> <#seconds>
- #factories: Number of candy-factory threads to spawn.
- #kids: Number of kid threads to spawn.
- #seconds: Number of seconds to allow the factory threads to run for
- Example: ./candykids 3 1 10

2) The "pre-assignment" folder contains the source code and Makefile for the Measuring Context Switch Costs Pre-Assignment as well as the pdf Time.pdf which documents all the timing measurements.
- MCSC1.c is code for the #1 pre assignment (Measure the cost of a minimal function call in C)
- MCSC2.c is code for the #2 pre assignment (Measure the cost of a minimal system call in C)
- MCSC3.c is code for the #3 pre assignment (Measure the cost of a process switching)
- MCSC4.c is code for the #4 pre assignment (Measure the cost of a thread switching)

PS: If you want to try the timing yourself run the commands "make MCSC1", "make MCSC2", "make MCSC3", or "make MCSC4" and run the respective executables.