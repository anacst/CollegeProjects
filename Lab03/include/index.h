#ifndef _INDEX_H_
#define _INDEX_H_

#include <stdio.h>
#include <stdlib.h>

#define bool int
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define SUCESS 1
#define TAM 16
#define DEL '*'
#define END -1
#define INVALID_POS -1
#define NOT_FOUND -1

typedef struct HeaderIndex {
	char status;
	int nRecords;
} IndexHeader;

typedef struct PrimaryIndex {
	int key;
	int rrn;
} PrimaryIndexData;
	
typedef struct SecondaryIndex {
	char key[TAM];
	int top;	
} SecondaryIndexData;

typedef struct InvertedList {
	int data;
	int next;
} InvertedList;

PrimaryIndexData* idx_loadIndex(FILE* fp) {
	PrimaryIndexData *idx = malloc(sizeof(PrimaryIndexData));
	for (int i = 1; i < count; ++i) {
		/* code */
	}
}

void idx_sortIndex(PrimaryIndexData* idx, int low, int high);

bool idx_insertPrimaryIndex(PrimaryIndexData* index, int key, int rrn);

bool idx_createSecundaryIndex();
bool idx_insertSecundaryIndex();

bool idx_removePrimaryIndex();
bool idx_removeSecundaryIndex();

int idx_searchPrimaryKey();
int idx_searchSecondaryKey();

#endif
