#!/usr/bin/make

CC = g++
CFLAGS = -ggdb3 -O2 -Wall -Wunused-variable -fexceptions -g -std=c++11

DIR_OUT = Release
SRC = sbr.cpp
OBJ = sbr.o
OBJ_OUT = $(DIR_OUT)/sbr.o

ifeq ($(OS),Windows_NT)
	TARGET = $(DIR_OUT)/UM-SSII.exe
	RM = del /Q
	RUN_TARGET = ./$(TARGET) BCs-BHs\BC-F.txt BCs-BHs\Config-F.txt BCs-BHs\BH-F1.txt
else
	TARGET = $(DIR_OUT)/UM-SSII
	RM = rm -rf
	RUN_TARGET = ./$(TARGET) BCs-BHs/BC-F.txt BCs-BHs/Config-F.txt BCs-BHs/BH-F1.txt
endif


all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_OUT)

$(OBJ):
	if [ ! -d $(DIR_OUT) ]; then mkdir -p $(DIR_OUT); fi
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ_OUT)

clean:
	$(RM) $(DIR_OUT)

run:
	$(RUN_TARGET)

	
.PHONY: clean all run