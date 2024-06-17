#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubro_negra.h"

// Função para inicializar a estrutura de informações
infos *initInfos() {
    infos *inf = (infos *)malloc(sizeof(infos));
    if (inf) {
        inf->rotations = 0;
    }
    return inf;
}

// Função para liberar a estrutura de informações
void freeInfos(infos *inf) {
    if (inf) {
        free(inf);
    }
}

// Função para gerar números aleatórios
int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    char fileName[100];

    // Solicita ao usuário o nome do arquivo de entrada
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", fileName);

    // Tenta abrir o arquivo para leitura
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Cria uma árvore Rubro-Negra vazia
    arvoreRN *arvore = criaArv();
    if (arvore == NULL) {
        fprintf(stderr, "Falha ao criar a árvore Rubro-Negra\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Cria a estrutura de informações
    infos *informacoes = initInfos();
    if (informacoes == NULL) {
        fprintf(stderr, "Erro ao criar a estrutura de informações\n");
        fclose(file);
        free(arvore->sentinela);
        free(arvore);
        exit(EXIT_FAILURE);
    }

    int value;
    clock_t start, end;
    double cpu_time_used;

    // Inicia a contagem do tempo para inserção
    start = clock();

    // Lê valores do arquivo e os insere na árvore Rubro-Negra
    while (fscanf(file, "%d", &value) == 1) {
        if (!insereNoRN(arvore, value, informacoes)) {
            fprintf(stderr, "Erro ao inserir o valor %d na árvore\n", value);
        }
    }

    // Termina a contagem do tempo para inserção
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Imprime o tempo de inserção e a quantidade de rotações
    printf("Tempo de inserção: %f segundos\n", cpu_time_used);
    printf("Quantidade de rotações para inserção: %d\n", informacoes->rotations);

    // Fecha o arquivo e o reabre para leitura dos valores para busca
    fclose(file);
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        freeInfos(informacoes);
        free(arvore->sentinela);
        free(arvore);
        exit(EXIT_FAILURE);
    }

    // Reseta o contador de rotações
    informacoes->rotations = 0;

    // Inicia a contagem do tempo para busca
    start = clock();

    // Realiza 1000 buscas aleatórias na árvore Rubro-Negra
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    for (int i = 0; i < 1000; ++i) {
        int randomKey = randomInt(1, 1000000); // Suponha que suas chaves estejam nesse intervalo
        noRN *result = searchRN(arvore, randomKey);
        // Se desejar imprimir os resultados das buscas, descomente a linha abaixo
        // if (result != NULL) printf("Chave encontrada: %d\n", result->chave);
    }

    // Termina a contagem do tempo para busca
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de busca: %f segundos\n", cpu_time_used);

    // Libera os recursos e fecha o arquivo
    freeInfos(informacoes);
    liberaArv(arvore);
    fclose(file);

    return 0;
}
