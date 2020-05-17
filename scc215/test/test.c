#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

#define bool char
#define uint unsigned int

typedef struct {
	int size_motherCity;
	int size_babyCity;
	char motherCity[48];
	char babyCity[49];
	int idBirth;
	int motherAge;
	char birthDate[10];
	char babyGender[1];
	char motherState[2];
	char babyState[2];
} Registry;

#pragma pack(push,1)
typedef struct {
	bool status[1];
	int RRNnextRegistry;
	int numberInsertedRegistries;
	int numberRemovedRegistries;
	int numberUpdatedRegistries;
} FileHeader;
#pragma pack(pop)

int main(int argc, char const *argv[]) {
	char filename[16], binfilename[16];

	scanf("%*d");
	scanf("%s", filename);
	scanf("%s", binfilename);

	FILE *fp = fopen(filename, "r");
	FILE *binfp = fopen(binfilename, "wb");

	Registry r;
	FileHeader h;
	int field_count, i=0, size1, size2;
	char buf[128], header[128];
	char trash = '$';

	fscanf(fp, "%*[^\n]%*c");
	fseek(binfp, 17, SEEK_SET);
	for (int k = 0; k < 111; k++)
			fwrite(&trash, sizeof(char), 1, binfp);

	while (fscanf(fp, "%[^\n]%*c", buf) == 1) {

		char *field = split(buf);
		i++;
	
		field_count = 0;
		while(field_count < 8) {

			switch(field_count) {

				case 0: if (field) strcpy(r.motherCity, field);
						else strcpy(r.motherCity, "");
						break;

				case 1: if (field) strcpy(r.babyCity, field);
						else strcpy(r.babyCity, "");
						break;

				case 2: if (field) r.idBirth = atoi(field);
						else r.idBirth = -1;
						break;

				case 3: if (field) r.motherAge = atoi(field);
						else r.motherAge = -1;
						break;

				case 4: if (field) memmove(r.birthDate, field, 10);
						else memmove(r.birthDate, "\0$$$$$$$$$", 10);
						break;

				case 5: if (field) memmove(r.babyGender, field, 1);
						else memmove(r.babyGender, "0", 1);
						break;

				case 6: if (field) memmove(r.motherState, field, 2);
						else memmove(r.motherState, "\0$", 2);
						break;

				case 7: if (field) memmove(r.babyState, field, 2);
						else memmove(r.babyState, "\0$", 2);
						break;
			}

			field = split(NULL);
			field_count++;
		}

		size1 = strlen(r.motherCity);
		size2 = strlen(r.babyCity);
		fwrite(&size1, sizeof(int), 1, binfp);
		fwrite(&size2, sizeof(int), 1, binfp);
		if (size1) fwrite(&r.motherCity, size1, 1, binfp);		
		if (size2) fwrite(&r.babyCity, size2, 1, binfp);

		for (int k = size1+size2; k < 97; k++)
			fwrite(&trash, sizeof(char), 1, binfp);

		fwrite(&r.idBirth, sizeof(r.idBirth), 1, binfp);
		fwrite(&r.motherAge, sizeof(r.motherAge), 1, binfp);
		fwrite(r.birthDate, sizeof(r.birthDate), 1, binfp);
		fwrite(&r.babyGender, sizeof(r.babyGender), 1, binfp);
		fwrite(r.motherState, sizeof(r.motherState), 1, binfp);
		fwrite(r.babyState, sizeof(r.babyState), 1, binfp);
	}

	strcpy(h.status, "1");
	h.RRNnextRegistry = i;
	h.numberInsertedRegistries = i;
	h.numberRemovedRegistries = 0;
	h.numberUpdatedRegistries = 0;

	fseek(binfp, 0, SEEK_SET);
	fwrite(&h, 17, 1, binfp);

	fclose(fp);
	fclose(binfp);

	binarioNaTela(binfilename);

	return 0;
}