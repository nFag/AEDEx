#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "filas.h"

//Inicializa fila
void InicializarFila(FILA *f){
    f->inicio = NULL;
    f->fim = NULL;
}

//Faz a soma dos inteiros de uma fila;
int SomaTermosFila(FILA *f){
    if(!f->inicio) return 0;
    NOF* p = f->inicio;
    int soma = 0;
    while(p){
        soma += p->info;
        p = p->prox;
    }
    return soma;
}

void menuFilas() { printf("Menu Filas em breve...\n"); }
