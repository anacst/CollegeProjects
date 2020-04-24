#include <stdlib.h>
#include "colecao.h"

struct _no {
    int valor;
    struct _no* esq;
    struct _no* dir;
    int altura;
} ;

struct _c {
    No* inicio;
    int estrutura_id;
};

Colecao* cria_colecao(int estrutura_id) {
    Colecao* c = (Colecao*)malloc(sizeof(Colecao));
    c->inicio = NULL;
    c->estrutura_id = estrutura_id;
    return c;
}

No* cria_no(int valor) {
    No* novo = (No*)calloc(1, sizeof(No));
    novo->valor = valor;
    return novo;
}

// busca na lista ordenado
int existe_lista_ordenada(No *raiz, int valor) {
  No* aux = raiz;
  while (aux != NULL && aux->valor <= valor) {
    if (aux->valor == valor) return 1;
    aux = aux->dir;
  }
  return 0;
}

// busca listas normais
int existe_lista(No *raiz, int valor) {
  No* aux = raiz;
  while (aux != NULL) {
    if (aux->valor == valor) return 1;
    aux = aux->dir;
  }
  return 0;
}

// busca arvore
int existe_arv(No *raiz, int valor) {
  if (raiz == NULL) return 0;
  if (raiz->valor == valor) return 1;
  if (raiz != NULL) {
    if (valor > raiz->valor) existe_arv(raiz->dir, valor);
    else if (valor < raiz->valor) existe_arv(raiz->esq, valor);
  }
}

// insere valores na lista ordenada
void insere_ordenado(Colecao* c, No* n) {
  // caso a insercao seja na primeira posiçao
  if (c->inicio == NULL || c->inicio->valor >= n->valor) {
    n->dir = c->inicio;
    c->inicio = n;
  } else { // insercao no meio da lista
    No* ptr = c->inicio;
    while(ptr->dir && ptr->dir->valor < n->valor)
      ptr = ptr->dir;
    n->dir = ptr->dir;
    n->esq = ptr;
    ptr->dir = n;
    if (n->dir != NULL)
      n->dir->esq = n;
  }
}

void insere_ultimo(Colecao* c, No* n) {
  No* ptr = c->inicio;

  if (n) {
    while (ptr && ptr->dir != NULL)
      ptr = ptr->dir;

    if (ptr == NULL) {
      c->inicio = n;
      n->esq = NULL;
    } else {
      ptr->dir = n;
      n->esq = ptr;
    }

    n->dir = NULL;
  }
}

void insere_primeiro(Colecao* c, No* n) {
  if (n) {
    if (c->inicio == NULL) {
      c->inicio = n;
      return;
    }
    c->inicio->esq = n;
    n->dir = c->inicio;
    n->esq = NULL;
    c->inicio = n;
  }
}

// insercao na arvore binaria
No** __insere_binaria(No* ptr, int x) {
  if (x > ptr->valor)
    return ptr->dir != NULL ? __insere_binaria(ptr->dir, x) : &ptr->dir;
  else
    return ptr->esq != NULL ? __insere_binaria(ptr->esq, x) : &ptr->esq;
}

void insere_binaria(Colecao* c, No* n) {
  if (existe_arv(c->inicio, n->valor))
    return;

  if (n) {
    if (c->inicio == NULL) {
      c->inicio = n;
      return;
    }
    *(__insere_binaria(c->inicio, n->valor)) = n;
  }
}

// insercao na arvore avl
int max(int a, int b) {
  return (a > b ? a : b);
}

int altura_no(No* n) {
  return (n == NULL ? -1 : n->altura);
}

No* rotacao_esquerda(No* a) {
  No* b = a->dir;
  a->dir = b->esq;
  b->esq = a;

  a->altura = max(altura_no(a->esq), altura_no(a->dir)) + 1;
  b->altura = max(altura_no(b->esq), altura_no(b->dir)) + 1;

  return b;
}

No* rotacao_direita(No* a) {
  No* b = a->esq;
  a->esq = b->dir;
  b->dir = a;

  a->altura = max(altura_no(a->esq), altura_no(a->dir)) + 1;
  b->altura = max(altura_no(b->esq), altura_no(b->dir)) + 1;

  return b;
}

No* insere_avl(No* root, No* n) {
  if (root == NULL)
    return n;

  if (n->valor < root->valor)
    root->esq = insere_avl(root->esq, n);
  else if (n->valor > root->valor)
    root->dir = insere_avl(root->dir, n);
  else
    return root;

  root->altura = max(altura_no(root->esq), altura_no(root->dir)) + 1;

  if (altura_no(root->esq) - altura_no(root->dir) == 2) {
    if (altura_no(root->esq->esq) - altura_no(root->esq->dir) == 1) {
      return rotacao_direita(root);
    } else {
      root->esq = rotacao_esquerda(root->esq);
      return rotacao_direita(root);
    }
  } else if (altura_no(root->esq) - altura_no(root->dir) == -2) {
    if (altura_no(root->dir->esq) - altura_no(root->dir->dir) == 1) {
      root->dir = rotacao_direita(root->dir);
      return rotacao_esquerda(root);
    } else {
      return rotacao_esquerda(root);
    }
  }
  return root;
}

// apaga listas
void lista_esvazia (No *ptr) {
  if (ptr != NULL){
    if(ptr->dir != NULL)
      lista_esvazia(ptr->dir);
    ptr->esq = NULL;
    free(ptr); /* apaga o nó*/
    ptr = NULL;
 }
}

void lista_apagar(Colecao **ptr){
  if (*ptr == NULL) return;
  lista_esvazia((*ptr)->inicio);
  free(*ptr);
  *ptr = NULL;
}

// apaga arvore
void __arv_apagar_nos(No **raiz) {
  if (*raiz != NULL) {
    __arv_apagar_nos(&(*raiz)->esq);
    __arv_apagar_nos(&(*raiz)->dir);
    free(*raiz);
    *raiz = NULL;
  }
}

void arv_apagar(Colecao **T) {
  __arv_apagar_nos(&(*T)->inicio);
  free(*T);
  *T = NULL;
}

void adiciona(Colecao* c, int valor) {
  No* novo = cria_no(valor);

  switch (c->estrutura_id) {
    case 1: insere_ordenado(c, novo);
            break;

    case 2: insere_ultimo(c, novo);
            break;

    case 3: insere_primeiro(c, novo);
            break;

    case 4: insere_binaria(c, novo);
            break;

    case 5: c->inicio = insere_avl(c->inicio, novo);
            break;

    default: return;
  }
}

int existe(Colecao* c, int valor) {

  switch (c->estrutura_id) {
    case 1: return existe_lista_ordenada(c->inicio, valor);
            break;

    case 2: return existe_lista(c->inicio, valor);
            break;

    case 3: return existe_lista(c->inicio, valor);
            break;

    case 4: return existe_arv(c->inicio, valor);
            break;

    case 5: return existe_arv(c->inicio, valor);
            break;

    default: return 0;
  }
}

void destroi(Colecao* c) {
  Colecao *ptr = c;
  switch (c->estrutura_id) {
    case 1: return lista_apagar(&ptr);
            break;

    case 2: return lista_apagar(&ptr);
            break;

    case 3: return lista_apagar(&ptr);
            break;

    case 4: return arv_apagar(&ptr);
            break;

    case 5: return arv_apagar(&ptr);
            break;

    default: return;
  }
}
