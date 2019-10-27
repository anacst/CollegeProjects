#include <stdlib.h>
#include <collection.h>

struct node_ {
  int value;
  NODE* left;
  NODE* right;
  int height;
};

struct c_ {
  NODE* start;
  int structure_id;
};

COLLECTION* create_collection(int structure_id) {
  COLLECTION* c = (COLLECTION*) malloc(sizeof(COLLECTION));
  c->start = NULL;
  c->structure_id = structure_id;
  return c;
}

NODE* create_node(int value) {
    NODE* new = (NODE*) calloc(1, sizeof(NODE));
    new->value = value;
    return new;
}

bool insert_ordered(COLLECTION* c, NODE* n) {
  NODE* ptr = c->start;

  if(n) {
    //In case it's the first node to be added
    if(ptr == NULL) {
      c->start = n;
      return SUCCESS;
    }

    while(ptr->next != NULL && ptr->next->value < n->value)
      ptr = ptr->right;

    n->right = ptr->right;
    ptr->right = n;
    n->right->left = n;
    n->left = ptr;

    return SUCCESS;
  }

  return ERROR;
}

bool insert_last(COLLECTION* c, NODE* n) {
  NODE* ptr = c->start;

  if(n) {
    while(ptr != NULL)
      ptr = ptr->right;

    if(ptr == NULL) //In case we're adding the first node
      c->start = n;
    else
      ptr->right = n;
    n->left = ptr;
    n->right = NULL;
    return SUCCESS;
  }

  return ERROR;
}

bool insert_first(COLLECTION* c, NODE* n) {
  if(n) {
    c->start->left = n;
    n->right = c->start;
    n->left = NULL;
    c->start = n;
    return SUCCESS;
  }

  return ERROR;
}

NODE** insert_binary_recursive(NODE* ptr, int x) {
  if(x > ptr->value)
    return ptr->right != NULL ? insert_binary_recursive(p->right, x) : &ptr->right;
  else
    return ptr->left != NULL ? insert_binary_recursive(p->left, x) : &ptr->left;
}

bool  insert_binary(COLLECTION* c, NODE* n) {
  //TODO
  //if(search_tree(c, n))
  //  return 0;

  if(n) {
    *(insert_binary_recursive(c->start, n->value)) = n;
    return SUCCESS;
  }

  return ERROR;
}

bool insert_avl(COLLECTION* c, NODE* n) {
  //TODO
  //if(search_tree(c, n))
  //  return 0;
}

bool insert(COLLECTION* c, int value) {
  NODE* new = create_node(value);

  switch (c->structure_id) {

    case 1: return insert_ordered(new);
            break;

    case 2: return insert_last(new);
            break;

    case 3: return insert_first(new);
            break;

    case 4: return insert_binary(new);
            break;

    case 5: return insert_avl(new);
            break;
  }
}

bool exist(COLLECTION* c, int value) {
  switch (c->structure_id) {

    case 1: return search_ordered(c, value);
            break;

    case 2: return search_last(c, value);
            break;

    case 3: return search_first(c, value);
            break;

    case 4: return search_binary(c, value);
            break;

    case 5: return search_avl(c, value);
            break;

    default: return ERROR;
  }
}

void destroy(COLLECTION*) {

}
