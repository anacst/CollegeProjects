#include <stdio.h>
#include <stdlib.h>

#include <parking.h>
#include <stack.h>
#include <queue.h>
#include <car.h>

int read_int() {
	int opt, status;

	status = scanf(" \n%d", &opt);

	if(status)
		return opt;
	else
		return -1;
}

float read_float() {
	float opt;
	int status;

	status = scanf(" \n%f", &opt);

	if(status)
		return opt;
	else
		return -1;
}

int occupied (STACK* p1, QUEUE* p2) {
	return size_stack(p1) + size_queue(p2);
}

int parking_full (STACK* p1, QUEUE* p2) {
	return (size_stack(p1) + size_queue(p2) >= 15);
}

int departure_time (int arrival, int stay) {
	int time = arrival + stay;
	if(time > 24) time -= 24;
	return time;
}

ITEM* check_in (void) {
	ITEM* new = create_car();

	printf("\n\n\t\tREGISTRAR CARRO\n\n");
	printf("\tPlaca do carro: ");
	int license_plate = read_int();
	setLicense_plate(license_plate, new);
	
	printf("\tHorário de Chegada: ");
	int arrival = read_int();
	setArrival(arrival, new);

	printf("\tTempo de permanência: ");
	int stay = read_int();
	setDeparture(departure_time(arrival, stay), new); 

	/**
	if(search_item(license_plate) >= 0) {
		printf("Carro já se encontra no estacionamento!"); 
		return NULL;
	}
	**/

	return new;	
}

void check_out (CAR* car) {


}

float descount (CAR* car, STACK* p1, QUEUE* p2) {
	if (((occupied(p1, p2) * 15) / 100) >= 25) { 
		int a = getArrival(car);
		if (a == 9 || a == 12 || a == 15 || a == 18) {
			int x = rand() % occupied(p1, p2);

		}
	}
}

int availability(int departure, STACK* p1, QUEUE* p2) {

	if(empty_stack(p1)) 
		return 1;

	if(empty_queue(p2))
		return 2;

	if(size_stack(p1) < 5) 
		if(departure <= getDeparture(top(p1)));
			return 1;

	if (size_queue(p2) < 10) 
		if(departure >= getDeparture(peek(p2)));
			return 2;

	return 0;
}

int rejection(int arrival, int departure, int availability, STACK* p1, QUEUE* p2) {
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
	if(!availability) {
		printf("Condições de disponibilidade não foram satisfeitas.\n");
		return 1;
	}

	return 0;
}

void print(STACK* p1, QUEUE* p2) {

	printf("\n\n\t\tCARROS REGISTRADOS\n\n");
	printf("\tPlaca| Pátio | Valor\n");
	print_stack(p1);
	print_queue(p2);
}