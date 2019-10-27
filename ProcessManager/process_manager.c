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
	Node* next;
	Node* next_prior;
	Node* next_schedule;
	Node* prev;
	Node* prev_prior;
	Node* prev_schedule;
};

struct list {
	Node* start;
	Node* first_prior;
	Node* first_schedule;
	Node* end;
	int size;
};

void erase_node (Node** n) {
	free(*n);
	*n = NULL;
}

List* create_list (void) {
	List* new = (List*) malloc(sizeof(List));
	new->start = NULL;
	new->first_prior = NULL;
	new->first_schedule = NULL;
	new->end = new->start;
	new->size = 0;
	return new;
}

void erase_list (List** l) {
	Node* p = NULL;
	Node* n = (*l)->start;
	if(*l == NULL) return;
	while (n != (*l)->end) {
		if(n->next != NULL) {
			p = n; n = n->next;
			erase_node(&p);
		}
	}
	(*l)->start = NULL;
	(*l)->first_prior = NULL;
	(*l)->first_schedule = NULL;
	free(*l);
	(*l) = NULL;
}

Node* prior_partition (Node* start, Node* end, Node** newStart, Node** newEnd) {
	Node* pivot = end;
	Node* current = start;
	Node* prev = NULL;
	Node* tail = pivot;

	while (current != pivot) {
		if (current->process.prior > pivot->process.prior) {
			if ((*newStart) == NULL)
				(*newStart) = current;
			prev = current;
			current = current->next;
		} else {
			if (prev) prev->next_prior = current->next_prior;
			Node* tmp = current->next;
			current->next_prior = NULL;
			tail->next_prior = current;
			tail = current;
			current = tmp;
		}
	}

	//Se o pivot é o maior elemento, ele se torna o primeiro
	if ((*newStart) == NULL)
		(*newStart) = pivot;

	//(?)Atualizamos o último elemento
	(*newEnd) = tail;

	return pivot;
}

Node* recursive_sort_prior(Node* start, Node* end) {
	//Caso base
	if (!start || start == end) return start;

	Node* newStart = NULL;
	Node* newEnd = NULL;

	Node* pivot = prior_partition(start, end, &newStart, &newEnd);

	if (pivot != newStart) {

		//Find last element of the new sublist to be ordered
		Node* tmp = newStart;
		while (tmp->next != pivot) tmp = tmp->next;
		tmp->next = NULL;

		//Recur for the sublist before the pivot
		newStart = recursive_sort_prior(newStart, tmp);

		//Connect last element of the left ordered sublist with the rest of list
		tmp = newEnd;
		tmp->next_prior = pivot;
	}

	//Recur for the sublist after the pivot
	pivot->next = recursive_sort_prior(pivot->next, newEnd);

	return newStart;
}

void sort_prior (List* process_list) {
	if(!process_list->size) return;
	process_list->first_prior = recursive_sort_prior(process_list->start, process_list->end);
}

//Node* schedule_partition ();

//Node* recursive_sort_schedule (Node* start, Node* end);
/*
void sort_schedule (List* process_list) {
	process_list->first_schedule = recursive_sort_schedule(process_list->start, process_list->end);
}
*/
Node* search_prior(int old_prior, List* process_list) {
	for (Node* n = process_list->first_prior; (n != NULL) && (n->process.prior >= old_prior); n = n->next_prior)
		if (n->process.prior == old_prior) return n;
	return NULL;
}

Node* search_schedule(int old_hh, int old_mm, int old_ss, List* process_list) {
	for (Node* n = process_list->first_schedule; (n != NULL) && (n->process.arrival.hh <= old_hh); n = n->next_schedule) {
		if (n->process.arrival.hh < old_hh) {
			return n;
		} else {
			if (n->process.arrival.mm < old_mm) {
				return n;
			} else {
				if (n->process.arrival.ss == old_ss) {
					return n;
				}
			}
		}
	}
	return NULL;
}

void add_process (List* process_list) {
	Node* new = (Node*) malloc(sizeof(Node));

	if(!process_list->size) {
		process_list->start = new;
		process_list->first_prior = new;
		process_list->first_schedule = new;
	} else {
		process_list->end->next = new;
	}
	scanf("%d", &(new->process.prior));
	scanf("%d:%d:%d", &(new->process.arrival.hh), &(new->process.arrival.mm), &(new->process.arrival.ss));
	scanf("%s", new->process.description);
	new->prev = process_list->end;
	process_list->end = new;
	new->next = NULL;
	process_list->size++;
	
//	sort_prior(process_list);
}

void exec_process (List* process_list) {
	char op;
	Node* n;
	scanf(" -%c", &op);
	if(!process_list->size) return;

	switch (op) {

		case 'p': //sort_prior(process_list);
			  n = process_list->first_prior;
			  process_list->first_prior = n->next_prior;
			  n->prev->next = n->next;
			  n->next->prev = n->prev;
			  n->prev_schedule->next_schedule = n->next_schedule;
			  n->next_schedule->prev_schedule = n->prev_schedule;
			  erase_node(&n);
			  process_list->size--;
			  break;

		case 't': //sort_prior(process_list);
			  n = process_list->first_schedule;
			  process_list->first_schedule = n->next_schedule;
			  n->prev->next = n->next;
			  n->next->prev = n->prev;
			  n->prev_prior->next_prior = n->next_prior;
			  n->next_prior->prev_prior = n->prev_prior;
			  erase_node(&n);
			  process_list->size--;
			  break;

	}
}

void next_process (List* process_list) {
	char op;
	Process p;
	scanf(" -%c", &op);
	if (!process_list->size) return;

	switch (op) {

		case 'p': p = process_list->first_prior->process;
			  printf("%d %d:%d:%d %s\n", p.prior, p.arrival.hh, p.arrival.mm, p.arrival.ss, p.description);
			  break;

		case 't': p = process_list->first_schedule->process;
			  printf("%d %d:%d:%d %s\n", p.prior, p.arrival.hh, p.arrival.mm, p.arrival.ss, p.description);
			  break;

	}
}

void change_process (List* process_list) {
	char op;
	Node* n;
	int old_prior, new_prior;
	int old_hh, old_mm, old_ss, new_hh, new_mm, new_ss;
	scanf(" -%c", &op);

	switch (op) {

		case 'p': scanf("%d|%d", &old_prior, &new_prior);
			  n = search_prior(old_prior, process_list);
			  n->process.prior = new_prior;
			  break;

		case 't': scanf("%d:%d:%d|%d:%d:%d", &old_hh, &old_mm, &old_ss, &new_hh, &new_mm, &new_ss);
			  n = search_schedule(old_hh, old_mm, old_ss, process_list);
			  n->process.arrival.hh = new_hh;
			  n->process.arrival.mm = new_mm;
			  n->process.arrival.ss = new_ss;
			  break;

	}

	sort_prior(process_list);
}

void print_process (List* process_list) {
	char op;
	Process *p;
	scanf(" -%c", &op);

	switch (op) {

		case 'p': for (Node *n = process_list->first_prior; n != NULL; n = n->next_prior) {
				  p = &n->process;
				  printf("%d %d:%d:%d %s\n", p->prior, p->arrival.hh, p->arrival.mm, p->arrival.ss, p->description);
			  }
			  break;

		case 't': for (Node *n = process_list->first_schedule; n != NULL; n = n->next_schedule) {
				  p = &n->process;
				  printf("%d %d:%d:%d %s\n", p->prior, p->arrival.hh, p->arrival.mm, p->arrival.ss, p->description);
			  }
			  break;

	}
}

void quit (List* l) {
	erase_list(&l);
}

void print (List* l) {
	Process *p;
	for (Node* n = l->start; n != NULL; n = n->next) {
		p = &n->process;
  		printf("%d %d:%d:%d %s\n", p->prior, p->arrival.hh, p->arrival.mm, p->arrival.ss, p->description);
	}
}

void start () {
	char command[8];
	List* process_list = create_list();

	do {

		scanf("%s", command);

		if (!strcmp(command, "add")) add_process(process_list);
		else if (!strcmp(command, "exec")) exec_process(process_list);
		else if (!strcmp(command, "next")) next_process(process_list);
		else if (!strcmp(command, "change")) change_process(process_list);
		else if (!strcmp(command, "print")) print(process_list);
		else if (strcmp(command, "quit") == 0) {
			quit(process_list);
			break;
		}

	} while (1);

	return;
}

int main(void) {

	start();
	return 0;
}
