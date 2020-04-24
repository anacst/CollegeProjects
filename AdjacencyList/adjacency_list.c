#include <stdio.h>
#include <stdlib.h>

#include "adjacency_list.h"
#include "linked_list.h"

List** create_graph(int n) {
	List** g = (List**) malloc(n*sizeof(List*)); 
	for (int i = 0; i < n; i++)
		g[i] = create_list();
	return g;
}

bool insert_edge(List **g, int u, int v) {

	if (g) {
		insert_node(g[u], v);
		insert_node(g[v], u);
		
		return SUCCESS;
	}

	return ERROR;
}

bool remove_edge(List** g, int u, int v) {
	
	if (g) {
		remove_node(g[u], v);
		remove_node(g[v], u);
	
		return SUCCESS;
	}

	return ERROR;
}

bool print_graph(List** g, int n) {
	if (g) {
		for (int i = 0; i < n; i++) {
			printf("%d: ", i);
			print_list(g[i]);
			printf("\n");
		}

		return SUCCESS;
	}

	return ERROR;
}

bool destroy_graph(List** g, int n) {
	if (g) {
		for (int i = 0; i < n; i++) 
		//	destroy_list(g[i]);
		free(g);
		g = NULL;
		return SUCCESS;
	}

	return ERROR;
}
