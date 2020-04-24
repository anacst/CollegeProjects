#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#define bool char
#define ERROR 0
#define SUCCESS 1
#define NOT_FOUND -1

typedef struct Node Node;
typedef struct List List;

List* create_list(void);
List* create_list_vector(int);
bool insert_node(List*, int);
bool remove_node(List*, int);
bool print_list(List*);
bool destroy_list(List*);

#endif
