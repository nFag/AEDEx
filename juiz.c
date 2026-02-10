#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juiz.h"

#define MAX_BUFFER 10000

char* lerCodigoDoAluno(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) return NULL;

    // Aloca memória na HEAP (Memória dinâmica)
    char* buffer = (char*)malloc(MAX_BUFFER * sizeof(char));
    
    // Verificação de segurança (caso falte memória no PC)
    if (!buffer) { 
        fclose(f);
        return NULL;
    }

    buffer[0] = '\0'; // Inicializa string vazia

    char linha[256];
    int tamanhoAtual = 0;

    // 2. SEGURANÇA CONTRA ESTOURO DE BUFFER
    while (fgets(linha, sizeof(linha), f)) {
        int tamLinha = strlen(linha);
        
        // Só concatena se couber no buffer
        if (tamanhoAtual + tamLinha < MAX_BUFFER - 1) {
            strcat(buffer, linha);
            tamanhoAtual += tamLinha;
        } else {
            // Opcional: Avisar que o código foi cortado
            printf("\n[AVISO] O codigo do aluno e muito grande e foi cortado.\n");
            break;
        }
    }
    
    fclose(f);
    return buffer; // Retorna o texto completo
}

int rodarJuiz(const char* headers, const char* codigoAluno, const char* mainTeste) {
    // ---------------------------------------------------------
    // PASSO 1: CRIAR O ARQUIVO "FRANKENSTEIN"
    // ---------------------------------------------------------
    FILE* f = fopen("temp_teste.c", "w");
    if (!f) {
        printf("[ERRO INTERNO] Nao foi possivel criar arquivo temporario.\n");
        return -2;
    }

    // Escreve as 3 partes
    fprintf(f, "%s\n", headers);      // 1. Structs
    fprintf(f, "\n// --- CODIGO DO ALUNO ---\n");
    fprintf(f, "%s\n", codigoAluno);  // 2. Função do aluno
    fprintf(f, "\n// --- TESTE AUTOMATICO ---\n");
    fprintf(f, "%s\n", mainTeste);    // 3. Main de teste
    
    fclose(f);

    // ---------------------------------------------------------
    // PASSO 2: COMPILAR
    // ---------------------------------------------------------
    // Sem o "2>nul", os erros aparecem na tela pro aluno. Perfeito.
    printf("\n>>> COMPILANDO... <<<\n"); 
    int erroCompilacao = system("gcc temp_teste.c -o temp_teste.exe");

    if (erroCompilacao != 0) {
        return -1; // Erro de sintaxe (o aluno já viu o erro no terminal)
    }

    // ---------------------------------------------------------
    // PASSO 3: EXECUTAR
    // ---------------------------------------------------------
    printf(">>> EXECUTANDO TESTE... <<<\n");
    int resultado = system("temp_teste.exe");

    // ---------------------------------------------------------
    // PASSO 4: LIMPEZA
    // ---------------------------------------------------------
    remove("temp_teste.c");
    remove("temp_teste.exe");

    return resultado; // 0 = Sucesso, 1 = Falha Lógica
}