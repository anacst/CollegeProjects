#ifndef _REGISTRY_H_
#define _REGISTRY_H_

#define bool char
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define SUCCESS 1
#define TRASH '$'
#define INCONSISTENT "0"
#define CONSISTENT "1"
#define IGNORED '0'
#define MALE '1'
#define FEMININE '2'
#define BUFFER_SIZE 258
#define SIZE_TRASH_HEADER 111
#define MAX_VAR_FIELD 97
#define uint unsigned int

#pragma pack(push,1)
typedef struct {
	bool status[1];
	uint RRNnextRegistry;
	uint numberInsertedRegistries;
	uint numberRemovedRegistries;
	uint numberUpdatedRegistries;
} FileHeader;
#pragma pack(pop)

typedef struct {
	uint size_motherCity;
	uint size_babyCity;
	char motherCity[48];
	char babyCity[49];
	int idBirth;
	int motherAge;
	char birthDate[10];
	char babyGender[1];
	char motherState[2];
	char babyState[2];
} Registry;

void initHeader(FILE*);
FileHeader loadHeader(FILE*);
void updateHeader(FILE*, char*);
int readRegistry(FILE*, Registry*);
void writeHeader(FILE*, FileHeader);

#endif