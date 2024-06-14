####################################################################################
#Makefile for CS480 Assignment #1
#Allen Zhang cssc: 4406 RedID: 816160742 & Karina Yeager: cssc: 4433 RedID: 826646802
####################################################################################
EXEC = dsh
HEADER = processes.h
FILES = main.cpp execute_command.cpp execute_pipe.cpp
CC = g++
LFLAGS = -g
CFLAGS = -g -c

OBJECTS = $(FILES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)
	rm -f *.o

.cpp.o:
	$(CC) $(CFLAGS) $<

execute_command.o: execute_command.cpp processes.h
	$(CC) $(CFLAGS) execute_command.cpp

execute_pipe.o: execute_pipe.cpp processes.h
	$(CC) $(CFLAGS) execute_pipe.cpp

clean:
	rm -f *.o $(EXEC)
####################################################################################     