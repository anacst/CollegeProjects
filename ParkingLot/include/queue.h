#ifndef QUEUE_H
  #define QUEUE_H

  #include <car.h>
  #define bool char
  #define ERROR 0

  typedef struct queue_ QUEUE;
  typedef struct node_ NODE;
  typedef struct car_ ITEM;

  QUEUE* create_queue(void);
  bool enqueue(ITEM*, QUEUE*);
  ITEM* dequeue(QUEUE*);
  ITEM* peek(QUEUE*);
  int size_queue(QUEUE*);
  bool empty_queue(QUEUE*);
  void print_queue(QUEUE*);
  void destroy_queue(QUEUE**);

#endif
