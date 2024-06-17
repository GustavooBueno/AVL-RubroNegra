#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL.h"

#define NUM_SEARCHES 1000

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

    // Cria uma árvore AVL vazia
    AVLTree* avlTree = createAVLTree();
    if (avlTree == NULL) {
        fprintf(stderr, "Falha ao criar a árvore AVL\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int value;
    clock_t start, end;
    double cpu_time_used;

    // Inicia a contagem do tempo para inserção na AVL
    start = clock();

    // Lê valores do arquivo e os insere na árvore AVL
    while (fscanf(file, "%d", &value) == 1) {
        insertIntoAVL(avlTree, value);
    }

    // Termina a contagem do tempo para inserção na AVL
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de inserção na AVL: %f segundos\n", cpu_time_used);

    // Fecha e reabre o arquivo para leitura dos valores para busca
    fclose(file);
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        destroyAVLTree(avlTree);
        exit(EXIT_FAILURE);
    }

    // Inicia a contagem do tempo para busca na AVL
    start = clock();

    // Realiza 1000 buscas aleatórias na AVL
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    for (int i = 0; i < NUM_SEARCHES; ++i) {
        int randomKey = randomInt(1, 1000000); // Suponha que suas chaves estejam nesse intervalo
        Node* result = searchAVL(avlTree, randomKey);
        // Se desejar imprimir os resultados das buscas, descomente a linha abaixo
        // if (result != NULL) printf("Chave encontrada: %d\n", result->key);
    }

    // Termina a contagem do tempo para busca na AVL
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de busca na AVL: %f segundos\n", cpu_time_used);

    // Libera os recursos e fecha o arquivo
    destroyAVLTree(avlTree);
    fclose(file);

    return 0;
}
