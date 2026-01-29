#ifndef MATRIZES_H
#define MATRIZES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 1. As constantes DEVEM ficar no .h para a struct saber o tamanho
#define MAXLIN 100
#define MAXCOL 100

// 2. Struct do Nó da Matriz (Nome único: no_matriz)
typedef struct no_matriz {
    int lin;
    int col;
    int info;
    struct no_matriz *proxL;
    struct no_matriz *proxC;
} NOM;

// 3. Descritor da Matriz
typedef struct {
    NOM* lin[MAXLIN + 1]; // +1 pois você usa índices de 1 a 100
    NOM* col[MAXCOL + 1];
} LISTASCR;

// 4. Protótipos (Menu e Funções)
void menuMatrizes();
void inicializarMatriz(LISTASCR* m);
int contaElementos(LISTASCR* m);
int somaColuna(LISTASCR* m, int k);
int somaLinha(LISTASCR* m, int k);
void exibirProdutos(LISTASCR m, int c1, int c2);
bool excluiElementoPorIJ(LISTASCR* m, int i, int j);
int somaDiagonal(LISTASCR* m);
NOM* listaDiagonal(LISTASCR* m);
bool verificalistaDiagonal(NOM* teste, NOM* m);
bool ehSimetrica(LISTASCR* m);
bool ehTriangularSuperior(LISTASCR* m);

#endif