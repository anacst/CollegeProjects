#include <stdio.h>
#include <stdlib.h>
#include "parking.h"
#include "list.h"

void register_car (List* p1, List* p2) {
	int cond;
	Item* new_car = check_in();
	
	check_out();
	
	List* p = availability(getDeparture(new_car), p1, p2);
	if(!p) cond = 0;
	else cond = 1; 
	
	if(rejection(getArrival(new_car), getDeparture(new_car), cond, p1, p2))
		return;

	insert_item(new_car, p);	
}

void print_cars (List* p1, List* p2) {
	printf("Placa\t| Pátio | Valor\n");
	print_list(p1);
	print_list(p2);
}

void options (void) {
	
	List* parking_lot_1 = create_list();
	List* parking_lot_2 = create_list();
	int op = read_int();

	switch(op) {
		case 1: register_car(parking_lot_1, parking_lot_2);
			break;

		case 2: print_cars(parking_lot_1, parking_lot_2);
			break;
	
		case 3:
			exit(0);
			break;

	}	
}

void menu() {

	printf("\n\n");
	printf("\t\t\tMENU\n\n");
	printf("\t(1) Registrar Carro\n");
	printf("\t(2) Imprimir Carros\n");
	printf("\t(1) Sair\n");
	printf("\n\tSelecione uma opção");
	
	options();
}

int main (void) {
	menu();
	return 0;
}
