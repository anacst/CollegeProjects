#ifndef LIST_H
    #define LIST_H

    typedef struct car_ Item;
    typedef struct node_ Node;
    typedef struct list_ List;
    
    int read_int();
    
    float read_float();
    
    /* Função que determina se lista está vazia */
    int empty (List*);

	int size (List*);		

    /* Função para inicialização de uma lista */
    List* create_list (void);
    
    /* Função para inserção de registro */
    void insert_item (Item*, List*);

    /* Função para remoção de registro a partir de ID */
    void remove_item (int, List*);
    
    /* Função para impressão de todos os registros */
    void print_list (List*);
    
    /* Função que libera nós da lista recursivamente */
    void empty_list(Node*);

    /* Função que apaga toda a lista */
    void delete_list(List**);

#endif
