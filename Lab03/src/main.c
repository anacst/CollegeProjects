/**
 * @file 
 * @author
 * @date
 * @brief
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define bool int
#define FALSE 0
#define TRUE 1
#define TAM 16
#define DEL '*'
#define END -1
#define DATA_FILE 0
#define PRIMARY_INDEX_FILE 1
#define SECONDARY_INDEX_FILE 2

int menu() {
	int opt;

	printf("\n\n\t\tMENU\n\n");
	printf("\t(1) Gravar registro\n");
	printf("\t(2) Pesquisar registro\n");
	printf("\t(3) Remover registro\n");
	printf("\t(0) Finalizar\n");
	printf("\n\tDigite uma opção: ");

	opt = readInt();

	while(opt < 0 || opt > 4) {
		printf("\tSelecione uma opção válida: ");
		opt = readInt();
	}

	return opt;
}

void options(int opt) {

	switch (opt) {
	
		case 1: insertRecord();
				break;

		case 2: searchRecord();
				break;

		case 3: removeRecord();
				break;

		case 0: end();
				break;
	
	}

}

void createFile(FILE* fp, char fileType) {
	char fileName[16];

	if (fileType == DATA_FILE) {
		fileName = "alunos.dad";
	} else if (fileType == PRIMARY_INDEX_FILE) {
		fileName = "index_prim.dad";
	} else if (fileType == SECONDARY_INDEX_FILE) {
		fileName = "index_sec.dad";
	}

	if (fp == NULL) {
		fp = fopen(fileName, "w");
		fclose(fp);
		fp = NULL;
	}
}

int main() {
	FILE *dataFile, *primaryIndexFile, *secondaryIndexFile;

	do {
		

	} while (dataFile == NULL && primaryIndexFile == NULL && searchRecord == NULL)
	return 0;
}
