CC = g++
CFLAGS = -g -Wall -Wextra

all: main clean

clean:
	rm *.o

main: main.o classes.o functions.o board_class.o
	${CC} ${CFLAGS} -o $@ $^

%.o: %.cpp
	${CC} ${CFLAGS} -c -o $@ $^
