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


//questão 2 prova 2017.1

int abNumNosAlturaH(TNode *t, int h){
    if(t != NULL){
        if(h == 0){
            return 1;
        }
        
        else{
            int nl = abNumNosAlturaH(t->l, h -1);
            int nr = abNumNosAlturaH(t->r, h-1);

            return nl+nr;
        }
    }

    return 0;
}


//questao 3 prova 2017.1

int abpCalculaDiferencaMenorParaMaior(TNode *t, int(*getavalue)(void *)){
    if(t != NULL){
        TNode *maior = t;
        TNode *menor = t;

        while(menor->l != NULL){
            menor = menor -> l;
        }

        while (maior->r != NULL){
            maior = maior -> r;
        }

        return (getavalue(maior) - getavalue(menor));

    }

    return 0;
}

//questao 2 prova 2023.1
int abCalcNumNosGrau1(TNode *t){
    if(t != NULL){
        int nl, nr;
        if((t->r == NULL && t->l != NULL )|| (t->r != NULL && t->l == NULL)){
            nl = abCalcNumNosGrau1(t->l);
            nr = abCalcNumNosGrau1(t->r);
            return nl + nr + 1;
        }

        else{
            nl = abCalcNumNosGrau1(t->l);
            nr = abCalcNumNosGrau1(t->r);

            return nl + nr;
        }
    }

    return 0;
}

//questao 3 prova 2023.1
int comparaArvores(TNode *t1, TNode *t2, int(*getvalue)(void *)){
    if(t1 != NULL && t2 != NULL){
        if(getvalue(t1) > getvalue(t2)){
        
            return comparaArvores(t1->r, t2->r, getvalue) && comparaArvores(t1->l, t2->l, getvalue);
            
        }

        else{
            return 0;
        }
    }
    else if(t1 == NULL && t2 == NULL){
        return 1;
    }

    return 0;
}


//questao 4 prova 2023.1
TNode *abpRemoveMaior(TNode *t, int(*cmp)(void *, void *)){
    if(t != NULL){
        if(t -> r == NULL){ 
            if(t->l == NULL){
                free(t);
                return NULL;
            }
            else{
                TNode *aux = t -> l;
                free(t);
                return aux;
            }
        }
        else{
            t->r = abpRemoveMaior(t->r, cmp); 
            return t;   
        }
    }

    return NULL;
}

//questao 6 lista de exercicios
int abNumNosUmFilhoOuMais(TNode *t){
    if(t != NULL){
        if(t->l != NULL || t->r != NULL){
            return 1 + abNumNosUmFilhoOuMais(t->l) + abNumNosUmFilhoOuMais(t->r);
        }
    }

    return 0;
}

int abAltura(TNode *t){
    if(t != NULL){
        int hr, hl, h;
        hr = 1 + abAltura(t->r);
        hl = 1 + abAltura(t->l);
        if(hr > hl){
            h = hr;
        }
        else{
            h = hl;
        }

        return h;
    }

    return 0;
}


//questao 10 da lista de exercicios, tenho q corrigir
int ehCompleta(TNode *){
    if(t != NULL){
        if(t -> r != NULL && t->l != NULL){
            return ehCompleta(t->r) && ehCompleta(t->l);
        }

        else if(t -> r == NULL && t-> l == NULL){
            return TRUE;
        }
        else{
            return FALSE;
        }
    }

    return TRUE;
}

//questao 8 da lista de exercicios


void visitarNosPorNivelOrdem(TNode *t, void (*visit)(void *)){
    if(t != NULL){
        //primeiro calcularei a altura da arvore
        int h = abAltura(TNode *t);

        for(int i = 0; i < h; i++){
            visitNosAlturaH(t, i, visit);
        }

    }
}

void visitNosAlturaH(TNode *t, int h, void(*visit)(void *)){
    if(t != NULL){
        if(h >= 0){
            if(h == 0){
                visit(t);
            }

            else{
                visitNosAlturaH(t->r, h-1, visit);
                visitNosAlturaH(t->l, h-1, visit);
            }
        }
    }
}


void visitarNosPorNivelOrdemReversa(TNode *t, void(*visit)(void *)){
    if(t != NULL){
        //primeiro calcularei a altura da arvore
        int h = abAltura(TNode *t);

        for(int i = h-1; i <= 0; i--){
            visitNosAlturaH(t, i, visit);
        }
    }
}

//questao 11

TNode *abRetornarCantoEsquerdo(TNode *t){
    if(t != NULL){
        if(t->l != NULL){
            return abRetornarCantoEsquerdo(t->l);
        }

        else{
            return t->data;
        }
    }

    return NULL;

}


//questao 12

int verificarSeEhABP(TNode *t, int(*cmp)(void *, void *)) {

    if (t != NULL) {
        if (t->l != NULL && cmp(t->l->data, t->data) >= 0) {
            return false;
        }

    
        if (t->r != NULL && cmp(t->r->data, t->data) < 0) {
            return false;
        }

        return verificarSeEhABP(t->l, cmp) && verificarSeEhABP(t->r, cmp);


    }

    return TRUE;   
}


//questao 938 leetcode 
//retornar a soma dos valores dos nos de uma arvore em que os valores esta dentro de um intervalo
int rangeSumBST(TNode *root, int low, int high) {
    if(root != NULL){
        if(root -> data >= low && root->data <= high){
            return root->val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);      
            
        }

        else if(root -> val > high){
            return rangeSumBST(root->left, low, high);
        }

        else if(root -> val < low){
            return rangeSumBST(root->right, low ,high);
        }
    }

    return 0;
}




//questao 1379 leetcode
// Given two binary trees original and cloned and given a reference to a node target in the original tree.

// The cloned tree is a copy of the original tree.

// Return a reference to the same node in the cloned tree.

// Note that you are not allowed to change any of the two trees or the target node and the answer must be a reference to a node in the cloned tree.

TNode* getTargetCopy(TNode* original, TNode* cloned, TNode* target) {
        if(original != NULL && cloned != NULL){
            if(original->data == target->data && cloned->data == target -> data){
                return cloned;
            }

            else{
                possibilidade1 = getTargetCopy(original->l, cloned->l, target);
                if(possibilidade1 != NULL){
                    return possibilidade1;
                }
                possibilidade2 = getTargetCopy(original->r, cloned->r, target);
                if(possibilidade2 != NULL){
                    return possibilidade2;
                }

                return NULL;

                
            }
        }

        return NULL;
}

//questao 700 leetcode 

// You are given the root of a binary search tree (BST) and an integer val.
// Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.

TNode* searchBST(TNode* root, int val) {
    if(root != NULL){
        if(root->val == val){
            return root;
        }
        else if(root->val > val){
            return searchBST(root->left, val);
        }

        return searchBST(root->right, val);
    }

    return NULL;
}


//questao 617 leetcode
// You are given two binary trees root1 and root2.
// Imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge the two trees into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of the new tree.
// Return the merged tree.
// Note: The merging process must start from the root nodes of both trees.

TNode* mergeTrees(TNode* root1, TNode* root2) {
    if(root1 != NULL && root2 != NULL){
        root1->val += root2->val;
        
        root1->left = mergeTrees(root1->left, root2->left);

        root1->right = mergeTrees(root1->right, root2->right);
        

        return root1;
    }

    else if(root1 != NULL && root2 == NULL){
        return root1;
    }

    else if(root1 == NULL && root2 != NULL){
        return root2;
    }

    return NULL;
}

//questao 897 leetcode
// Given the root of a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the 
// root of the tree, and every node has no left child and only one right child.

TNode* increasingBST(TNode* root, TNode *tail) {
    if(root != NULL){
        TNode *res = increasingBST(root->l, root);
        root->l = NULL;
        root->r = increasingBST(root->right, tail);

        return res;
    }
    else{
        return tail;
    }

}

//questao 2331 leetcode

int evaluateTree(TNode* root) {
    if(root->l != NULL && root->r != NULL){
        if(root->data == 3){
            return evaluateTree(root->l) || evaluateTree(root->r);
        }
        else{
            return evaluateTree(root->l) && evaluateTree(root->r);
        }
    }

    else{
        if(root->data == 0){
            return FALSE;
        }

        else{
            return TRUE;
        }
    }
}


//questao 226 leetcode
//Given the root of a binary tree, invert the tree, and return its root.

TNode* invertTree(TNode* root) {
    if(root != NULL){
        TNode* temp = root->l;
        root->l = invertTree(root->r);
        root->r = invertTree(temp);

        return root;
    }

    else{
        return NULL;
    }
}


//questao 104
// Given the root of a binary tree, return its maximum depth.
// A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

int maxDepth(TNode* root) {
    if(root != NULL){
        int rightPath = 1 + maxDepth(root->r);
        int leftPath = 1 + maxDepth(root -> l);

        if(rightPath >= leftPath){
            return rightPath;
        }

        else{
            return leftPath;
        }
    }
    return 0;
}


int numNosUmFilhoOuMenos(TNode *t){
    if(t != NULL){
        if(t->l != NULL && t->r != NULL){
            return 0 + numNosUmFilhoOuMenos(t->l) + numNosUmFilhoOuMenos(t->r);
        }
        else{
            if(t -> l != NULL){
                return 1 + numNosUmFilhoOuMenos(t->l);
            }
            else if(t -> r != NULL){
                return 1 + numNosUmFilhoOuMenos(t->r);
            }

            return 1;
        }
    }

    return 0;
}

TNode *abRetornarCantoEsquerdoNivelK(TNode *t, int level, int k){
    if(t != NULL){
        if(k == level){
            return t;
        }
        else{
            TNode *esquerdo = abRetornarCantoEsquerdoNivelK(t->l, level +1, k);
            TNode *direito = abRetornarCantoEsquerdoNivelK(t->k, level+1, k);
            if(esquerdo != NULL){
                return esquerdo;
            }
            else{
                return direito;
            }
        }
    }

    return NULL;
}


TNode *removeMaiorABP(TNode *t, int(*cmp)(void *)){
    if(t != NULL){
        if(t->r == NULL){
            if(t -> l != NULL){
                TNode *aux = t->l;
                free(t);
                return aux;
            }
            else{
                free(t);
                return NULL;
            }
        }
        else{
            t->r = removeMaiorABP(t->r, cmp);
            return t;
        }
    }
}

int arvore1maiorque2(TNode *t, TNode *k, int(*getvalue)(void*)){
    if(t != NULL && k != NULL){
        if(getvalue(t) > getvalue(k)){
            int checagemDireita = (t->r, k->r, getvalue);
            int checagemEsquerda = (t->l, k->l, getvalue);

            if(checagemDireita == 1 && checagemEsquerda == 1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    else if(t != NULL && k != NULL){
        return 1;
    }

    return 0;

}       


int numeroNosGrau1(TNode *t){
    if(t != NULL){
        if((t->r != NULL && t->l == NULL) || (t->r == NULL && t->l != NULL)){
            return 1 + numeroNosGrau1(t->r) + numeroNosGrau1(t->l);
        }

        else{
            return numeroNosGrau1(t->r) + numeroNosGrau1(t->l);
        }
    }

    return 0;
}







