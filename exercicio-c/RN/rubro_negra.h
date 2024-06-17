#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H

// Definição da estrutura para informações adicionais
typedef struct {
    int rotations;  // Contador de rotações
} infos;

// Definição da estrutura do nó da árvore Rubro-Negra
typedef struct noRN {
    int chave;
    char cor;
    struct noRN *esq, *dir, *pai;
} noRN;

// Definição da estrutura da árvore Rubro-Negra
typedef struct {
    noRN *sentinela;
    int numElementos;
} arvoreRN;

// Funções para manipulação da árvore Rubro-Negra
arvoreRN *criaArv();
void liberaArv(arvoreRN *arv);
int insereNoRN(arvoreRN *arv, int chave, infos *inf);
int removeNoRN(arvoreRN *arv, int valor, infos *inf);
int consultaRN(arvoreRN *arv, int chave);
void rotacaoDir(arvoreRN *arv, noRN *p);
void rotacaoEsq(arvoreRN *arv, noRN *p);
void analisaRN_Insercao(arvoreRN *arv, noRN *p, infos *inf);
void analisaRN_Remocao(arvoreRN *arv, noRN *p, infos *inf);
noRN *searchRN(arvoreRN *arv, int chave);


#endif // RUBRO_NEGRA_H
