#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "car.h"

struct node_ {
	Item* item;
	Node* next;
};

struct list_ {
	Node* first;
	Node* last;
	int size;
};

int read_int() {
	int opt, status;

	status = scanf(" \n%d", &opt);

	if(status)
		return opt;
	else
		return -1;
}

float read_float() {
	float opt;
	int status;

	status = scanf(" \n%f", &opt);

	if(status)
		return opt;
	else
		return -1;
}

int empty (List* l) {
	return (l->size == 0);
}

int size (List* l) {
	return l->size;
}

List* create_list (void) {
	List* l = (List*) malloc(sizeof(List));

	l->first = NULL;
	l->last = NULL;
	l->size = 0;

	return l;
}

void insert_item (Item* new_item, List* l) {
	Node* new = (Node*) malloc(sizeof(Node));

	if (l->first == NULL) //caso lista ainda esteja vazia
		l->first = new;
	else
		l->last->next = new;
	
	l->last = new;
	new->item = new_item;
	new->next = NULL;

	l->size++;
}

void remove_item (int id, List* l) {
	if (empty(l))
		return;

	Node *p, *q;
	p = l->first; 
	q = p;

	while (p != NULL && id != getID(p->item)) {
		q = p; 
		p = p->next;
	}

	if(p == NULL) //caso o item não exista
		return;

	if(l->first == p) //caso item seja o primeiro da lista	
		l->first = p->next;

	if(p->next == NULL) //caso item seja o ultimo da lista
		l->last = q;

	q->next = p->next;

	free(p->item);
	free(p);

	l->size--;

	if(l->size == 0) {
		l->first = NULL;
		l->last = NULL;
	}
}

void print_list (List* l) {
	if (empty(l))
		return;

	Node* p = l->first;
	
	while (p != NULL) {
		print_car(p->item);
		p = p->next;
	}
}

void empty_list (Node* p) {
	if (p != NULL) {
		if (p->next != NULL)
			empty_list(p->next);

		free(p);
		p = NULL;
	}
}

void delete_list (List** l) {
	if(*l == NULL) return;
	empty_list((*l)->first);
	free(*l);
	*l = NULL;
}
