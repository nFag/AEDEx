/*
// MATRIZ EM LINHAS CRUZADAS
int somaColuna (MATRIZ* m, int k){
    if(!m || k > MAXCOL) return 0;
    int soma = 0;

    NO* p = m->col[k];
    while(p){
        soma = soma + p->info;
        p = p->proxL;
    }
    return soma;
}

int somaLinha (MATRIZ* m, int k){
    if(!m || k > MAXLIN) return 0;
    int soma = 0;

    NO* p = m->lin[k];
    while(p){
        soma = soma + p->info;
        p = p->proxC;
    }
    return soma;
}
*/