#include <stdio.h>
#include <stdlib.h>
#include <stack.h>

struct stack_ {
  int size;
  NODE* top;
};

struct node_ {
  ITEM* data;
  NODE* prev;
};

STACK* create_stack(void) {
  return calloc(1, sizeof(STACK));
}

bool push(ITEM* x, STACK* s) {
  NODE* new = (NODE*)malloc(sizeof(NODE));
  if(new) {
    new->data = x;
    new->prev = s->top;
    s->top = new;
    s->size++;
    return (1);
  }
  return ERROR;
}

ITEM* pop(STACK* s) {
  if(s && !empty_stack(s)) {
    ITEM* tmp = s->top->data;
    s->top->prev = NULL;
    free(s->top);
    s->top = s->top->prev;
    s->size--;
    return tmp; //Não vai ter apagado o conteúdo do item no free?
  }
  return NULL;
}

ITEM* top(STACK* s) {
  return ((s) && !empty_stack(s) ? s->top->data : NULL);
}

int size_stack(STACK* s) {
  return ((s) ? s->size : ERROR);
}

bool empty_stack(STACK* s) {
  return (s->size == 0);
}

void print_stack(STACK* s) {
  for(NODE* p = s->top; p != NULL; p = p->prev)
     printf("\t%d\t1\t\n", getLicense_plate(p->data));
}

void destroy_stack(STACK** s) {
  if(s && !empty_stack(*s)) {
    while((*s)->top != NULL) {
      NODE* aux = (*s)->top;
      (*s)->top = (*s)->top->prev;
      free(aux->data);
      aux->prev = NULL;
      free(aux);
      aux = NULL;
    }
  }
  (*s)->top = NULL;
  free(*s);
  *s = NULL;
}
