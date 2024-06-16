#include <stdio.h>

int main() {
    FILE *file = fopen("entrada_ordenada.txt", "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return 1;
    }

    for (int i = 1; i <= 10000; i++) {
        fprintf(file, "%d\n", i);
    }

    fclose(file);
    printf("Arquivo de entrada com 10000 valores ordenados foi gerado com sucesso.\n");

    return 0;
}
