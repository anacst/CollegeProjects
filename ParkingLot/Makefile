CC=gcc

INCLUDE=./include
SRC=./src
OBJ=./obj

all: prog

run: prog
	./prog

prog: parking.o stack.o queue.o car.o
	$(CC) -o prog $(SRC)/main.c $(OBJ)/parking.o $(OBJ)/stack.o $(OBJ)/queue.o $(OBJ)/car.o -I$(INCLUDE) -Wall

parking.o:
	$(CC) -c $(SRC)/parking.c -I./$(INCLUDE) -o $(OBJ)/parking.o

stack.o:
	$(CC) -c $(SRC)/stack.c -I./$(INCLUDE) -o $(OBJ)/stack.o

queue.o: 
	$(CC) -c $(SRC)/queue.c -I./$(INCLUDE) -o $(OBJ)/queue.o

car.o:
	$(CC) -c $(SRC)/car.c -I./$(INCLUDE) -o $(OBJ)/car.o
