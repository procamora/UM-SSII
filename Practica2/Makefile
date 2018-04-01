#!/usr/bin/make -f
#g++.exe -Wall -fexceptions -g -Igalib247-c2014/galib247-c2014 -c src/sudoku.cpp -o Debug/src/sudoku.o
#g++.exe -o Debug/UM-SSII.exe Debug/src/sudoku.o galib247-c2014/galib.a

CC = g++
CFLAGS = -ggdb3 -Wall -Wunused-variable -fexceptions -g -std=c++11
SRC = sbr.cpp
OBJ = sbr.o
OBJ_OUT = ../Debug/src/sbr.o

ifeq ($(OS),Windows_NT)
	TARGET = ../Debug/UM-SSII.exe
	RM = del /Q
	RUN_TARGET = ./$(TARGET) BCs-BHs\BC-F.txt BCs-BHs\Config-F.txt BCs-BHs\BH-F1.txt
else
	TARGET = ../Debug/UM-SSII
	RM = rm -f
	RUN_TARGET = ./$(TARGET) BCs-BHs/BC-F.txt BCs-BHs/Config-F.txt BCs-BHs/BH-F1.txt
endif


all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_OUT)

$(OBJ):
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ_OUT)

clean:
	$(RM) $(call TARGET)
	$(RM) $(call OBJ_OUT)

run:
	$(RUN_TARGET)

	
.PHONY: clean all run