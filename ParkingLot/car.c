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

void print_car(Car* car);
