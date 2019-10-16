#include <stdio.h>
#include <stdlib.h>


typedef struct image_ {
	int magic_num;
	int height, length;
	int** matrix;
} Image;

int** allocate_matrix(int m, int n) {
	int** M = (int**) malloc(m*sizeof(int*));
	for (int i = 0; i < m; i++) 
		M[i] = (int*) malloc(n*sizeof(int));
	return M;
}

int median(int v[], int size) {
	int max = v[0];
	for (int i = 1; i < size; i++) {
		if(v[i] > max)
	}
}

void median_filter(int** matrix, int m, int n) {
	int neighbor[8];
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			neighbor[0] = matrix[i-1][j-1];
			neighbor[1] = matrix[i-1][j];
			neighbor[2] = matrix[i-1][j+1];
			neighbor[3] = matrix[i][j];
			neighbor[4] = matrix[i][j];
			neighbor[5] = matrix[i+1][j];
			neighbor[6] = matrix[i+1][j];
			neighbor[7] = matrix[i+1][j];
		
			matrix[i][j] = neighbor[4];
		}
	}

}

void read_file(FILE* file, Image* img) {

	fscanf(file, "%d", &img->magic_num);
	fscanf(file, "%d %d", &img->height, &img->length);
	fscanf(file, "%*d");

	img->matrix = allocate_matrix(img->height, img->length); 	
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->length; j++)
			fscanf(file, "%d", &img->matrix[i][j]);
}

void free_matrix(int** M, int m) {
	for (int i = 0; i < m; i++)
		free(M[i]);
	free(M);
}

Image* open_file(void) {
	char filename[16];
	FILE* image;
	Image* img = (Image*) malloc(sizeof(Image));
	
	scanf("%s", filename);
	image = fopen(filename, "r");
	if(image == NULL) {
		printf("Erro ao abrir imagem");
		return NULL;
	}

	read_file(image, img);

	fclose(image);
	return img;
}

int main(void) {
	Image* img = open_file();

	return 0;
}
