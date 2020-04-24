#include "student.h"
#include "index.h"

#define bool int
#define SUCESS 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

RegisterHeader* reg_readHeader(FILE* fp) {
	RegisterHeader *h;

	fseek(fp, 0, SEEK_SET);
	fread(h, sizeof(RegisterHeader), 1, fp);

	return h;
}

void reg_writeHeader(FILE* fp, RegisterHeader* h) {
	fseek(fp, 0, SEEK_SET);
	fwrite(h, sizeof(RegisterHeader), 1, fp);
}

bool reg_insertRegister(FILE* fp, PrimaryIndexData* primaryIndex, SecondaryIndexData* surnameIndex, InvertedList* ) {
	Student r;
	RegisterHeader h = reg_readHeader(fp);
	int primaryKey, secondaryKey, rrn;

	// Cria novo registro
	r = createStudent();

	// Checa se chave primária já existe
	if (index_searchPrimaryKey(primaryKey) != NOT_FOUND) return ERROR;

	// Incrementa contagem de registros
	h.nRegisters++;

	// Define chaves e rrn
	primaryKey = getNusp(r);
	secondaryKey = getSurname(r);
	rrn = h.nRegisters;

	// Posiciona arquivo físico na posição a ser inserido o próximo registro
	fseek(fp, 0, SEEK_END);		

	// Inserir registro no arquivo
	fwrite(&r, sizeof(r), 1, fp);

	// Atualizar vetor de indíces primários
	insertPrimaryIndex(primaryIndex, primaryKey, rrn);

	// Atualizar vetor de indíces secundários
	insertSecondaryIndex(surnameIndex, secondaryKey, primaryKey);

	// Update header
	reg_writeHeader(fp, &h);

	return SUCESS;
}

int reg_searchRegister(FILE* fp, PrimaryIndexData* index, int key) {

	int rrn, byteoffset;

	rrn = index_searchPrimaryKey(idx, key, 1, ??);

	if (rrn == NOT_FOUND) return NOT_FOUND;
	else return rrn*sizeof(Student) + sizeof(HeaderIndex);
}
