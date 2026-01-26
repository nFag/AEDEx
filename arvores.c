#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>


// INICIALIZAR ARVORE BINARIA
typedef struct estrutura {
    int chave;
    struct estrutura *esq;
    struct estrutura *dir;
} NO;

typedef struct estrutura {
    int chave;
    struct estrutura *esq;
    struct estrutura *dir;
    int bal;
} NOAVL;

void inicializarArvore (NO* *raiz){
    *raiz = NULL;
}

//EXERCICIOS COM ARVORES COMUNS

bool arvoreVazia (NO* raiz){
    if(!raiz) return (true);
        else return (false);
}

//transforma as folhas da arvore em uma lista
void listaFolhas (NO* raiz, NO** ultimo, NO** primeiro){
    if(raiz){
        if(!raiz->esq && !raiz->dir){
            if(!(*ultimo)){
                (*ultimo) = raiz;
                (*primeiro) = raiz;
            } else {
                (*ultimo)->esq = raiz;
                (*ultimo) = raiz;
            }
        }
        auxListaFolhas(raiz->esq, ultimo);
        auxListaFolhas(raiz->dir, ultimo);
    }
}
NO* listaFolhas(NO* raiz){
    NO* ultimo = NULL;
    NO* primeiro = NULL;
    auxListaFolhas(raiz, &ultimo, &primeiro);
    return primeiro;
}

//soma o intervalo fechado entre um intervalo
int somaIntervalo(NO* raiz, int min, int max){
    if(raiz){
        if(raiz->chave < min) return somaIntervalo(raiz->esq, min, max);
        if(raiz->chave > max) return somaIntervalo(raiz->dir, min, max);

        if((raiz->chave >= min) && (raiz->chave <= max)){
            return somaIntervalo(raiz->esq, min, max) + somaIntervalo(raiz->dir, min, max);
        }
    }
    return 0;
}

//verifica se cada no da arvore ou tem apenas dois filhos ou nenhum
bool ehEstritamenteBinaria(NO* raiz){
    if(raiz){
        if((!raiz->esq && raiz->dir) || (raiz->esq  && !raiz->dir)) return false;
        return ehEstritamenteBinaria(raiz->esq) && ehEstritamenteBinaria(raiz->dir);
    }
    return true;
}

//verifica qual o nó com a chave respectiva que esta mais proximo da raiz
void auxOcorrenciaMaisProxima (NO* raiz, int ch, int nivel, int* nivelMin, NO** resp){
    if(raiz){
        if(raiz->chave == ch){
            if(nivel < (*nivelMin)){
                *resp = raiz;
            }
            return;
        }
        auxOcorrenciaMaisProxima(raiz->esq, ch, nivel+1, nivelMin, resp);
        auxOcorrenciaMaisProxima(raiz->dir, ch, nivel+1, nivelMin, resp);
    }
}
NO* ocorrenciaMaisProxima (NO* raiz, int ch){
    int nivelMin = INT_MAX;
    NO* resp = NULL;
    auxOcorrenciaMaisProxima(raiz, ch, 1, &nivelMin, &(resp));
    return resp;
}




//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




//EXERCICIOS COM ABB's

/*
bool ehABB (NO* raiz, int min, int max){
    if(raiz){

    }
}
*/

void exibirMaiores(NO* raiz, int ch){
    if(raiz){
        if(raiz->chave > ch){
            printf("%d", raiz->chave);
            exibirMaiores(raiz->esq, ch);
        }
        exibirMaiores(raiz->dir, ch);
    }
}



//EXERCICIOS COM AVL's

NO* rotacaoL(NOAVL* p)
{
    NOAVL* u;
    NOAVL* v;
    u = p->esq;
    if(u->bal == -1) {
        // LL
         p->esq = u->dir;
        u->dir = p;
        p->bal = 0;
        p = u;
    }
    else {
        // LR
        v = u->dir;
        u->dir = v->esq;
        v->esq = u;
        p->esq = v->dir;
        v->dir = p;
        if(v->bal == -1) p->bal = 1;
        else p->bal = 0;
        if(v->bal == 1) u->bal = -1;
        else u->bal = 0;
        p = v;
    }
    p->bal = 0; // balanço final da raiz (p) da subarvore
    return (p);
}

NO* inserirAVL(NOAVL* p, int ch, bool* ajustar) {
    if(!p) {
        p = (NO *) malloc(sizeof(NO));
        p->esq = NULL;
        p->dir = NULL;
        p->chave = ch;
        p->bal = 0;
        *ajustar = true;
    }
    else {
        if(ch < p->chave) {
            p->esq = inserirAVL(p->esq, ch, ajustar);
            if(*ajustar)
                switch (p->bal) {
                    case 1 : p->bal = 0;
                        *ajustar = false;
                        break;
                    case 0 : p->bal = -1;
                        break; // continua verificando
                    case -1: p = rotacaoL(p);
                        *ajustar = false;
                        break;
                }
        }
        else {
            p->dir = inserirAVL(p->dir, ch, ajustar);
            if(*ajustar){
                switch (p->bal) {
                    case -1: p->bal = 0;
                        *ajustar = false;
                        break;
                    case 0 : p->bal = 1;
                        break; // continua verificando
                    case 1 : p = rotacaoR(p);
                         *ajustar = false;
                        break;
                }
            }
        }
    return (p);
    }
}
