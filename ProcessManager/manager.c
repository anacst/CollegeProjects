/*
TODO;
> sort_prior
> sort_schedule
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
	Process* process;
	Node* next_prior;
	Node* prev_prior;
	Node* next_schedule;
	Node* prev_schedule;
};

struct list {
    Node* head_prior;
	Node* head_schedule;
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
		if(n->next_prior != NULL) {
			p = n; n = n->next_prior;
			erase_node(&p);
		}
	}
	(*l)->head_prior = NULL;
	(*l)->head_schedule = NULL;
	free(*l);
	(*l) = NULL;
}


Node* search_schedule(int hh, int mm, int ss, List* process_list) {
	Node* ptr = process_list->head_schedule;

	while(ptr != NULL && ptr->process->arrival.hh <= hh)
        ptr = ptr->next_schedule;

    if(ptr->process->arrival.hh == hh) {
        while(ptr != NULL && ptr->process->arrival.mm <= mm)
            ptr = ptr->next_schedule;

        if(ptr->process->arrival.mm == mm) {
            while(ptr != NULL && ptr->process->arrival.ss < ss)
                ptr = ptr->next_schedule;

        }
    }

	return ptr;
}

Node* search_prior(int prior, List* process_list) {
	Node* ptr = process_list->head_prior;

	while(ptr != NULL && ptr->process->prior != prior)
		ptr = ptr->next_prior;

	return ptr;
}

void add_process(List* process_list) {
	Node* new_node = (Node*) calloc(1, sizeof(Node));

	scanf("%d", &(new_node->process->prior));
	scanf("%d:%d:%d", &(new_node->process->arrival.hh), &(new_node->process->arrival.mm), &(new_node->process->arrival.ss));
	scanf("%s", new_node->process->description);

	//Inserção ordenada por prioridade
	Node* ptr = process_list->head_prior;
	if(!process_list->head_prior)
		process_list->head_prior = new_node;

	while(ptr != NULL && ptr->process->prior > new_node->process->prior)
		ptr = ptr->next_prior;

	new_node->next_prior = ptr;
	new_node->prev_prior->next_prior = new_node;
	if(ptr) {
		new_node->prev_prior = ptr->prev_prior;
		ptr->prev_prior = new_node;
	} else {
		new_node->prev_prior = NULL;
	}


	if(ptr == process_list->head_prior)
		process_list->head_prior = new_node;

	//Inserção ordenada por tempo
    ptr = process_list->head_schedule;
    if(!process_list->head_schedule)
		process_list->head_schedule = new_node;

    while(ptr != NULL && ptr->process->arrival.hh <= new_node->process->arrival.hh)
        ptr = ptr->next_schedule;

    if(ptr->process->arrival.hh == new_node->process->arrival.hh) {
        while(ptr != NULL && ptr->process->arrival.mm <= new_node->process->arrival.mm)
            ptr = ptr->next_schedule;

        if(ptr->process->arrival.mm == new_node->process->arrival.mm) {
            while(ptr != NULL && ptr->process->arrival.ss < new_node->process->arrival.ss)
                ptr = ptr->next_schedule;

        }
    }

    new_node->next_schedule = ptr;
    new_node->prev_schedule->next_schedule = new_node;

    if(ptr) {
        new_node->prev_schedule = ptr->prev_schedule;
        ptr->prev_schedule = new_node;
    } else {
        new_node->prev_schedule = NULL;
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
	Process* p;
	scanf(" -%c", &op);
	if (!process_list->size) return;

	switch (op) {

		case 'p': p = process_list->head_prior->process;
			  	  printf("%d %d:%d:%d %s\n", p->prior, p->arrival.hh, p->arrival.mm, p->arrival.ss, p->description);
				  break;

		case 't': p = process_list->head_schedule->process;
			  	  printf("%d %d:%d:%d %s\n", p->prior, p->arrival.hh, p->arrival.mm, p->arrival.ss, p->description);
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
				  n->process->prior = new_prior;
				  //sort_prior(process_list);
			  	  break;

		case 't': scanf("%d:%d:%d|%d:%d:%d", &old_hh, &old_mm, &old_ss, &new_hh, &new_mm, &new_ss);
			 	  n = search_schedule(old_hh, old_mm, old_ss, process_list);
				  n->process->arrival.hh = new_hh;
				  n->process->arrival.mm = new_mm;
				  n->process->arrival.ss = new_ss;
				  //sort_schedule(process_list);
				  break;
	}
}

void print_process(List* process_list) {
	char op;
	Process *p;
	scanf(" -%c", &op);

	switch (op) {

		case 'p': for (Node *n = process_list->head_prior; n != NULL; n = n->next_prior)
				  	printf("%d %d:%d:%d %s\n", n->process->prior, n->process->arrival.hh, n->process->arrival.mm, n->process->arrival.ss, n->process->description);
				  break;

		case 't': for (Node *n = process_list->head_schedule; n != NULL; n = n->next_schedule)
		  			printf("%d %d:%d:%d %s\n", n->process->prior, n->process->arrival.hh, n->process->arrival.mm, n->process->arrival.ss, n->process->description);
				  break;

	}
}

void quit(List** l) {
	erase_list(l);
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
		else if (strcmp(command, "quit") == 0) {
			quit(&process_list);
			break;
		}

	} while (1);

	return;
}

int main(void) {

	start();
	return 0;
}
