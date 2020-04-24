int readInt() {
	int in, status;

	status = scanf(" %d", &in);

	if(status) return in;
	else return -1;
}

float readFloat() {
	int status;
	float in;

	status = scanf(" %f", &in);

	if(status) return in;
	else return -1;
}

