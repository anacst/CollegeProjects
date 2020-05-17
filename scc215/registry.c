#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registry.h"
#include "utils.h"

void initHeader(FILE* fp) {
	FileHeader header;
	char trash[111];
	memset(trash, TRASH, 111);

	memmove(header.status, INCONSISTENT, 1);
	header.RRNnextRegistry = 0;
	header.numberInsertedRegistries = 0;
	header.numberRemovedRegistries = 0;
	header.numberUpdatedRegistries = 0;

	fwrite(&header, sizeof(FileHeader), 1, fp);
	fwrite(trash, sizeof(trash), 1, fp);
}

FileHeader loadHeader(FILE* fp) {
	FileHeader header;

	fseek(fp, 0, SEEK_SET);
	fread(&header, sizeof(header), 1, fp);
	fseek(fp, SIZE_TRASH_HEADER, SEEK_CUR);

	return header;
}

void writeHeader(FILE* fp, FileHeader header) {
	if (fp) {
		fseek(fp, 0, SEEK_SET);
		fwrite(&header, sizeof(FileHeader), 1, fp);
	}
}

void updateHeader(FILE* fp, char* status) {
	if(fp) {
		fseek(fp, 0, SEEK_SET);
		fwrite(status, sizeof(char), 1, fp);
	}
}

int readRegistry(FILE *fp, Registry* r) {
	int field_count;
	char *field, buf[BUFFER_SIZE];

	if (fscanf(fp, "%[^\n]%*c", buf) == 1) {
		
		field_count = 0;
		field = split(buf);
		
		while(field_count < 8) {

			switch(field_count) {

				case 0: if (field) strcpy(r->motherCity, field);
						else strcpy(r->motherCity, "");
						break;

				case 1: if (field) strcpy(r->babyCity, field);
						else strcpy(r->babyCity, "");
						break;

				case 2: if (field) r->idBirth = atoi(field);
						else r->idBirth = -1;
						break;

				case 3: if (field) r->motherAge = atoi(field);
						else r->motherAge = -1;
						break;

				case 4: if (field) memmove(r->birthDate, field, 10);
						else memmove(r->birthDate, "\0$$$$$$$$$", 10);
						break;

				case 5: if (field) memmove(r->babyGender, field, 1);
						else memmove(r->babyGender, "0", 1);
						break;

				case 6: if (field) memmove(r->motherState, field, 2);
						else memmove(r->motherState, "\0$", 2);
						break;

				case 7: if (field) memmove(r->babyState, field, 2);
						else memmove(r->babyState, "\0$", 2);
						break;
			}

			field = split(NULL);
			field_count++;
		}
		return 1;	
	}

	return 0;
}