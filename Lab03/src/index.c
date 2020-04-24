#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "index.h"

bool idx_loadIndex();



/* Function to sort index vector using quick sort */
void idx_sortIndex(PrimaryIndexData* idx, int low, int high) {
	int i, j;

	partition(idx, low, high, &i, &j);
	if(low < j-1) sortIndex(idx, low, j-1);
	if(high > i+1) sortIndex(idx, i+1, high);
}

void partition(PrimaryIndexData* idx, int low, int high, int *i, int *j) {
	int pivot = idx[(low + high)/2].key;
	*i = low;
	*j = high;

	do {
		while(idx[*i].key < pivot) {
			(*i)++;
		}
		while(idx[*j].key > pivot) {
			(*j)--;	
		}
		swap(&idx[*i], &idx[*j]);
	} while(*i < *j); 
}

bool idx_insertPrimaryIndex(PrimaryIndexData* idx, int key, int rrn) {
	int pos = idx[0].rrn;

	if (rrn > 0) {
		idx = (PrimaryIndexData*) realloc(idx, (pos+1)*sizeof(PrimaryIndexData));
		idx[pos].key = key;
		idx[pos].rrn = rrn;

		idx_sortIndex(idx, 1, pos);

		return SUCESS;	
	}

	return ERROR; 
}

bool idx_insertSecundaryIndex(SecondaryIndexData* idx, InvertedList* aux, char* secondaryKey, int primaryKey) {
	int s, l, next, pos, i, q;

	s = idx[0].top;			// Proxima posição livre do vetor de indíces secundários
	l = aux[0].next;		// Proxima posição livre da lista invertida
	next = END;				// Posição para qual elemento inserido deve apontar na lista invertida

	// Verifica se chave secundária já foi registrada 
	pos = index_searchSecondaryKey();

	// Caso já esteja registrada, faz iteração por lista invertida corresponde a chave secundária
	if (pos != NOT_FOUND) {
		i = idx[pos].top;	//
		q = INVALID_POS;	//	

		while (primaryKey > aux[i].data) {
			q = i; i = aux[i].next;	
		}

		next = (q == INVALID_POS) ? idx[pos].top : aux[q].next;

		// Se chave primária for inserida no topo da lista invertida,
		// o rrn (top) do index secundário deve ser atualizado		
		if (q == INVALID_POS) l = i; 
	} else {
		idx = (SecondaryIndexData*) realloc(idx, (s+1)*sizeof(SecondaryIndexData));
	}
	
	strcpy(idx[s].key, secondaryKey);
	idx[s].top = l;

	aux = (InvertedList*) realloc(aux, (l+1)*sizeof(InvertedList));
	aux[l].data = primaryKey;
	aux[l].next = next;
}

bool idx_removePrimaryIndex();
bool idx_removeSecundaryIndex();

int idx_searchPrimaryKey(PrimaryIndexData *idx, int key, int low, int high) {
	int mid;
	
	if (low <= high) mid = low+high/2;

	if (key < idx[mid].key) return idx_searchSecondaryKey(idx, key, low, mid-1);
	else if (key > idx[mid].key) return idx_insertPrimaryIndex(idx, key, mid+1);
	else return mid;

	return NOT_FOUND;
}

int idx_searchSecondaryKey();


