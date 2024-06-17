#include "rubro_negra.h"
#include <stdlib.h>
#include <stdio.h>

arvoreRN *criaArv() {
    arvoreRN *arv = (arvoreRN *)malloc(sizeof(arvoreRN));
    if (!arv) {
        return NULL;
    }
    arv->numElementos = 0;
    arv->sentinela = (noRN *)malloc(sizeof(noRN));
    if (!arv->sentinela) {
        free(arv);
        return NULL;
    }
    arv->sentinela->chave = -1000;
    arv->sentinela->dir = arv->sentinela->esq = arv->sentinela->pai = NULL;
    arv->sentinela->cor = 'b';
    return arv;
}

void liberaArv(arvoreRN *arv) {
    if (arv) {
        if (arv->sentinela) {
            free(arv->sentinela);
        }
        free(arv);
    }
}

int insereNoRN(arvoreRN *arv, int chave, infos *inf) {
    noRN *aux1, *aux2, *novo = (noRN *)malloc(sizeof(noRN));
    if (!novo) {
        return 0;
    }
    novo->dir = novo->esq = NULL;
    novo->chave = chave;
    novo->cor = 'r';
    if (!arv->sentinela->dir) {
        novo->pai = arv->sentinela;
        arv->sentinela->dir = novo;
    } else {
        aux2 = arv->sentinela->dir;
        while (aux2) {
            aux1 = aux2;
            if (aux2->chave <= chave) {
                aux2 = aux2->dir;
            } else {
                aux2 = aux2->esq;
            }
        }
        novo->pai = aux1;
        if (aux1->chave <= chave) {
            aux1->dir = novo;
        } else {
            aux1->esq = novo;
        }
    }
    arv->numElementos++;
    analisaRN_Insercao(arv, novo, inf);
    return 1;
}

int removeNoRN(arvoreRN *arv, int valor, infos *inf) {
    noRN *atual, *aux = NULL;
    if (arv->numElementos) {
        atual = arv->sentinela->dir;
        while (atual && atual->chave != valor) {
            if (atual->chave > valor) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }
        if (atual) {
            if (!atual->dir && !atual->esq) {
                if (atual == atual->pai->dir) {
                    atual->pai->dir = NULL;
                } else {
                    atual->pai->esq = NULL;
                }
            } else if (atual->dir && atual->esq) {
                aux = atual;
                atual = atual->dir;
                while (atual->esq) {
                    atual = atual->esq;
                }
                aux->chave = atual->chave;
                if (atual == atual->pai->dir) {
                    atual->pai->dir = atual->dir;
                } else {
                    atual->pai->esq = atual->dir;
                }
                if (atual->dir) {
                    atual->dir->pai = atual->pai;
                }
            } else if (atual->dir) {
                if (atual == atual->pai->dir) {
                    atual->pai->dir = atual->dir;
                } else {
                    atual->pai->esq = atual->dir;
                }
                atual->dir->pai = atual->pai;
            } else {
                if (atual == atual->pai->dir) {
                    atual->pai->dir = atual->esq;
                } else {
                    atual->pai->esq = atual->esq;
                }
                atual->esq->pai = atual->pai;
            }
            arv->numElementos--;
            if (atual->cor == 'b') {
                analisaRN_Remocao(arv, atual, inf);
            }
            free(atual);
            atual = NULL;
            return 1;
        }
        return -1;
    }
    return 0;
}

int consultaRN(arvoreRN *arv, int chave) {
    noRN *aux;
    if (arv->numElementos) {
        aux = arv->sentinela->dir;
        while (aux && aux->chave != chave) {
            if (aux->chave < chave) {
                aux = aux->dir;
            } else {
                aux = aux->esq;
            }
        }
        if (aux) {
            return 1;
        }
        return -1;
    }
    return 0;
}

void rotacaoDir(arvoreRN *arv, noRN *p) {
    noRN *aux = p->esq;
    p->esq = aux->dir;
    if (aux->dir) {
        aux->dir->pai = p;
    }
    aux->pai = p->pai;
    if (p == p->pai->dir) {
        p->pai->dir = aux;
    } else {
        p->pai->esq = aux;
    }
    aux->dir = p;
    p->pai = aux;
}

void rotacaoEsq(arvoreRN *arv, noRN *p) {
    noRN *aux = p->dir;
    p->dir = aux->esq;
    if (aux->esq) {
        aux->esq->pai = p;
    }
    aux->pai = p->pai;
    if (p == p->pai->dir) {
        p->pai->dir = aux;
    } else {
        p->pai->esq = aux;
    }
    aux->esq = p;
    p->pai = aux;
}

void analisaRN_Insercao(arvoreRN *arv, noRN *p, infos *inf) {
    noRN *pai, *avo, *tio;
    while (p->pai->cor == 'r') {
        pai = p->pai;
        avo = pai->pai;
        if (avo->esq == pai) {
            tio = avo->dir;
        } else {
            tio = avo->esq;
        }
        if (tio && tio->cor == 'r') {
            pai->cor = tio->cor = 'b';
            avo->cor = 'r';
            p = avo;
        } else {
            if (pai == avo->esq && p == pai->esq) {
                pai->cor = 'b';
                avo->cor = 'r';
                rotacaoDir(arv, avo);
                inf->rotations++;
            } else if (pai == avo->dir && p == pai->dir) {
                pai->cor = 'b';
                avo->cor = 'r';
                rotacaoEsq(arv, avo);
                inf->rotations++;
            } else if (pai == avo->esq && p == pai->dir) {
                p->cor = 'b';
                avo->cor = 'r';
                rotacaoEsq(arv, pai);
                inf->rotations++;
                rotacaoDir(arv, avo);
                inf->rotations++;
            } else {
                p->cor = 'b';
                avo->cor = 'r';
                rotacaoDir(arv, pai);
                inf->rotations++;
                rotacaoEsq(arv, avo);
                inf->rotations++;
            }
        }
    }
    arv->sentinela->dir->cor = 'b';
}

void analisaRN_Remocao(arvoreRN *arv, noRN *p, infos *inf) {
    noRN *irmao;
    while (p != arv->sentinela->dir && p->cor == 'b') {
        if (p == p->pai->esq) {
            irmao = p->pai->dir;
            if (irmao->cor == 'r') {
                irmao->cor = 'b';
                p->pai->cor = 'r';
                rotacaoEsq(arv, p->pai);
                inf->rotations++;
                irmao = p->pai->dir;
            }
            if ((!irmao->esq || irmao->esq->cor == 'b') && (!irmao->dir || irmao->dir->cor == 'b')) {
                irmao->cor = 'r';
                p = p->pai;
            } else {
                if (!irmao->dir || irmao->dir->cor == 'b') {
                    if (irmao->esq) {
                        irmao->esq->cor = 'b';
                    }
                    irmao->cor = 'r';
                    rotacaoDir(arv, irmao);
                    inf->rotations++;
                    irmao = p->pai->dir;
                }
                irmao->cor = p->pai->cor;
                p->pai->cor = 'b';
                if (irmao->dir) {
                    irmao->dir->cor = 'b';
                }
                rotacaoEsq(arv, p->pai);
                inf->rotations++;
                p = arv->sentinela->dir;
            }
        } else {
            irmao = p->pai->esq;
            if (irmao->cor == 'r') {
                irmao->cor = 'b';
                p->pai->cor = 'r';
                rotacaoDir(arv, p->pai);
                inf->rotations++;
                irmao = p->pai->esq;
            }
            if ((!irmao->esq || irmao->esq->cor == 'b') && (!irmao->dir || irmao->dir->cor == 'b')) {
                irmao->cor = 'r';
                p = p->pai;
            } else {
                if (!irmao->esq || irmao->esq->cor == 'b') {
                    if (irmao->dir) {
                        irmao->dir->cor = 'b';
                    }
                    irmao->cor = 'r';
                    rotacaoEsq(arv, irmao);
                    inf->rotations++;
                    irmao = p->pai->esq;
                }
                irmao->cor = p->pai->cor;
                p->pai->cor = 'b';
                if (irmao->esq) {
                    irmao->esq->cor = 'b';
                }
                rotacaoDir(arv, p->pai);
                inf->rotations++;
                p = arv->sentinela->dir;
            }
        }
    }
    p->cor = 'b';
}
noRN *searchRN(arvoreRN *arv, int chave) {
    noRN *atual = arv->sentinela->dir;

    while (atual != NULL && atual != arv->sentinela) {
        if (chave == atual->chave) {
            return atual;
        } else if (chave < atual->chave) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    return NULL; // Elemento não encontrado
}
