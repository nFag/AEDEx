#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// --- INCLUSÃO DOS SEUS MÓDULOS ---
// O main precisa conhecer o "cardápio" de cada arquivo .h
#include "listas.h"
#include "pilhas.h"
#include "filas.h"
#include "listasGen.h"
#include "arvores.h"
#include "matrizes.h"

// Função simples para dar créditos
void creditos() {
    system("cls");
    printf("=========================================\n");
    printf("      SOBRE O PROJETO AED 1             \n");
    printf("=========================================\n");
    printf("Este portfolio reune implementacoes de:\n");
    printf(" - Listas, Pilhas, Filas\n");
    printf(" - Listas Generalizadas\n");
    printf(" - Arvores Binarias e AVL\n");
    printf(" - Matrizes Esparsas\n\n");
    printf("Para a disciplina de AED I.\n");
    printf("Desenvolvido por mim\n");
    printf("=========================================\n");
    printf("\nPRESSIONE ENTER PARA VOLTAR...");
    fflush(stdin);
    getchar();
}

void VOCENAOESTAPREPARADO(){
    printf("VOCE NAO ESTA PREPARADO");
    system("pause");
}

int main() {
    printf("O PROGRAMA INICIOU!!!\n"); // Adicione isso para testar
    // Configura acentuação para português
    setlocale(LC_ALL, "Portuguese");
    
    int opcao = -1;

    do {
        system("cls"); // Limpa a tela (Windows)
        
        // ASCII ART para dar estilo
        printf("\n");
        printf("   ALGORITMOS E ESTRUTURA DE DADOS   \n");
        printf("   ---------------------------------   \n");
        printf("   Selecione o modulo para revisar:        \n\n");
        
        printf("   [1] Listas Ligadas\n");
        printf("   [2] Pilhas\n");
        printf("   [3] Filas\n");
        printf("   [4] Listas Generalizadas\n");
        printf("   [5] Matrizes Esparsas\n");
        printf("   [6] Arvores\n");
        printf("   ---------------------------------\n");
        printf("   [9] Creditos / Sobre\n");
        printf("   [0] SAIR\n");
        
        printf("\n>> Digite sua opcao: ");
        scanf("%d", &opcao);
        fflush(stdin); // Limpa buffer do teclado

        switch (opcao) {
            case 1:
                menuListas(); 
                break;
            case 2:
                menuPilhas();
                break;
            case 3:
                menuFilas();
                break;
            case 4:
                menuListasGen();
                break;
            case 5:
                menuMatrizes();
                break;
            case 6:
                menuArvores();
                break;
            case 7:
                VOCENAOESTAPREPARADO();
                break;
            case 9:
                creditos();
                break;
            case 0:
                printf("\nEncerrando o programa... Bons estudos!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                getchar(); // Pausa rápida
                break;
        }

    } while (opcao != 0);

    return 0;
}