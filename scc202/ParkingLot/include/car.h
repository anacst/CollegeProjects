#include <stack.h>
#include <queue.h>

typedef struct car_ CAR;

CAR* create_car(void);

void setLicense_plate(int, CAR*);

void setArrival(int, CAR*);

void setDeparture(int, CAR*);

void setDescount(float, CAR*);

int getLicense_plate(CAR*);

int getArrival(CAR*);

int getDeparture(CAR*);

float getDescount(CAR*);

float getPrice(CAR* car);
