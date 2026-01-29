#ifndef ARVORES_H
#define ARVORES_H

#include <stdio.h>

// Struct para Árvore Binária Comum
typedef struct no_arvore {   // <--- Nome único: no_arvore
    int chave;
    struct no_arvore *esq;   // <--- Ajustado para no_arvore
    struct no_arvore *dir;   // <--- Ajustado para no_arvore
} NOA;

// Struct para Árvore AVL
typedef struct no_avl {      // <--- Nome único: no_avl
    int chave;
    struct no_avl *esq;      // <--- Ajustado para no_avl
    struct no_avl *dir;      // <--- Ajustado para no_avl
    int bal;
} NOAVL;

void menuArvores();
#endif