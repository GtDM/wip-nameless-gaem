CC = clang++
CFLAGS  = -g -O0 -std=c++1z -Wall

default: noname

noname:  main.o Entity.o Level.o Debug.o
	$(CC) $(CFLAGS) -o ./wip-nameless-gaem main.o Entity.o Level.o Debug.o -lBox2D -lsfml-graphics -lsfml-window -lsfml-system

Entity.o:  Entity.cpp Entity.hpp 
	$(CC) $(CFLAGS) -c Entity.cpp

Level.o:  Level.cpp Level.hpp
	$(CC) $(CFLAGS) -c Level.cpp

Debug.o:  Debug.cpp Debug.hpp
	$(CC) $(CFLAGS) -c Debug.cpp

main.o:  main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

clean: 
	$(RM) wip-nameless-gaem *.o *~
