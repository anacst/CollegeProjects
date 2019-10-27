#ifndef COLLECTION_
#define COLLECTION_

  #define ORDERED_LIST 1
  #define LAST_LIST    2
  #define FIRST_LIST   3
  #define BINARY_TREE  4
  #define AVL_TREE     5
  #define SUCCESS      1
  #define ERROR       -1
  #define bool int

  typedef struct node_ NODE;
  typedefstruct c_ COLLECTION;

  COLLECTION* create_collection(int);
  NODE* create_node(int);
  void insert(COLLECTION*, int);
  bool exist(COLLECTION*, int);
  void destroy(COLLECTION*);

#endif
