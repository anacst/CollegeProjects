#include "car.h"
#include <stdio.h>
#include <stdlib.h>

struct car_ {
	int license_plate;
	int arrival;
	int departure;
	float descount;
};

Car* create_car(void) {
	return malloc(sizeof(struct car_));
}

void setLicense_plate(int license_plate, Car* car) {
	car->license_plate = license_plate;
}

void setArrival(int arrival, Car* car) {
	car->arrival = arrival;
}

void setDeparture(int departure, Car* car) {
	car->departure = departure;
}


void setDescount(float descount, Car* car) {
	car->descount = descount;
}

int getLicense_plate(Car* car) {
	return car->license_plate;
}

int getArrival(Car* car) {
	return car->arrival;
}

int getDeparture(Car* car) {
	return car->departure;
}

float getDescount(Car* car) {
	return car->descount;
}

void print_car(Car* car);
