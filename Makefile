OBJS	= main.o func.o
SOURCE	= main.c func.c
HEADER	= func.h
OUT	= rush.exe
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

func.o: func.c
	$(CC) $(FLAGS) func.c 


clean:
	rm -f $(OBJS) $(OUT)
