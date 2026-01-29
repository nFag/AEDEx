#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "arvores.h"


void inicializarArvore (NOA* *raiz){
    *raiz = NULL;
}

//EXERCICIOS COM ARVORES COMUNS

bool arvoreVazia (NOA* raiz){
    if(!raiz) return (true);
        else return (false);
}

//transforma as folhas da arvore em uma lista
void auxListaFolhas (NOA* raiz, NOA** ultimo, NOA** primeiro){
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
        auxListaFolhas(raiz->esq, ultimo, primeiro);
        auxListaFolhas(raiz->dir, ultimo, primeiro);
    }
}
NOA* listaFolhas(NOA* raiz){
    NOA* ultimo = NULL;
    NOA* primeiro = NULL;
    auxListaFolhas(raiz, &ultimo, &primeiro);
    return primeiro;
}

//soma o intervalo fechado entre um intervalo
int somaIntervalo(NOA* raiz, int min, int max){
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
bool ehEstritamenteBinaria(NOA* raiz){
    if(raiz){
        if((!raiz->esq && raiz->dir) || (raiz->esq  && !raiz->dir)) return false;
        return ehEstritamenteBinaria(raiz->esq) && ehEstritamenteBinaria(raiz->dir);
    }
    return true;
}

//verifica qual o nó com a chave respectiva que esta mais proximo da raiz
void auxOcorrenciaMaisProxima (NOA* raiz, int ch, int nivel, int* nivelMin, NOA** resp){
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
NOA* ocorrenciaMaisProxima (NOA* raiz, int ch){
    int nivelMin = INT_MAX;
    NOA* resp = NULL;
    auxOcorrenciaMaisProxima(raiz, ch, 1, &nivelMin, &(resp));
    return resp;
}

//verifica se há algum caminho até a raiz que possua uma soma k
bool caminhoSoma(NOAVL* raiz, int k){
    if(raiz){
        if(!raiz->esq && !raiz->dir){
            if (k == 0) return true;
                else return false;
        }
        k = abs(k - raiz->chave);
        return caminhoSoma(raiz->esq, k) || caminhoSoma(raiz->dir, k);
    }
    return false;
}

//verificar profundidade da arvore
int profundidade (NOAVL* raiz){
    if(raiz){
        int esq = profundidade(raiz->esq);
        int dir = profundidade(raiz->dir);
        if(esq > dir) return esq+1;
            else return dir+1;
    }
    return 0;
}

//remove folhas da arvore
void auxRemoveFolhas(NOA** raiz) {
    if(raiz || *raiz){
        NOA* atual = *raiz;

        if(!atual->esq && !atual->dir){
            free(atual);
            *raiz = NULL;
            return;
        }

        auxRemoveFolhas(&atual->esq);
        auxRemoveFolhas(&atual->dir);
    }
}
NOA* removeFolhas(NOA* raiz){
    NOA* resp = raiz;
    auxRemoveFolhas(&raiz);
    return resp;
}

//busca o nó mais profundo da arvore
void auxMaisProfundo(NOA* raiz, int ch, int nivelAtual, int* maxNivel, NOA** melhorNo) {
    if(raiz){
        if (raiz->chave == ch) {
            if (nivelAtual > *maxNivel) {
                *maxNivel = nivelAtual; 
                *melhorNo = raiz;         
            }
        }
        auxMaisProfundo(raiz->esq, ch, nivelAtual + 1, maxNivel, melhorNo);
        auxMaisProfundo(raiz->dir, ch, nivelAtual + 1, maxNivel, melhorNo);
    }
}
NOA* maisProfundo(NOA* raiz, int ch) {
    NOA* resposta = NULL;
    int maxNivel = -1;
    auxMaisProfundo(raiz, ch, 1, &maxNivel, &resposta);
    return resposta;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




//EXERCICIOS COM ABB's

/*
bool ehABB (NO* raiz, int min, int max){
    if(raiz){

    }
}
*/

void exibirMaiores(NOAVL* raiz, int ch){
    if(raiz){
        if(raiz->chave > ch){
            printf("%d", raiz->chave);
            exibirMaiores(raiz->esq, ch);
        }
        exibirMaiores(raiz->dir, ch);
    }
}



//EXERCICIOS COM AVL's

NOAVL* rotacaoL(NOAVL* p)
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

/*NOAVL* inserirAVL(NOAVL* p, int ch, bool* ajustar) {
    if(!p) {
        p = (NOAVL*) malloc(sizeof(NOAVL));
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
*/

// ... seus exercícios anteriores ...

void menuArvores() {
    printf("\n--- MENU ARVORES ---\n");
    printf("1. Testar Insercao AVL\n");
    printf("0. Voltar\n");
    // Logica de teste aqui
    printf("Pressione ENTER para voltar...\n");
    fflush(stdin); getchar();
}