/*
 * @file adjacency_list.c
 * @author Ana Costa
 * @date 8 Abril 2020
 * @brief Implementação de uma Lista de Adjacências para
 * representação de um grafo atráves de listas encadeadas
**/

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

	if (g) { //Verifica se grafo existe

		//Verifica se aresta a ser inserida já existe no grafo
		if (edge_exist(g, u, v)) 
			return ERROR;

		insert_node(g[u], v);
		insert_node(g[v], u);
		
		return SUCCESS;
	}

	return ERROR;
}

bool edge_exist(List **g, int u, int v) {

	if (g) { //Verifica se grafo existe
	
		if (search_node(g[u], v))
			return TRUE;	
		else
			return FALSE;
	}
}

bool remove_edge(List** g, int u, int v) {
	
	if (g) { //Verifica se grafo existe

		//Verifica se aresta a ser removida existe
		if (!edge_exist(g, u, v)) 
			return ERROR;

		remove_node(g[u], v);
		remove_node(g[v], u);
	
		return SUCCESS;
	}

	return ERROR;
}

bool print_graph(List** g, int n) {

	if (g) { //Verifica se grafo existe
		for (int i = 0; i < n; i++) {
			printf("%d: ", i);
			print_list(g[i]);
			printf("\n");
		}
		printf("\n");

		return SUCCESS;
	}

	return ERROR;
}

bool destroy_graph(List** g, int n) {

	if (g) { //Verifica se grafo existe
		for (int i = 0; i < n; i++) 
			destroy_list(g[i]);
		free(g);
		g = NULL;
		return SUCCESS;
	}

	return ERROR;
}
