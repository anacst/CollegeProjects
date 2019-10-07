#include <stdio.h>
#include "parking.h"
#include "list.h"
#include "car.h"

int occupied (List* p1, List* p2) {
	return size(p1) + size(p2);
}

int parking_full (List* p1, List* p2) {
	return (p1->size + p2->size >= 15);
}

int departure_time (int arrival, int stay) {
	int time = arrival + stay;
	if(time > 24) time -= 24;
	return time;
}

Item* check_in (void) {
	Item* new = create_car();

	printf("\n\tPlaca do carro: ");
	int license_plate = read_int();
	setLicense_plate(license_plate, new);
	
	printf("\n\tHorário de Chegada: ");
	int arrival = read_int();
	setArrival(arrival, new);

	printf("\n\tTempo de permanência: ");
	int stay = read_int();
	setDeparture(departure_time(arrival, stay), new); 

	if(search_item(license_plate) >= 0) {
		printf("Carro já se encontra no estacionamento!"); 
		return NULL;
	}
	
	return new;	
}

void check_out (Car* car) {


}

float descount (Car* car, List* p1, List* p2) {
	if (((occupied(p1, p2) * 15) / 100) >= 25) { 
		int a = getArrival(car);
		if (a == 9 || a == 12 || a == 15 || a == 18) {
			int x = rand() % occupied(p1, p2);
	
		}
	}
}

List* availability(int departure, List* p1, List *p2) {
	if(empty(p1)) {
		return p1;
	} else if(empty(p2)) {
		return p2;
	} else if(size(p1) < 5) {
		if(departure <= getDeparture(p1->first));
			return p1;
	} else if (size(p2) < 10) {
		if(departure >= getDeparture(p2->last));
			return p2;
	} else return NULL;
}

int rejection(int arrival, int departure, int availability, List* p1, List* p2) {
	if(parking_full(p1, p2)) {
		printf("Estacionamento está cheio.");	
		return 1;
	}
	if(arrival < 8 || arrival > 22) {
		printf("Estacionamento está fechado.\n");
		return 1;
	}
	if(departure < 8 || departure > 22) {
		printf("Estacionamento estará fechado no horário previsto de saída.\n");
		return 1;
	}
	if(availability) {
		printf("Condições de disponibilidade não foram satisfeitas.\n");
		return 1;
	}

	return 0;
}


