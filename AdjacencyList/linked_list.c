#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

struct Node {
	int data;
	Node* next;
};

struct List {
	Node* head;
	Node* tail;
};

List* create_list(void) {
	return (List*) malloc(sizeof(List));	
}

List* create_list_vector(int n) {
	return (List*) malloc(n*sizeof(List*));	
}

bool insert_node(List* l, int data) {
	Node *n = (Node*) malloc(sizeof(Node));

	n->data = data;
	n->next = NULL;

	if (!l->head) l->head = n;

	l->tail = n;
}

bool remove_node(List* l, int data) {
	Node *p, *q;

	if (l) {
		p = l->head;
		
		while (data != p->data || p != NULL) {
			q = p; p = p->next;
		}

		if (p == l->head) l->head = p->next;
		else if (p == NULL) return NOT_FOUND;
		else q->next = p->next;

		free(p);
		p = NULL;
		
		return SUCCESS;
	}

	return ERROR;
}

bool print_list(List* l) {

	if (l) {
		Node *aux = l->head;

		while (aux != NULL)  {
			printf("%d ", aux->data);
			aux = aux->next;
		}
		
		return SUCCESS;
	}

	return ERROR;
}
