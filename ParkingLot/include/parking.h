#ifndef PARKING_H
	#define PARKING_H

	#include <stack.h>
	#include <queue.h>
	#include <car.h>
	#define MAX1 5
	#define MAX2 10
	
	int parking_full(STACK*, QUEUE*);
	int departure_time(int, int);
	ITEM* check_in(STACK*, QUEUE*);
	void check_out();
	float descount(CAR*, STACK*, QUEUE*);
	int availability(int, STACK*, QUEUE*);
	int rejection(int, int, int, STACK*, QUEUE*);
	void print(STACK* p1, QUEUE* p2);

#endif
