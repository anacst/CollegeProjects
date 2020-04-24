#ifndef _ADJACENCY_LIST_
#define _ADJACENCY_LIST_

#include "linked_list.h"

List** create_graph(int);
bool insert_edge(List**, int, int);
bool remove_edge(List**, int, int);
bool print_graph(List**, int);
bool destroy_graph(List**, int);

#endif
