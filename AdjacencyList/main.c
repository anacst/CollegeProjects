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
		
			case 1: scanf("%d %d", &u, &v);
					insert_edge(graph, u, v);
					break;

			case 2: scanf("%d %d", &u, &v);
					remove_edge(graph, u, v);
					break;

			case 3: print_graph(graph, n);
					break;

			default: break;
		}
	
	}

}
