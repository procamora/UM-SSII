#!/usr/bin/make
#g++.exe -Wall -fexceptions -g -Igalib247-c2014/galib247-c2014 -c src/sudoku.cpp -o Debug/src/sudoku.o
#g++.exe -o Debug/UM-SSII.exe Debug/src/sudoku.o galib247-c2014/galib.a

CC = g++
CFLAGS = -ggdb3 -Wall -Wunused-variable -fexceptions -g -std=c++11

DIR_OUT = Release
LDLIBS = -Igalib247-c2014/galib247-c2014
SRC = sudoku.cpp
OBJ = sudoku.o
OBJ_OUT = $(DIR_OUT)/sudoku.o

ifeq ($(OS),Windows_NT)
	LIB_COMPILED = galib247-c2014/galib_windows.a
	TARGET = $(DIR_OUT)/UM-SSII.exe
	RM = del /Q
	RUN_TARGET = ./$(TARGET) Casos\Caso-A1.txt 100 GARouletteWheelSelector 0.8 0.01
else
	LIB_COMPILED = galib247-c2014/galib_linux.a
	TARGET = $(DIR_OUT)/UM-SSII
	RM = rm -rf
	RUN_TARGET = ./$(TARGET) Casos/Caso-A1.txt 100 GARouletteWheelSelector 0.8 0.01
endif


#OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

all: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ_OUT) $(LIB_COMPILED)

$(OBJ):
	if [ ! -d $(DIR_OUT) ]; then mkdir -p $(DIR_OUT); fi
	$(CC) $(CFLAGS) $(LDLIBS) -c $(SRC) -o $(OBJ_OUT)

clean:
	$(RM) $(DIR_OUT)

run:
	$(RUN_TARGET)

	
.PHONY: clean all run