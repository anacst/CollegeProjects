#ifndef _ADJACENCY_LIST_
#define _ADJACENCY_LIST_

#include "linked_list.h"

#define FALSE 0
#define TRUE 1

/**
 * Cria um vetor de lista encadeadas
 * @param 	n 	número de vértices do grafo
 * @return 	g 	endereço do vetor de listas encadeadas
 */
List** create_graph(int);

/**
 * Insere uma aresta no grafo, adicionando o vértice u à lista de adjacência de v
 * e o vértice v à lista de adjacência de u
 * @param 	g 	grafo a ser manipulado
 * @param	u 	vértice
 * @param	v 	vértice
 * @return 	1 caso aresta seja adicionada com sucesso, 0 caso contrário
 */
bool insert_edge(List**, int, int);

/**
 * Verifica se uma aresta já existe no grafo, procurando o vértice v na lista de adjacência de u
 * @param 	g 	grafo a ser manipulado
 * @param	u 	vértice
 * @param	v 	vértice
 * @return 	1 caso aresta já exista no grafo, 0 caso contrário
 */
bool edge_exist(List **, int, int);

/**
 * Remove uma aresta no grafo, apagando o vértice u da lista de adjacência de v
 * e o vértice v da lista de adjacência de u
 * @param 	g 	grafo a ser manipulado
 * @param	u 	vértice
 * @param	v 	vértice
 * @return 	1 caso aresta seja removida com sucesso, 0 caso contrário
 */
bool remove_edge(List**, int, int);

/**
 * Faz impressão do grafo
 * @param 	g 	grafo a ser manipulado
 * @param	n 	número de vértices do grafo
 * @return 	1 caso grafo seja impresso com sucesso, 0 caso contrário
 */
bool print_graph(List**, int);

/**
 * Libera a memória alocada para o grafo
 * @param 	g 	grafo a ser manipulado
 * @param	n 	número de vértices do grafo
 * @return 	1 caso grafo seja apagado com sucesso, 0 caso contrário
 */
bool destroy_graph(List**, int);

#endif
