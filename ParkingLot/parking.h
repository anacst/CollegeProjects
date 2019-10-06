#ifndef PARKING_H
	#define PARKING_H

	#include "list.h"
	#include "car.h"
	#define MAX1 5
	#define MAX2 10
	
	int parking_full(List*, List*);
	void print_car(Car*);
	int departure_time(int, int);
	Item* check_in(void);
	void check_out();
	void descount();
	List* availability(int, List*, List*);
	int rejection(int, int, int, List*, List*);

#endif
