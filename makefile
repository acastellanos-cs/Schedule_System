CC = g++
CPPFLAGS = -std=c++17  -g -Wall
OBJS = main.o bst.o schedule.o

main: $(OBJS)

main.o: bst.h schedule.h

bst.o:  bst.h schedule.h

schedule.o: schedule.h

clean:   
	rm main *.o

leak:
	valgrind -s --leak-check=full ./main
