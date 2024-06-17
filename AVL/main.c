#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL.h"

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

    // Cria uma árvore AVL vazia
    AVLTree* tree = createAVLTree();
    if (tree == NULL) {
        fprintf(stderr, "Falha ao criar a árvore AVL\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int value;
    clock_t start, end;
    double cpu_time_used;

    // Reseta o contador de rotações
    resetRotationCount();

    // Inicia a contagem do tempo
    start = clock();

    // Lê valores do arquivo e os insere na árvore AVL
    while (fscanf(file, "%d", &value) == 1) {
        insertIntoAVL(tree, value);
    }

    // Termina a contagem do tempo
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Imprime o tempo de inserção e a quantidade de rotações
    printf("Tempo de inserção: %f segundos\n", cpu_time_used);
    printf("Quantidade de rotações para inserção: %d\n", getRotationCount());

    // Fecha e reabre o arquivo para leitura dos valores para remoção
    fclose(file);
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        destroyAVLTree(tree);
        exit(EXIT_FAILURE);
    }

    // Reseta o contador de rotações
    resetRotationCount();

    // Inicia a contagem do tempo para remoção
    start = clock();

    // Lê valores do arquivo e os remove da árvore AVL
    while (fscanf(file, "%d", &value) == 1) {
        removeFromAVL(tree, value);
    }

    // Termina a contagem do tempo para remoção
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Imprime o tempo de remoção e a quantidade de rotações
    printf("Tempo de remoção: %f segundos\n", cpu_time_used);
    printf("Quantidade de rotações para remoção: %d\n", getRotationCount());

    // Libera os recursos e fecha o arquivo
    destroyAVLTree(tree);
    fclose(file);

    return 0;
}
