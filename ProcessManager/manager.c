/* @authors	Ana Laura Chioca, #
			Ana Luisa Teixeira Costa, #11218963
			Flavio Salles, #11218809
			Thales Willian Dalvi da Silva, #11219196
			Nathy
	@brief Trabalho de gerenciador de processos feito para discplina de ICC.
			Utilizamos uma lista duplamente encadeada para gerenciar os processos,
			adicionando-os ordenamente e chamando a função de ordenação apenas
			quando alteramos um processo.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCR 50

typedef struct schedule Schedule;
typedef struct process Process;
typedef struct node Node;
typedef struct list List;

struct schedule {
	int hh;
	int mm;
	int ss;
};

struct process {
	int prior;
	Schedule arrival;
	char description[MAX_DESCR];
};

struct node {
	Process process;
	Node* next_prior;
	Node* prev_prior;
	Node* next_schedule;
	Node* prev_schedule;
};

struct list {
    Node* head_prior;
	Node* head_schedule;
    Node* tail_prior;
    Node* tail_schedule;
	int size;
};

List* create_list (void) {
	return calloc(1, sizeof(List));
}

void erase_node(Node** n) {
	(*n)->next_prior = NULL;
	(*n)->prev_prior = NULL;
	(*n)->next_schedule = NULL;
	(*n)->prev_schedule = NULL;
	free(*n);
	*n = NULL;
}

void erase_list (List** l) {
	Node* p = NULL;
	Node* n = (*l)->head_prior;
	if(*l == NULL) return;
	while (n != NULL) {
			p = n; n = n->next_prior;
			erase_node(&p);
	}
	(*l)->head_prior = NULL;
	(*l)->head_schedule = NULL;
	free(*l);
	(*l) = NULL;
}

/* Compara os hórarios de dois procesos.
 * retornando 1 se o p1 é maior, -1 se
 * o p2 é mair e 0 se eles são iguais. */
int compare_schedule(Process p1, Process p2) {
	if(p1.arrival.hh < p2.arrival.hh)
        return -1;
	else if(p1.arrival.hh > p2.arrival.hh)
        return 1;
	else
        if(p1.arrival.mm < p2.arrival.mm)
            return -1;

		else if(p1.arrival.mm > p2.arrival.mm)
            return 1;
		else
            if(p1.arrival.ss < p2.arrival.ss)
                return -1;
			else if(p1.arrival.ss > p2.arrival.ss)
                return 1;

	return 0;
}

/* Split a doubly linked list (DLL) into 2 DLLs of half sizes */
//  For priority
Node *split_prior(Node *head) {
    Node *fast = head,*slow = head;
    while (fast->next_prior && fast->next_prior->next_prior) {
        fast = fast->next_prior->next_prior;
        slow = slow->next_prior;
    }
    Node *temp = slow->next_prior;
    slow->next_prior = NULL;
    return temp;
}
//For schedule
Node *split_schedule(Node *head) {
    Node *fast = head,*slow = head;
    while (fast->next_schedule && fast->next_schedule->next_schedule) {
        fast = fast->next_schedule->next_schedule;
        slow = slow->next_schedule;
    }
    Node *temp = slow->next_schedule;
    slow->next_schedule = NULL;
    return temp;
}

/* Function to merge two linked lists */

//For priority
Node* merge_prior(Node *first, Node *second) {
    // If first linked list is empty
    if (!first)
        return second;
    // If second linked list is empty
    if (!second)
        return first;
    // Pick the smaller value
    if (first->process.prior > second->process.prior) {
        first->next_prior = merge_prior(first->next_prior,second);
        first->next_prior->prev_prior = first;
        first->prev_prior = NULL;
        return first;
    } else {
        second->next_prior = merge_prior(first, second->next_prior);
        second->next_prior->prev_prior = second;
        second->prev_prior = NULL;
        return second;
    }
}

//For schedule
Node* merge_schedule(Node *first, Node *second) {
    // If first linked list is empty
    if (!first)
        return second;
    // If second linked list is empty
    if (!second)
        return first;
    // Pick the smaller value
    if (compare_schedule(first->process, second->process) == -1) {
        first->next_schedule = merge_schedule(first->next_schedule,second);
        first->next_schedule->prev_schedule = first;
        first->prev_schedule = NULL;
        return first;
    } else {
        second->next_schedule = merge_schedule(first, second->next_schedule);
        second->next_schedule->prev_schedule = second;
        second->prev_schedule = NULL;
        return second;
    }
}

/* Function to do merge sort */
Node* mergeSort_prior(Node *head) {
    if (!head || !head->next_prior)
        return head;
    Node *second = split_prior(head);

    // Recur for left and right halves
    head = mergeSort_prior(head);
    second = mergeSort_prior(second);

    // Merge the two sorted halves
    return merge_prior(head,second);
}

Node* mergeSort_schedule(Node *head) {
    if (!head || !head->next_schedule)
        return head;
    Node *second = split_schedule(head);

    // Recur for left and right halves
    head = mergeSort_schedule(head);
    second = mergeSort_schedule(second);

    // Merge the two sorted halves
    return merge_schedule(head,second);
}

/* Retorna endereço de nó pesquisando pelo horário */
Node* search_schedule(int hh, int mm, int ss, List* process_list) {
	Node* ptr = process_list->head_schedule;
	Process* tmp = (Process*) calloc(1, sizeof(Process));
	tmp->arrival.hh = hh;
	tmp->arrival.mm = mm;
	tmp->arrival.ss = ss;

	while(ptr != NULL && compare_schedule(ptr->process, *tmp) != 0) {
        ptr = ptr->next_schedule;
	}

	return ptr;
}

/* Retorna endereço de nó pesquisando pela prioridade */
Node* search_prior(int prior, List* process_list) {
	Node* ptr = process_list->head_prior;

	while(ptr != NULL && ptr->process.prior != prior)
		ptr = ptr->next_prior;

	return ptr;
}

void add_process(List* process_list) {
	Node* new_node = (Node*) calloc(1, sizeof(Node));

	scanf("%d", &(new_node->process.prior));
	scanf("%d:%d:%d", &(new_node->process.arrival.hh), &(new_node->process.arrival.mm), &(new_node->process.arrival.ss));
	scanf("%s", new_node->process.description);

    if(!process_list->size) {
        process_list->head_prior = process_list->tail_prior = new_node;
        process_list->head_schedule = process_list->tail_schedule = new_node;
		process_list->size++;
        return;
    }

	//Inserção ordenada por prioridade
	Node* ptr = process_list->head_prior;

	while(ptr != NULL && ptr->process.prior > new_node->process.prior)
		ptr = ptr->next_prior;


    if(ptr == NULL) { // Adicionar na ultima posição
        new_node->next_prior = NULL;
        new_node->prev_prior = process_list->tail_prior;
        process_list->tail_prior->next_prior = new_node;
        process_list->tail_prior = new_node;
    } else if(ptr == process_list->head_prior) { // Adicionar na primeira posição
        new_node->next_prior = ptr;
        new_node->prev_prior = NULL;
        ptr->prev_prior = new_node;
        process_list->head_prior = new_node;
    } else {
        new_node->next_prior = ptr;
        new_node->prev_prior = ptr->prev_prior;
        ptr->prev_prior->next_prior = new_node;
        ptr->prev_prior = new_node;
    }

	//Inserção ordenada por tempo
    ptr = process_list->head_schedule;

   	while(ptr != NULL && compare_schedule(ptr->process, new_node->process) == -1)
		ptr = ptr->next_schedule;

    if(ptr == NULL) {
        new_node->next_schedule = NULL;
        new_node->prev_schedule = process_list->tail_schedule;
        process_list->tail_schedule->next_schedule = new_node;
        process_list->tail_schedule = new_node;
    } else if(ptr == process_list->head_schedule) {
        new_node->next_schedule = ptr;
        new_node->prev_schedule = NULL;
        ptr->prev_schedule = new_node;
        process_list->head_schedule = new_node;
    } else {
        new_node->next_schedule = ptr;
        new_node->prev_schedule = ptr->prev_schedule;
        ptr->prev_schedule->next_schedule = new_node;
        ptr->prev_schedule = new_node;
    }

	process_list->size++;
}

void exec_process(List* process_list) {
	char op;
	Node* n;
	scanf(" -%c", &op);
	if(!process_list->size) return;

	switch (op) {

		case 'p': n = process_list->head_prior;
				  process_list->head_prior = n->next_prior;
				  n->prev_schedule->next_schedule = n->next_schedule;
				  n->next_schedule->prev_schedule = n->prev_schedule;
				  process_list->size--;
				  erase_node(&n);
				  break;

		case 't': n = process_list->head_schedule;
				  process_list->head_schedule = n->next_schedule;
				  n->prev_prior->next_prior = n->next_prior;
				  n->next_prior->prev_prior = n->prev_prior;
				  process_list->size--;
				  erase_node(&n);
				  break;
	}
}

void next_process(List* process_list) {
	char op;
	Node *n;
	scanf(" -%c", &op);
	if(!process_list->size) return;

	switch (op) {

		case 'p': n = process_list->head_prior;
			  	  printf("%d %d:%d:%d %s\n\n",  n->process.prior, n->process.arrival.hh, n->process.arrival.mm, n->process.arrival.ss, n->process.description);
				  break;

		case 't': n = process_list->head_schedule;
			  	  printf("%d %d:%d:%d %s\n\n",  n->process.prior, n->process.arrival.hh, n->process.arrival.mm, n->process.arrival.ss, n->process.description);
				  break;

	}
}

void change_process(List* process_list) {
	char op;
	Node* n;
	int old_prior, new_prior;
	int old_hh, old_mm, old_ss, new_hh, new_mm, new_ss;
	scanf(" -%c", &op);

	switch (op) {

		case 'p': scanf("%d|%d", &old_prior, &new_prior);
				  n = search_prior(old_prior, process_list);
				  n->process.prior = new_prior;
				  process_list->head_prior = mergeSort_prior(process_list->head_prior);
				  process_list->head_schedule = mergeSort_schedule(process_list->head_schedule);
			  	break;

		case 't': scanf("%d:%d:%d|%d:%d:%d", &old_hh, &old_mm, &old_ss, &new_hh, &new_mm, &new_ss);
			 	  n = search_schedule(old_hh, old_mm, old_ss, process_list);
				  n->process.arrival.hh = new_hh;
				  n->process.arrival.mm = new_mm;
				  n->process.arrival.ss = new_ss;
				  process_list->head_prior = mergeSort_prior(process_list->head_prior);
				  process_list->head_schedule = mergeSort_schedule(process_list->head_schedule);
				  break;
	}
}

void print_process(List* process_list) {
	char op;
	scanf(" -%c", &op);

	switch (op) {

		case 'p': for (Node *n = process_list->head_prior; n != NULL; n = n->next_prior)
				  	printf("%d %d:%d:%d %s\n", n->process.prior, n->process.arrival.hh, n->process.arrival.mm, n->process.arrival.ss, n->process.description);
				  printf("\n");
				  break;

		case 't': for (Node *n = process_list->head_schedule; n != NULL; n = n->next_schedule)
		  			printf("%d %d:%d:%d %s\n", n->process.prior, n->process.arrival.hh, n->process.arrival.mm, n->process.arrival.ss, n->process.description);
				  printf("\n");
				  break;

	}
}

void quit(List** l) {
	erase_list(l);
	exit(0);
}

void start() {
	char command[8];
	List* process_list = create_list();

	do {

		scanf("%s", command);

		if (!strcmp(command, "add")) add_process(process_list);
		else if (!strcmp(command, "exec")) exec_process(process_list);
		else if (!strcmp(command, "next")) next_process(process_list);
		else if (!strcmp(command, "change")) change_process(process_list);
		else if (!strcmp(command, "print")) print_process(process_list);
		else if	(!strcmp(command, "quit")) quit(&process_list);

	} while (strcmp(command, "quit"));
}

int main(void) {

	start();
	return 0;
}
