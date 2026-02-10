#ifndef JUIZ_H
#define JUIZ_H

// Lê o arquivo txt e devolve uma string
char* lerCodigoDoAluno(const char* nomeArquivo);

// Compila e roda o teste
int rodarJuiz(const char* headers, const char* codigoAluno, const char* mainTeste);

#endif