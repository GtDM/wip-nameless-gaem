CC ?= clang++
CFLAGS  = -g -O0 -std=c++14 -Wall

default: noname

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
noname:  main.o Entity.o Level.o 
	$(CC) $(CFLAGS) -o ./wip-nameless-gaem main.o Entity.o Level.o -lBox2D -lsfml-graphics -lsfml-window -lsfml-system

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
Entity.o:  Entity.cpp Entity.hpp 
	$(CC) $(CFLAGS) -c Entity.cpp

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
Level.o:  Level.cpp Level.hpp
	$(CC) $(CFLAGS) -c Level.cpp

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#
main.o:  main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) wip-nameless-gaem *.o *~
