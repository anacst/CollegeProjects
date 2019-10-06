typedef struct car_ Car;

Car* create_car(void);

void setLicense_plate(int license_plate, Car* car);

void setArrival(int arrival, Car* car);

void setDeparture(int departure, Car* car);

void print_car(Car* car);

