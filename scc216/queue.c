#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	Node *next;
} Node;

typedef struct {
	Node *front;
	Node *rear;
} Queue;


Queue* queue_create() {
	Queue *Q = (Queue *) malloc(sizeof(Queue));
	Q->front = Q->rear = NULL;
	return Q;
}

int queue_empty(Queue *Q) {
	return (Q->front == NULL);
}

void queue_enqueue(Queue *Q, int data) {
	if (!Q) return INVALID_ARGUMENT;

	Node *n = (Node *) malloc(sizeof(Node));
	n->data = data;
	n->next = NULL;
	Q->rear->next = n;	
}

Node* queue_dequeue(Queue *Q) {
	Node *n = Q->front;
	Q->front = Q->front->next;
	return n;
}

void queue_destroy(Queue *Q) {
	Node *n;
	while(!queue_empty(Q)) {
		n = queue_dequeue(Q);
		free(n);
	}

	free(Q);
	n = NULL;
	Q = NULL;
}
