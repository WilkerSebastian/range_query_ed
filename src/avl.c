/*

    https://github.com/edpfacom/libfacom/blob/main/src/avl.c

*/
#include<stdio.h>
#include<stdlib.h>
#include"avl.h"

int max(int a,int b){
    return a>b?a:b;
}

int altura(tnode *arv){
    int ret;
    if (arv==NULL){
        ret = -1;
    }else{
        ret = arv->h;
    }
    return ret;
}

// função para inserir um item na arvore
void addItem(tnode *node, titem item) {

    LinkedList *newItem = (LinkedList *)malloc(sizeof(LinkedList));
    newItem->item = item;
    newItem->prox = node->items;
    node->items = newItem;

}

// função para criar um novo nó que para avl
tnode *createNode(titem item) {

    tnode *node = (tnode *)malloc(sizeof(tnode));
    node->items = NULL;
    addItem(node, item);
    node->esq = NULL;
    node->dir = NULL;
    node->father = NULL;
    node->h = 0;

    return node;

}

void avl_insere(tnode ** parv,titem item){
    if (*parv == NULL){
        *parv = createNode(item);
    }else if ((*parv)->items->item > item) {
        avl_insere(&(*parv)->esq, item);
        if ((*parv)->esq != NULL) {
            (*parv)->esq->father = *parv;
        }
    } else if ((*parv)->items->item < item) {
        avl_insere(&(*parv)->dir, item);
        if ((*parv)->dir != NULL) {
            (*parv)->dir->father = *parv;
        }
    } else {
        addItem(*parv, item);
    }
    (*parv)->h = max(altura((*parv)->esq), altura((*parv)->dir)) + 1;
    _avl_rebalancear(parv);
}
void _rd(tnode **parv) {
    tnode *y = *parv;
    tnode *x = y->esq;
    tnode *B = x->dir;

    x->dir = y;
    y->esq = B;

    x->father = y->father;
    y->father = x;
    if (B != NULL) {
        B->father = y;
    }

    *parv = x;

    y->h = max(altura(y->esq), altura(y->dir)) + 1;
    x->h = max(altura(x->esq), altura(x->dir)) + 1;
}

void _re(tnode **parv) {
    tnode *x = *parv;
    tnode *y = x->dir;
    tnode *B = y->esq;

    y->esq = x;
    x->dir = B;

    y->father = x->father;
    x->father = y;
    if (B != NULL) {
        B->father = x;
    }

    *parv = y;

    x->h = max(altura(x->esq), altura(x->dir)) + 1;
    y->h = max(altura(y->esq), altura(y->dir)) + 1;
}


void _avl_rebalancear(tnode **parv){
    int fb;
    int fbf;
    tnode * filho;
    fb = altura((*parv)->esq) - altura((*parv)->dir);

    if (fb  == -2){
        filho = (*parv)->dir;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf <= 0){ /* Caso 1  --> ->*/
            _re(parv);
        }else{   /* Caso 2  --> <-*/
            _rd(&(*parv)->dir);
            _re(parv);
        }
    }else if (fb == 2){  
        filho = (*parv)->esq;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf >=0){ /* Caso 3  <-- <-*/
            _rd(parv);
        }else{  /* Caso 4  <-- ->*/
            _re(&(*parv)->esq);
            _rd(parv);
        }
    }
}

tnode ** percorre_esq(tnode ** arv){
    tnode * aux = *arv;
    if (aux->esq  == NULL){
        return arv;
    }else{
        while (aux->esq->esq != NULL)
            aux = aux->esq;
        return &(aux->esq);
    }
}
void avl_remove(tnode **parv, titem reg){
    int cmp;
    tnode *aux;
    tnode **sucessor;
    if (*parv != NULL){
        cmp  = (*parv)->items->item  - reg;
        if (cmp > 0){ /* ir esquerda*/
            avl_remove(&((*parv)->esq), reg);
        }else if (cmp < 0){ /*ir direita*/
            avl_remove(&((*parv)->dir), reg);
        }else{ /* ACHOU  */
            if ((*parv)->esq == NULL && (*parv)->dir == NULL){   /* no folha */
                free(*parv);
                *parv = NULL;
            }else if ((*parv)->esq == NULL || (*parv)->dir == NULL){ /* tem um filho*/
                aux = *parv;
                if ((*parv)->esq == NULL){
                    *parv = (*parv)->dir;
                }else{
                    *parv = (*parv)->esq;
                }
                free(aux);
            }else{ /* tem dois filhos */
                sucessor = percorre_esq(&(*parv)->dir);
                (*parv)->items = (*sucessor)->items;
                avl_remove(&(*parv)->dir,(*sucessor)->items->item);
            }
        }
        if (*parv != NULL){
            (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
            _avl_rebalancear(parv);
        }
    }
}

void avl_destroi(tnode *parv){
    if (parv != NULL) {
        avl_destroi(parv->esq);
        avl_destroi(parv->dir);

        LinkedList *current = parv->items;
        while (current != NULL) {
            LinkedList *aux = current;
            current = current->prox;
            free(aux);
        }

        free(parv);
    }
}

// função para pecorrer a avl para encontrar o sucessor
tnode *sucessor(tnode *node) {
    if (node->dir != NULL) {
        tnode *current = node->dir;
        while (current->esq != NULL) {
            current = current->esq;
        }
        return current;
    } else {
        tnode *current = node;
        tnode *parent = node->father;
        while (parent != NULL && current == parent->dir) {
            current = parent;
            parent = parent->father;
        }
        return parent;
    }
}