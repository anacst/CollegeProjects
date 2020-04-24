all: prog


run: prog
	./prog

prog:  adjacency_list.o linked_list.o main.c
	gcc adjacency_list.o linked_list.o main.c -o prog -Wall

adjacency_list.o: adjacency_list.c
	gcc -c adjacency_list.c

linked_list.o: linked_list.c
	gcc -c linked_list.c
