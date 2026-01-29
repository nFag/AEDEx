#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "matrizes.h"
#define MAXLIN 100
#define MAXCOL 100

// apostila
// Inicialização
void inicializarMatriz(LISTASCR* m) {
    int i;
    for(i=1; i <= MAXLIN; i++){
        m->lin[i] = NULL;
        for(i=1; i <= MAXCOL; i++){
            m->col[i] = NULL;
        }
    }
}

// apostila
// Conta elementos da estrutura
int contaElementos(LISTASCR* m) {
    int i, t;
    NOM* p;
    t = 0;
    for(i=1; i<= MAXLIN; i++) {
        p = m->lin[i];
        while (p) {
            t++;
            p = p->proxC;
        }
    }
    return(t);
}

// MATRIZ EM LINHAS CRUZADAS
int somaColuna (LISTASCR* m, int k){
    if(!m || k > MAXCOL) return 0;
    int soma = 0;

    NOM* p = m->col[k];
    while(p){
        soma = soma + p->info;
        p = p->proxL;
    }
    return soma;
}

int somaLinha (LISTASCR* m, int k){
    if(!m || k > MAXLIN) return 0;
    int soma = 0;

    NOM* p = m->lin[k];
    while(p){
        soma = soma + p->info;
        p = p->proxC;
    }
    return soma;
}


// apostila
// Exclui elemento p das listas apontadas por *linha e *coluna
    void excluir(NOM* *linha, NOM* *coluna, NOM* esq, NOM* acima, NOM* p) {
    if(p) {
    // desliga do vetor de linhas
        if(esq) esq->proxC = p->proxC;
            else *linha = p->proxC;

        // desliga do vetor de colunas
        if(acima) acima->proxL = p->proxL;
            else *coluna = p->proxL;

        free(p);
    }
}

// apostila
// Exibe os produtos dos elementos das colunas c1 e c2
void exibirProdutos(LISTASCR m, int c1, int c2) {

    NOM* p1 = m.col[c1];
    NOM* p2 = m.col[c2];

    int atual = 0;   // linha a ser processada
    int v1, v2;

    while (p1 || p2) {

        v1 = 0;
        if (p1) {
            if (p1->lin < atual) {
                p1 = p1->proxL;
                continue;
            }
            if (p1->lin == atual)
                v1 = p1->info;
        }

        v2 = 0;
        if (p2) {
            if (p2->lin < atual) {
                p2 = p2->proxL;
                continue;
            }
            if (p2->lin == atual)
                v2 = p2->info;
        }

        printf("Linha %d : %d*%d=%d\n", atual, v1, v2, v1 * v2);
        atual++;
    }

    if (atual < MAXLIN + 1)
        for (; atual <= MAXLIN; atual++)
            printf("Linha %d : 0*0=0\n", atual);
}

//excluir elemento passando por parametro numero da linha e numero da coluna
bool excluiElementoPorIJ(LISTASCR* m, int i, int j){
    if(i > MAXLIN || j > MAXCOL || !m) return false;
    NOM* ant;
    NOM* p = m->lin[i];
    while(p && p->col < j){
        ant = p;
        p = p->proxC;
    }
    
    if (p && p->col == j){
        ant->proxC = p->proxC;
    } else return false;
    
    p = m->col[j];
    
    while(p && p->lin < i){
        ant = p;
        p = p->proxL;
    }

    if (p && p->lin == j){
        ant->proxL = p->proxL;
    }
    free(p);
    return true;
}

//soma os elementos da diagonal da matriz
int somaDiagonal (LISTASCR* m){
    if(!m) return -1;
    int max, soma;
    if(MAXLIN > MAXCOL) max = MAXLIN;
        else max = MAXCOL;
    soma = 0;
    for (int i = 1; i <= max; i++){
        NOM* p = m->lin[i];
        while (p && p->lin < p->col){
            p = p->proxL;
        }
        if(p->col == p->lin) soma += p->info;
    }
    return soma;
}

//transforma a diagonal da matriz em listas cruzadas em lista DESCONSIDERANDO OS ZEROS (utilizando proxC como prox)
NOM* listaDiagonal (LISTASCR* m){
    if(!m) return NULL;
    
    NOM* inicio = NULL;
    NOM* ultimo = NULL;
    
    int min;
    if (MAXLIN > MAXCOL) min = MAXCOL;
        else min = MAXLIN;

    for(int i = 1; i <= min; i++){
        NOM* p = m->lin[i];
        while (p && p->col < i){ 
            p = p->proxC;
        }
        if (p && i == p->col){
            NOM* novo = (NOM*)malloc(sizeof(NOM));
            novo->info = p->info;
            novo->proxC = NULL;

            if(!ultimo) {
                inicio = novo;
            }
            else ultimo->proxC = p;
            
            ultimo = novo;    
        }
    }
    return inicio;
}
bool verificalistaDiagonal(NOM* teste, NOM* m){

    while(teste && m){
        if(teste->info != m->info) return false;
        teste = teste->proxC;
        m = m->proxC;
    }
    if((!teste && m) || (teste && !m)) return false;

    return true;
}

//verifica se a matriz é simétrica
//creio estar correto, entretanto revisa-lo-ei!
bool ehSimetrica(LISTASCR* m){
    if(!m || MAXLIN != MAXCOL) return false;

    for (int i = 1; i <= MAXCOL; i++){
        NOM* p1 = m->lin[i];
        NOM* p2 = m->col[i];

        while (p1 && p2){
            if((p1->info != p2->info) && (p1->lin != p2->col) && (p2->col != p1->lin)) return false;
            p1 = p1->proxC;
            p2 = p2->proxL;
        }
        if((!p1 && p2) || (p1 && !p2)) return false;
    }
    return true;
}

//verifica se a matriz é triangular superior
bool ehTriangularSuperior (LISTASCR* m){
    if(!m) return false;    // a matriz necessariamente deve ser quadrada
    for(int i = 1; i <= MAXLIN; i++){
        NOM* p = m->lin[i];
        while (p){
            if(p->lin > p->col) return false;
            p = p->proxC;
        }
    }
    return true;
}

// ... seus exercícios anteriores ...

void menuMatrizes() {
    printf("\n--- MENU MATRIZES ---\n");
    printf("1. Testar Diagonal\n");
    printf("0. Voltar\n");
    // Logica de teste aqui
    printf("Pressione ENTER para voltar...\n");
    fflush(stdin); getchar();
}