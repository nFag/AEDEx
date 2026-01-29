#ifndef FILAS_H 
#define FILAS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Definindo os nós da fila:
typedef struct no_fila{
    int info;
    struct no_fila *prox;
}NOF

//Definindo a fila:
typedef struct{
    NOF* inicio;
    NOF* fim;
}FILA

void menuFilas();



// ... outros protótipos ...

#endif // Fim do ifndef
