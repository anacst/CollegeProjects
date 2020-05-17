#include <stdio.h>
#include <stdlib.h>
#include <car.h>

struct car_ {
	int license_plate;
	int arrival;
	int departure;
	float descount;
};

CAR* create_car(void) {
	return calloc(1, sizeof(CAR));
}

void setLicense_plate(int license_plate, CAR* car) {
	car->license_plate = license_plate;
}

void setArrival(int arrival, CAR* car) {
	car->arrival = arrival;
}

void setDeparture(int departure, CAR* car) {
	car->departure = departure;
}


void setDescount(float descount, CAR* car) {
	car->descount = descount;
}

int getLicense_plate(CAR* car) {
	return car->license_plate;
}

int getArrival(CAR* car) {
	return car->arrival;
}

int getDeparture(CAR* car) {
	return car->departure;
}

float getDescount(CAR* car) {
	return car->descount;
}

float getPrice(CAR* car) {
	return  ((3 * (car->departure - car->arrival)) - car->descount);
}