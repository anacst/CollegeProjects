#ifndef STACK_H
  #define STACK_H

  #include <car.h>
  #define bool char
  #define ERROR 1

    typedef struct stack_ STACK;
    typedef struct node_ NODE;
    typedef struct car_ ITEM;

    STACK* create_stack(void);
    bool push(ITEM*, STACK*);
    ITEM* pop(STACK*);
    ITEM* top(STACK*);
    int size_stack(STACK*);
    bool empty_stack(STACK*);
    void print_stack(STACK*);
    bool search_stack(int x, STACK* s);
    void destroy_stack(STACK**);

#endif
