#!/usr/bin/make -f
#g++.exe -Wall -fexceptions -g -Igalib247-c2014/galib247-c2014 -c src/sudoku.cpp -o Debug/src/sudoku.o
#g++.exe -o Debug/UM-SSII.exe Debug/src/sudoku.o galib247-c2014/galib.a

CC = g++
CFLAGS = -ggdb3 -Wall -Wunused-variable -fexceptions -g -std=c++14
LDLIBS = -Igalib247-c2014/galib247-c2014
SRC = Practica1/sudoku.cpp
OBJ = sudoku.o
OBJ_OUT = Debug/src/sudoku.o

ifeq ($(OS),Windows_NT)
	LIB_COMPILED = galib247-c2014/galib_windows.a
	TARGET = Debug/UM-SSII.exe
	RM = del /Q
	RUN_TARGET = ./$(TARGET) Practica1\Casos\Caso-A1.txt 100 GARouletteWheelSelector 0.8 0.01
else
	LIB_COMPILED = galib247-c2014/galib_linux.a
	TARGET = Debug/UM-SSII
	RM = rm -f
	RUN_TARGET = ./$(TARGET) Practica1/Casos/Caso-A1.txt 100 GARouletteWheelSelector 0.8 0.01
endif


OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))

all: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ_OUT) $(LIB_COMPILED)

$(OBJ):
	$(CC) $(CFLAGS) $(LDLIBS) -c $(SRC) -o $(OBJ_OUT)

clean:
	$(RM) $(call TARGET)
	$(RM) $(call OBJ_OUT)

run:
	./$(TARGET) Practica1/Casos/Caso-A1.txt 100 GARouletteWheelSelector 0.8 0.01
	#$(RUN_TARGET)

	
.PHONY: clean all run