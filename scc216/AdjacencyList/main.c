#include <stdio.h>

#include "adjacency_list.h"

int main() {
	int n, m, q, u, v, op;
	List** graph; 

	scanf("%d %d", &n, &m);

	graph = create_graph(n);

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		insert_edge(graph, u, v);
	} 
	
	scanf("%d", &q);

	while (q > 0) {
	
		scanf("%d", &op);
		
		switch(op) {
		
			case 1: //Insere nova aresta
					scanf("%d %d", &u, &v);
					insert_edge(graph, u, v);
					break;

			case 2: //Remove aresta 
					scanf("%d %d", &u, &v);
					remove_edge(graph, u, v);
					break;

			case 3: //Faz impressão do grafo
					print_graph(graph, n);
					break;

			default: break;
		}

		q--;
	}

	destroy_graph(graph, n);
}
