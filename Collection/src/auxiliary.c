#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <auxiliary.h>

int* read_integers(const char* file_name, const int n) {
  FILE* f = fopen(file_name, "r");
  int* integers = (int*) malloc(n*sizeof(int));
  for(int i = 0; !feof(f); i++)
    fscanf(f, "%d", &integers[i]);
  fclose(f);
  return integers;
}

void init_time() {
  srand(time(NULL));
  _init = clock();
}

double end_time() {
  _end = clock();
  return ((double) (_end - _init)) / CLOCKS_PER_SEC;
}
