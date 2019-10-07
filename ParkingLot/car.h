typedef struct car_ Car;

Car* create_car(void);

void setLicense_plate(int, Car*);

void setArrival(int, Car*);

void setDeparture(int, Car*);

void setDescount(float, Car*);

int getLicense_plate(Car*);

int getArrival(Car*);

int getDeparture(Car*);

float getDescount(Car*);

void print_car(Car*);

