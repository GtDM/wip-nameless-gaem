CC = clang++
CFLAGS  = -g -O0 -std=c++1z -Wall
OBJECTS = main.o Entity.o Level.o Debug.o
LINKER_FLAGS = -lBox2D -lsfml-graphics -lsfml-window -lsfml-system

default:  $(OBJECTS)
	$(CC) $(CFLAGS) -o ./wip-nameless-gaem $(OBJECTS) $(LINKER_FLAGS)

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
