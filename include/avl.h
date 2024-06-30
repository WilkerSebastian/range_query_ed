/*

    https://github.com/edpfacom/libfacom/blob/main/include/avl.h

*/
#ifndef __AVL__
#define  __AVL__

#include <stdint.h>

typedef void* titem;

typedef int (*Comparator)(titem, titem);

typedef struct lnode {
    titem item;
    uint32_t *codigo_ibge;
    struct lnode *prox;
} LinkedList;

typedef struct _node{
    LinkedList *items;
    struct _node *esq;
    struct _node *dir;
    struct _node *father;
    int h;
}tnode;

void avl_insere(tnode ** parv,titem reg, uint32_t *codigo_ibge, Comparator comparator);
void avl_destroi(tnode * parv);

void _rd(tnode ** pparv);
void _re(tnode ** pparv);
void _avl_rebalancear(tnode ** pparv);

void addItem(tnode *no, titem item, uint32_t *codigo_ibge);
tnode *createNode(titem item, uint32_t *codigo_ibge);

tnode ** sucessor(tnode **parv);

void printAVL(tnode *node, int level);

#endif