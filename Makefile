 #! /usr/bin/make -f
#g++.exe -Wall -fexceptions -g -Igalib247-c2014/galib247-c2014 -c C:/Users/procamora/pablojoserocamora@gmail.com/Universidad/SSII/UM-SSII/nreinas.cpp -o obj/Debug/nreinas.o
#g++.exe -o bin/Debug/UM-SSII.exe obj/Debug/nreinas.o galib247-c2014/galib.a

CC = g++
CFLAGS = -ggdb3 -Wall -Wno-unused -fexceptions -g -std=c++14
LDLIBS = -Igalib247-c2014/galib247-c2014
SRC = src/sudoku.cpp
OBJ = nreinas.o
OBJ_OUT = Debug/src/sudoku.o

ifeq ($(OS),Windows_NT)
LIB_COMPILED = galib247-c2014/galib.a
TARGET = Debug/UM-SSII.exe
RM = del /Q
else
LIB_COMPILED = galib247-c2014/galib_linux.a
TARGET = Debug/UM-SSII
RM = rm -f
endif


OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

all: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ_OUT) $(LIB_COMPILED)

nreinas.o:
	$(CC) $(CFLAGS) $(LDLIBS) -c $(SRC) -o $(OBJ_OUT)

clean:
	$(RM) $(call TARGET)
	$(RM) $(call OBJ_OUT)

	
.PHONY: clean all