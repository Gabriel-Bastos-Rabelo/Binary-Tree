#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct _tnode_ {
    void *data;
    struct t_node *l;
    struct t_node *r;
}TNode;

typedef struct _tree_ {
    TNode *root;
} Tree;

//visitação


void preOrdem ( TNode *t, void (*visit)(void *))
{
    if ( t != NULL ) {
        visit(t->data);
        preOrdem ( t->l, visit);
        preOrdem ( t->r, visit);
    }
}

void posOrdem ( TNode *t, void (*visit)(void *))
{
    if ( t != NULL ) {
        preOrdem ( t->l, visit);
        preOrdem ( t->r, visit);
        visit(t->data);
    }
}

void simetrica ( TNode *t, void (*visit)(void *))
{
    if ( t != NULL ) {
        preOrdem ( t->l, visit);
        visit(t->data);
        preOrdem ( t->r, visit);
        
    }
}

int abnNumNos(TNode *t){

    int n, nl, nr;
    if(t != NULL){
        n = 1;
        nl = abnNumNos(t->l);
        nr = abnNumNos(t->r);
    }

    return n + nl + nr;
}

int abnNumFolhas(TNode *t){
    if(t != NULL){
        if(t -> l == NULL && t -> r == NULL){
            return 1;
        }
        else{
            int right = abnNumFolhas(t->r);
            int left = abnNumFolhas(t->l);

            return right + left;
        }
    }

    return 0;
}


int abnFolhas(TNode *t){
    int n, nl, nr;
    if(t != NULL){  
        if(t->l == NULL && t->r == NULL){
            n = 1;
        }
        else{
            n = 0;
        }

        nl = abnFolhas(t->l);
        nr = abnFolhas(t->r);
        return n + nl + nr;
    }

    return 0;
}


int abnNumNosGrauDois(TNode *t){
    if(t != NULL){
        int n, nl, nr;
        if(t -> r != NULL && t->l != NULL){
            n = 1;
        }
        else{
            n = 0;
        }

        nl = abnNumNosGrauDois(t->l);
        nr = abnNumNosGrauDois(t->r);
        return n + nl + nr;
    }

    return 0;
}

int abnNumNosGrauUm(TNode *t){
    if(t != NULL){
        int n, nl, nr;
        if((t -> r != NULL && t -> l == NULL) || (t -> l != NULL && t -> r == NULL)){
            n = 1;
        }
        else{
            n = 0;
        }

        nl = abnNumNosGrauUm( t-> l);
        nr = abnNumNosGrauUm(t->r);
        return n + nl + nr;
    }

    return 0;
}

int abAltura(Tree *t){
    return abAlturaPartidaNo(t->root, 0);
}

int abAlturaPartidaNo(TNode *t, int altura){
    if(t != NULL){
        int h, hr, hl;
        hr = abAlturaPartidaNo(t->r, altura +1);
        hl = abAlturaPartidaNo(t->l, altura +1);

        if(hr > hl){
            h = hr;
        }
        else{
            h = hl;
        }

        return h+1;
    }

    return 0;
}


void *abpQuery(TNode *t, void *key, int(*cmp)(void*, void *)){
    if(t != NULL){
        int stat = cmp(key, t->data);

        if(stat == 0){
            return t->data;
        }
        else{
            if(stat == -1){
                abpQuery(t->l, key, cmp);
            }

            else{
                abpQuery(t->r, key, cmp);
            }
        }

    }

    return NULL;
}

void *abpMaior(TNode *t){
    if(t != NULL){
        if(t->r == NULL){
            return t->data;
        }
        else{
            return abpMaior(t->r);
        }
    }

    return NULL;
}

void *abpMenor(TNode *t){
    if(t != NULL){
        if(t->l == NULL){
            return t->data;
        }

        else{
            return abpMenor(t->l);
        }
    }

    return NULL;
}


TNode *abpInsert(TNode *t, void *data, int(*cmp)(void *, void*)){
    if(t == NULL){
        TNode *newnode = (TNode *)malloc(sizeof(TNode));
        if(newnode != NULL){
            newnode -> data = data;
            newnode -> l = NULL;
            newnode -> r = NULL;
            return newnode;
        }
    }

    else{
        if(cmp(data, t->data) == -1){
            t->l = abpInsert(t->l, data, cmp);
        }

        else{
            t->r = abpInsert(t->r, data, cmp);
        }

        return t;
    }

    return NULL;
}

//remoção
//casos: 
// 1- o nó está em uma folha
// 2- o nó tem somente um filho
// 3- o nó tem dois filhos


TNode *abpRemove(TNode *t, void *key, int(*cmp)(void *, void *), void **data){
    void *data2;
    if(t != NULL){
        int stat = cmp(key, t->data);
        if(stat < 0){
            t->l = abpRemove(t->l, key, cmp, data);
            return t;
        }

        else if(stat > 0){
            t->r = abpRemove(t->r, key, cmp, data);
            return t;
        }

        else{

            //case 1: o nó está em uma folha
            if(t->l == NULL && t->r == NULL){
                *data = t->data;
                free(t);
                return NULL;
            }

            else if(t -> l == NULL){
                TNode *aux = t->r;
                *data = t->data;
                free(t);
                return aux;
            }

            else if(t -> r == NULL){
                TNode *aux = t->l;
                *data = t->data;
                free(t);
                return aux;
            }

            else{
                data = t->data;
                t->l = abpRemoveMaior(t->l, cmp, &data2);
                t->data = data2;
                return t;
            }
        }
    }
}


TNode *abpRemoveMaior(TNode *t, int(*cmp)(void *, void *), void **data){
    if(t != NULL){
        if(t -> r != NULL){
            t->r = abpRemoveMaior(t->r, cmp, data);
            return t;
        }

        else{
            if(t -> l != NULL){
                *data = t->data;
                TNode *aux = t->l;
                free(t);
                return aux;
            }

            else{
                *data = t->data;
                free(t);
                return NULL;
            }
        }
    }

    *data = NULL;
    return NULL;
}

TNode *abpRemoveMenor(TNode *t, int(*cmp)(void *, void *), void **data){
    if(t != NULL){
        if(t->l != NULL){
            t->l = abpRemoveMenor(t->l, cmp, data);
            return t;
        }
        else{
            if(t -> r != NULL){
                TNode *aux = t->r;
                free(t);
                return aux;
            }

            else{
                free(t);
                return NULL;
            }
        }
    }

    return NULL;
}