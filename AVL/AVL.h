#ifndef AVL_H
#define AVL_H

#include <time.h>

// Definição da estrutura do nó da árvore AVL
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Definição da estrutura da árvore AVL
typedef struct AVLTree {
    Node* root;
} AVLTree;

// Contador de rotações
extern int rotationCount;

// Função para criar uma árvore AVL vazia
AVLTree* createAVLTree();

// Função para inserir um novo nó na árvore AVL
void insertIntoAVL(AVLTree* tree, int key);

// Função para remover um nó da árvore AVL
void removeFromAVL(AVLTree* tree, int key);

// Função para liberar a memória alocada pela árvore AVL
void destroyAVLTree(AVLTree* tree);

// Função para percorrer a árvore AVL em ordem
void inorderTraversal(Node* node);

// Função para obter e resetar o contador de rotações
int getRotationCount();
void resetRotationCount();

#endif
