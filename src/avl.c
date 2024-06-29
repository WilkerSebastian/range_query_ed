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

    LinkedList *nodeList = (LinkedList*)malloc(sizeof(LinkedList));
    nodeList->item = item;
    nodeList->prox = node->items;
    node->items = nodeList;
  
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

void avl_insere(tnode ** parv,titem item, Comparator comparator){

    printAVL(*parv, 0);

    if (*parv != NULL)
        printf("Inserindo %d | %d | %d\n", *(int*)(item), *(int*)((*parv)->items->item) ,(*comparator)((*parv)->items->item, item));

    if (*parv == NULL)
        *parv = createNode(item);

    else if ((*comparator)((*parv)->items->item, item) > 0) {

        avl_insere(&(*parv)->esq, item, comparator);

        if ((*parv)->esq != NULL) 
            (*parv)->esq->father = *parv;

    } else if ((*comparator)((*parv)->items->item, item) < 0) {

        avl_insere(&(*parv)->dir, item, comparator);

         if ((*parv)->dir != NULL) 
            (*parv)->dir->father = *parv;

    } else
        addItem(*parv, item);
    
    (*parv)->h = max(altura((*parv)->esq), altura((*parv)->dir)) + 1;
    _avl_rebalancear(parv);
}


void _rd(tnode **parv) {
    tnode *y = *parv;
    tnode *x = y->esq;
    tnode *B = x->dir;

    y->esq = B;
    x->dir = y;
    *parv = x;

    y->h = max(altura(y->esq), altura(y->dir)) + 1;
    x->h = max(altura(x->esq), altura(x->dir)) + 1;

    x->father = y->father;
    y->father = x;
    if (B != NULL)
        B->father = y;
}

void _re(tnode **parv) {
    tnode *x = *parv;
    tnode *y = x->dir;
    tnode *B = y->esq;

    x->dir = B;
    y->esq = x;
    *parv = y;

    x->h = max(altura(x->esq), altura(x->dir)) + 1;
    y->h = max(altura(y->esq), altura(y->dir)) + 1;

    y->father = x->father;
    x->father = y;
    if (B != NULL)
        B->father = x;
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

void avl_remove(tnode **parv, titem item, Comparator comparator) {
    if (*parv != NULL) {
        int cmp = (*comparator)((*parv)->items->item, item);
        if (cmp > 0) {
            avl_remove(&((*parv)->esq), item, comparator);
        } else if (cmp < 0) {
            avl_remove(&((*parv)->dir), item, comparator);
        } else {
            if ((*parv)->esq == NULL && (*parv)->dir == NULL) {
                avl_destroi(*parv);
                *parv = NULL;
            } else if ((*parv)->esq == NULL || (*parv)->dir == NULL) {
                tnode *aux = *parv;
                *parv = (*parv)->esq ? (*parv)->esq : (*parv)->dir;
                avl_destroi(aux);
            } else {
                tnode **s = sucessor(&(*parv)->dir);
                (*parv)->items = (*s)->items;
                avl_remove(&(*parv)->dir, (*s)->items->item, comparator);
            }
        }
        if (*parv != NULL) {
            (*parv)->h = max(altura((*parv)->esq), altura((*parv)->dir)) + 1;
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
tnode ** sucessor(tnode **parv) {

    if(*parv == NULL)
        return NULL;

    tnode **aux = parv;
    tnode **fParv = NULL;

    if((*aux)->dir) { 
        fParv = &(*aux)->dir;

        while((*fParv)->esq) 
            fParv= &(*fParv)->esq;

        return fParv;
    }
    
    fParv = &(*aux)->father;

    while(*fParv && *aux == (*fParv)->dir) { 
        aux = &(*fParv);
        fParv = &(*fParv)->father;
    }     

    return fParv;

}

// função para facilitar a vizualização da arvore já que eu estava tendo problemas durante um teste
void printAVL(tnode *parv, int level) {

    if (parv == NULL)
        return;

    printAVL(parv->dir, level + 1);
    printf("\n");

    for (int i = 0; i < level; i++)
        printf("\t");

    LinkedList *current = parv->items;
    while (current != NULL) {
        printf("%d ", *(int*)(current->item));
        current = current->prox;
    }
    printf("\n");
    printAVL(parv->esq, level + 1);
}