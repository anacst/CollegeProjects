/*
 * @file linked_list.c
 * @author Ana Costa
 * @date 18 Setembro 2019
 * @brief Implementação de Lista Encadeada
**/

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
	List *l = (List*) malloc(sizeof(List));
	l->head = l->tail = NULL;
	return l;
}

bool insert_node(List* l, int data) {
	Node *n = (Node*) malloc(sizeof(Node));

	if (!l->head) l->head = l->tail = n;

	l->tail->next = n;
	l->tail = n;

	n->data = data;
	n->next = NULL;
}

Node* search_node(List* l , int data) {
	Node *p, *q;

	if (l) {
		p = l->head;
		
		while (p != NULL) {
			if (data != p->data) {
				q = p; p = p->next;
			} else {
				break;
			}
		}

		return p;
	}

	return NULL;
}

bool remove_node(List* l, int data) {
	Node *p, *q;

	if (l) {
		p = l->head;
		
		while (p != NULL && data != p->data) {
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

bool destroy_list(List* l) {
	Node *p, *q;

	if (l) {
		p = l->head;
		q = NULL;

		while (p != NULL)  {
			q = p; p = p->next;
			free(q);
		}

		free(l);
		l = NULL;
		
		return SUCCESS;
	}

	return ERROR;
}
