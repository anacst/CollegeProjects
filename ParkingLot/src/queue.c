#include <stdio.h>
#include <stdlib.h>
#include <queue.h>

struct queue_ {
  NODE* front;
  NODE* rear;
  int size;
};

struct node_ {
  ITEM* data;
  NODE* next;
};

QUEUE* create_queue(void) {
    return calloc(1, sizeof(QUEUE));
}

bool enqueue(ITEM* x, QUEUE* q) {
  NODE* new = (NODE*)malloc(sizeof(NODE));
  if(new) {
    new->data = x;
    if(empty_queue(q))
      q->front = q->rear = new;
    else
      q->rear->next = new;
    q->rear = new;
    q->rear->next = NULL;
    q->size++;
    return (1);
  }
  return ERROR;
}

ITEM* dequeue(QUEUE* q) {
  if((q) && !empty_queue(q)) {
    ITEM* tmp = q->front->data;
    q->front->next = NULL;
    free(q->front);
    q->front = q->front->next;
    q->size--;
    return tmp;
  }
  return NULL;
}

ITEM* peek(QUEUE* q) {
  return ((q) && !empty_queue(q) ? q->front->data : NULL);
}

int size_queue(QUEUE* q) {
  return ((q) ? q->size : ERROR);
}

bool empty_queue(QUEUE* q) {
  return ((q) ? q->size == 0 : ERROR);
}

void print_queue(QUEUE* q) {

  for(NODE* p = q->front; p != NULL; p = p->next)
    printf("\t%d\t2\t\n", getLicense_plate(p->data));

}

void destroy_queue(QUEUE** q) {
  if((q) && !empty_queue(*q)) {
    while ((*q)->front != NULL) {
      NODE* aux = (*q)->front;
      (*q)->front = (*q)->front->next;
      free(aux->data);
      aux->next = NULL;
      free(aux);
      aux = NULL;
    }
  }
  (*q)->front = NULL;
  (*q)->rear = NULL;
  free(*q);
  *q = NULL;
}
