#ifndef LISTAS_H 
#define LISTAS_H

#include <stdio.h>


typedef struct no {
    int info;
    struct no* prox;
} NO;

void menuListas();
// ... outros protótipos ...

#endif // Fim do ifndef