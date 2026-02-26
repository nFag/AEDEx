#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "arvores.h"
#include "juiz.h"

// --- HEADER PADRÃO (O que vai no topo do arquivo TEMP) ---
const char* HEADER_ARVORE = 
    "#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "#include <stdbool.h>\n"
    
    "typedef struct no_arvore { int chave; struct no_arvore *esq, *dir; } NOA;\n"
    
    "NOA* novoNo(int k) { NOA* n=(NOA*)malloc(sizeof(NOA));\n"
    " n->chave=k;\n"
    " n->esq=NULL;\n"
    " n->dir=NULL;\n"
    " return n; }\n"

    "NOA* gerarArvore(int tipo) {\n"

    "    if (tipo == 1) return NULL;\n"

    "    // ARVORE 2: Apenas um no (Folha unica)\n"
    "    if (tipo == 2) return novoNo(10);\n"
    
    "    // ARVORE 3: Pequena (3 nos)\n"
    "    if (tipo == 3) {\n"
    "        NOA* r = novoNo(10);\n"
    "        r->esq = novoNo(5); r->dir = novoNo(15);\n"
    "        return r;\n"
    "    }\n"

    "    // ARVORE 4: Torta para a esquerda (4 nos)\n"
    "    if (tipo == 4) {\n"
    "        NOA* r = novoNo(10);\n"
    "        r->esq = novoNo(8);\n"
    "        r->esq->esq = novoNo(5);\n"
    "        r->esq->esq->esq = novoNo(2);\n"
    "        return r;\n"
    "    }\n"

    "    // ARVORE 5: Arvore Binaria de Busca grande (7 nos)\n"
    "    if (tipo == 5) {\n"
    "        NOA* r = novoNo(10);\n"
    "        r->esq = novoNo(5);\n"
    "        r->dir = novoNo(20);\n"
    "        r->esq->esq = novoNo(2);\n"
    "        r->esq->dir = novoNo(7);\n"
    "        r->dir->esq = novoNo(15);\n"
    "        r->dir->dir = novoNo(25);\n"
    "        return r;\n"
    "    }\n"

    "    return NULL;\n"
    "}\n"
    ;


// --- ESTRUTURA DE UMA QUESTÃO ---
typedef struct {
    char* titulo;
    char* enunciado;
    const char* teste;   // O main() que testa o aluno
} QUESTAO;

// --- BANCO DE QUESTÕES ---
QUESTAO dbArvores[] = {
    // retorna 1 se falhou
    // retorna 0 se passou

    // QUESTÃO 0: Arvore Vazia
    {
        "Arvore Vazia",
        "Escreva 'bool funcao(NOA* raiz)' que retorne true se for vazia e false se não for.",
        
        // GABARITO (TESTE):
        "int main() {\n"
        "    if (funcao(gerarArvore(1)) == false) return 1;\n"
        "    gerarArvore(2);\n"
        "    if (funcao(gerarArvore(2)) == true) return 1;\n"
        "    return 0; //sucesso\n"
        "}\n"
    },

    // QUESTÃO : Lista de Folhas
    {
        "Lista Folhas",
        "Escreva 'NOA* funcao(NOA* raiz)' que retorne uma lista ligada apenas com as folhas (a ordem não importa).\nUse os ponteiros da propria estrutura (esq aponta para o proximo).",
        
        // GABARITO (TESTE):
        "int main() {\n"
        "    NOA* teste1 = gerarArvore(1);\n"
        "    if(funcao(teste1)) return 1;\n"
        "    NOA* teste2 = gerarArvore(5);\n"
        "    NOA* lista = funcao(teste2);\n"
        "       int count = 0;\n"
        "       int soma = 0;\n"
        "       while (lista != NULL) {\n"
        "           count++;\n"
        "           soma += lista->chave;\n"
        "           lista = lista->esq;\n"
        "       }\n"
        "       if (soma != 49) return 1; // Espera soma das folhas: 2 + 7 + 15 + 25 = 52\n"
        "       if (count != 4) return 1; // Espera 4 folhas\n"
        "       return 0;\n"
        "}\n"
    }
};

// Calcula automaticamente quantas questões tem no vetor
int TOTAL_QUESTOES_ARV = sizeof(dbArvores) / sizeof(QUESTAO);

// --- MENU DINÂMICO ---
void menuArvores() {
    int opcao = -1;

    do {
        system("cls");
        printf("=== EXERCÍCIOS DE ARVORES ===\n");
        
        // Loop para imprimir o menu baseado no vetor
        for (int i = 0; i < TOTAL_QUESTOES_ARV; i++) {
            printf("[%d] %s\n", i + 1, dbArvores[i].titulo);
        }
        printf("[0] Voltar\n");
        printf("\nEscolha o exercicio: ");
        scanf("%d", &opcao);
        fflush(stdin);

        if (opcao > 0 && opcao <= TOTAL_QUESTOES_ARV) {
            int i = opcao - 1; // Ajuste do índice
            
            system("cls");
            printf(">>> EXERCICIO: %s <<<\n", dbArvores[i].titulo);
            printf("%s\n\n", dbArvores[i].enunciado);
            printf("------------------------------------------------------------------------\n");
            printf("IMPORTANTE: O nome da funcao que retornará a resposta deve ser 'funcao'.\n");
            printf("------------------------------------------------------------------------\n");
            system("pause");

            // 1. Cria arquivo pro aluno
            FILE* f = fopen("resposta.txt", "w");
            // Cria um esqueleto baseado na pergunta para ajudar o aluno
            if (i == 0) fprintf(f, "bool funcao(NOA* raiz) {\n    // Seu codigo...\n}\n");
            else fprintf(f, "NOA* funcao(NOA* raiz) {\n    // Seu codigo...\n}\n");
            fclose(f);
            
            // 2. Abre Notepad
            system("notepad.exe resposta.txt");
            printf("Pressione ENTER para corrigir...");
            getchar();

            // 3. Lê e Chama o Juiz
            char* codigo = lerCodigoDoAluno("resposta.txt");
            if (codigo) {
                // Passa: HEADER + CODIGO ALUNO + TESTE DA QUESTAO ESPECIFICA
                int veredito = rodarJuiz(HEADER_ARVORE, codigo, dbArvores[i].teste);
                
                if (veredito == 0) printf("\n[SUCESSO] Parabens! Voce acertou.\n");
                else if (veredito == -1) printf("\n[ERRO DE SINTAXE] Nao compilou.\n");
                else printf("\n[FALHA] Sua logica nao passou no teste.\n");
                
                free(codigo);
                system("pause");
            }
        }

    } while (opcao != 0);
}


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
