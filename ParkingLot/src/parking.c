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

ITEM* check_in (STACK* p1, QUEUE* p2) {
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

	
	if(search_stack(license_plate, p1) || search_queue(license_plate, p2)) {
		printf("\n\tCarro já se encontra no estacionamento!"); 
		return NULL;
	}

	return new;	
}

void check_out (CAR* car, STACK* p1, QUEUE* p2) {
	CAR* removed;

	if((!empty_stack(p1) && (getArrival(car) >= getDeparture(top(p1)))) || 
			(!empty_queue(p2) && getArrival(car) >= getDeparture(peek(p2)))) {
		printf("\n\n\t\tCARROS REMOVIDOS\n");
		printf("\n\t|  Placa  |  Valor  |\n");
		printf("\t|-------------------|\n");
	}
	
	while(!empty_stack(p1) && getArrival(car) >= getDeparture(top(p1))) {
		removed = pop(p1);
		printf("\t|  %d   |  %.2f   |\n", getLicense_plate(removed), getPrice(removed));
		free(removed);
	}

	while(!empty_queue(p2) && getArrival(car) >= getDeparture(peek(p2))) {
		removed = dequeue(p2);
		printf("\t|  %d   |  %.2f   |\n", getLicense_plate(removed), getPrice(removed));
		free(removed);
	}
}

float descount (CAR* car, STACK* p1, QUEUE* p2, int size) {

	if (((size * 100) / 15) < 25)
		return 0;

    CAR* cars[15];
    STACK *aux_stack = create_stack();
    CAR* aux;
    int i = 0;
    int a = getArrival(car);
    int x = rand() % size; //ao usar % para sortear o carro, não é necessário tratar a fila como circular
    printf("%d\n", x);

    //colocando carros do estacionamento PILHA na lista:
    while(!empty_stack(p1)) {
    	aux = pop(p1);
    	cars[i++] = aux;
    	push(aux, aux_stack);
    }                
  
    while(!empty_stack(aux_stack)) //reempilhando
        push(pop(aux_stack), p1);
    

    //colocando carros do estacionamento FILA na lista:
    while(i < size) {
        aux = dequeue(p2);
        enqueue(aux, p2); //tira o carro do inicio da fila e devolve ele para o fim
        cars[i++] = aux;
    }

	if (a == 9 || a == 12 || a == 15 || a == 18)
     	setDescount((0.1 * getPrice(aux)), aux);

	printf("\n\tO carro %d foi sorteado!\n", getLicense_plate(cars[x]));
	destroy_stack(&aux_stack);
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
		printf("\n\tEstacionamento está cheio.\n");	
		return 1;
	}
	if(arrival < 8 || arrival > 22) {
		printf("\n\tEstacionamento está fechado.\n");
		return 1;
	}
	if(departure < 8 || departure > 22) {
		printf("\n\tEstacionamento estará fechado no horário previsto de saída.\n");
		return 1;
	}
	if(!availability) {
		printf("\n\tCondições de disponibilidade não foram satisfeitas.\n");
		return 1;
	}

	return 0;
}

void print(STACK* p1, QUEUE* p2) {

	printf("\n\n\t\tCARROS REGISTRADOS\n\n");
	printf("\t|  Placa  |  Pátio  |  Valor  |\n");
	printf("\t|-----------------------------|\n");
	print_stack(p1);
	print_queue(p2);
}