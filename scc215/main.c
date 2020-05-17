#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registry.h"
#include "utils.h"

bool createBinaryFile(char *filename) {
	FILE *fp = fopen(filename, "wb");

	if(!fp) {
		printf("Erro no carregamento do arquivo.\n");
		return ERROR;
	} else {
	 	initHeader(fp);
	 	fclose(fp);
	 	fp = NULL;
	 	return SUCCESS;
	}
}

FILE* openReadDataFile(char *filename) {
	FILE *fp = fopen(filename, "r");

	if(!fp) printf("Erro no carregamento do arquivo.");
}

FILE* openWriteBinaryFile(char* filename) {
	FILE *fp = fopen(filename, "r+b");

	if(!fp) printf("Erro no carregamento do arquivo.");

	return fp;
}

FILE* openReadBinaryFile(char* filename) {
	FILE *fp = fopen(filename, "rb");
	FileHeader header;

	if(!fp) {
		printf("Falha no processamento do arquivo.");
	} else {
		header = loadHeader(fp);
		printf("aaaaaaaaaaaaaaaaa");
		if (strcmp(header.status,INCONSISTENT))
			printf("Falha no processamento do arquivo.");
		else {
			printf("aaaaaaaaaaaaaaaaa");
			updateHeader(fp, INCONSISTENT);
		}
	}

	return fp;
}

void closeBinaryFile(FILE* fp) {
	if (fp) { 
		updateHeader(fp, CONSISTENT);
		fclose(fp);
		fp = NULL;
	}
}

void writeBinaryFile(char *filenameDataFile, char *filenameBinaryFile) {
	FILE *dataFile, *binaryFile;
	int size_nullValue, rrn, nregs;
	char trash[105], buf[128];
	memset(trash, TRASH, 105);
	FileHeader header;
	Registry r;
	nregs = rrn = 0;
	
	dataFile = openReadDataFile(filenameDataFile);
	binaryFile = openWriteBinaryFile(filenameBinaryFile);

	fscanf(dataFile, "%*[^\n]%*c");
	fseek(binaryFile, sizeof(FileHeader)+111, SEEK_SET);

	while (readRegistry(dataFile, &r) == 1) {

		r.size_motherCity = strlen(r.motherCity);
		r.size_babyCity = strlen(r.babyCity);
		size_nullValue = MAX_VAR_FIELD - (r.size_motherCity + r.size_babyCity);

		fwrite(&r.size_motherCity, sizeof(int), 1, binaryFile);
		fwrite(&r.size_babyCity, sizeof(int), 1, binaryFile);
		if (r.size_motherCity) fwrite(&r.motherCity, r.size_motherCity, 1, binaryFile);
		if (r.size_babyCity) fwrite(&r.babyCity, r.size_babyCity, 1, binaryFile);
		fwrite(&trash, size_nullValue, 1, binaryFile);

		fwrite(&r.idBirth, sizeof(r.idBirth), 1, binaryFile);
		fwrite(&r.motherAge, sizeof(r.motherAge), 1, binaryFile);
		fwrite(r.birthDate, sizeof(r.birthDate), 1, binaryFile);
		fwrite(&r.babyGender, sizeof(r.babyGender), 1, binaryFile);
		fwrite(r.motherState, sizeof(r.motherState), 1, binaryFile);
		fwrite(r.babyState, sizeof(r.babyState), 1, binaryFile);

		nregs++;
		rrn++;
	}

	memmove(header.status, INCONSISTENT, 1);
	header.RRNnextRegistry = rrn;
	header.numberInsertedRegistries = nregs;
	header.numberRemovedRegistries = 0;
	header.numberUpdatedRegistries = 0;
	writeHeader(binaryFile, header);

	fclose(dataFile);
	closeBinaryFile(binaryFile);
}

void printBinaryFile(char *filename) {
	FILE *fp = openReadBinaryFile(filename);
	if (!fp) return;
	FileHeader header = loadHeader(fp);
	char city[50], state[3], birth[11], gender[10];
	int numberRegistries, size_trash;
	Registry r;

	// Retorna caso não exista registros no arquivo
	if (!header.numberInsertedRegistries) {
		printf("Registro inexistente.");
		return;
	}

	numberRegistries = header.numberInsertedRegistries;

	for (int i = 0; i < numberRegistries; i++) {
		fread(&r.size_motherCity, sizeof(int), 1, fp);
		fread(&r.size_babyCity, sizeof(int), 1, fp);
		fread(r.motherCity, r.size_motherCity, 1, fp);
		fread(r.babyCity, r.size_babyCity, 1, fp);
		size_trash = MAX_VAR_FIELD - (r.size_motherCity + r.size_babyCity);

		fseek(fp, size_trash, SEEK_CUR);
		fseek(fp, 8, SEEK_CUR);
		fread(r.birthDate, sizeof(r.birthDate), 1, fp);
		fread(r.babyGender, sizeof(r.babyGender), 1, fp);
		fseek(fp, 2, SEEK_CUR);
		fread(r.babyState, sizeof(r.babyState), 1, fp);

		// Copying name of city and state
		if (r.size_babyCity == 0) {
			strcpy(city, "-");
		} else {
			memmove(city, r.babyCity, r.size_babyCity); 
			city[r.size_babyCity] = '\0';
		}
		
		if (r.babyState[0] == '\0') {
			strcpy(state, "-");
		} else {
			memmove(state, r.babyState, 2);
			state[2] = '\0';
		}

		if (r.birthDate[0] == '\0') {
			strcpy(birth, "-");
		} else { 
			memmove(birth, r.birthDate, 10); 
			birth[10] = '\0';
		}

		if (r.babyGender[0] == IGNORED) strcpy(gender, "IGNORADO");
		else if (r.babyGender[0] == MALE) strcpy(gender, "MASCULINO");
		else strcpy(gender, "FEMININO");

		printf("Nasceu em %s/%s, em %s, um bebê de sexo %s.\n", city, state, birth, gender);
	}

	fclose(fp);
}

int main(int argc, char const *argv[]) {
	int op;
	scanf("%d", &op);
	char filenameCSVFile[20];
	char filenameBinaryFile[20];

	switch(op) {

		case 1: scanf("%s %s", filenameCSVFile, filenameBinaryFile);
				createBinaryFile(filenameBinaryFile);
				writeBinaryFile(filenameCSVFile, filenameBinaryFile);
				binarioNaTela(filenameBinaryFile);
				break;

		case 2: scanf("%s", filenameBinaryFile);
				printBinaryFile(filenameBinaryFile);
				break;

	}

	return 0;
}