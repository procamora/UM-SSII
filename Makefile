#! /usr/bin/make -f
#g++.exe -Wall -fexceptions -g -Igalib247-c2014/galib247-c2014 -c C:/Users/procamora/pablojoserocamora@gmail.com/Universidad/SSII/UM-SSII/nreinas.cpp -o obj/Debug/nreinas.o
#g++.exe -o bin/Debug/UM-SSII.exe obj/Debug/nreinas.o galib247-c2014/galib.a

CC = g++
CFLAGS = -ggdb3 -Wall -Wno-unused -fexceptions -g -std=c++14
LDLIBS = -Igalib247-c2014/galib247-c2014
LIB_COMPILED = galib247-c2014/galib.a
SRC = src/nreinas.cpp

OBJ = nreinas.o
OBJ_OUT = Debug/src/nreinas.o
TARGET = Debug/UM-SSII.exe

OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

all: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ_OUT) $(LIB_COMPILED)

nreinas.o:
	$(CC) $(CFLAGS) $(LDLIBS) -c $(SRC) -o $(OBJ_OUT)

clean:
	cmd //C del $(TARGET)
	#del /s *~ $(OBJECTS) $(TARGET) core
	
.PHONY: clean all