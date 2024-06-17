#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

// Inicialização do contador de rotações
int rotationCount = 0;

// Função para criar uma árvore AVL vazia
AVLTree* createAVLTree() {
    AVLTree* tree = (AVLTree*)malloc(sizeof(AVLTree));
    if (tree != NULL) {
        tree->root = NULL;
    }
    return tree;
}

// Função para criar um novo nó
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Função para obter a altura de um nó
int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Função para obter o fator de balanceamento de um nó
int getBalanceFactor(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Função para atualizar a altura de um nó
void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Função para fazer uma rotação simples à direita
Node* rotateRight(Node* node) {
    rotationCount++;
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Função para fazer uma rotação simples à esquerda
Node* rotateLeft(Node* node) {
    rotationCount++;
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Função para balancear um nó
Node* balanceNode(Node* node) {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

// Função para inserir um nó na árvore AVL
Node* insertNode(Node* node, int key) {
    if (node == NULL) {
        return newNode(key);
    }
    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        return node;
    }
    return balanceNode(node);
}

// Função para inserir um novo nó na árvore AVL
void insertIntoAVL(AVLTree* tree, int key) {
    if (tree == NULL) {
        return;
    }
    tree->root = insertNode(tree->root, key);
}

// Função para encontrar o nó com o valor mínimo
Node* findMin(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Função para remover um nó da árvore AVL
Node* deleteNode(Node* node, int key) {
    if (node == NULL) {
        return node;
    }
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (node->left == NULL || node->right == NULL) {
            Node* temp = node->left ? node->left : node->right;
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp;
            }
            free(temp);
        } else {
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }
    if (node == NULL) {
        return node;
    }
    return balanceNode(node);
}

// Função para remover um nó da árvore AVL
void removeFromAVL(AVLTree* tree, int key) {
    if (tree == NULL) {
        return;
    }
    tree->root = deleteNode(tree->root, key);
}

// Função para percorrer a árvore em ordem
void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->key);
        inorderTraversal(node->right);
    }
}

// Função para liberar a memória alocada pela árvore AVL
void freeTree(Node* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

// Função para liberar a memória alocada pela árvore AVL
void destroyAVLTree(AVLTree* tree) {
    if (tree != NULL) {
        freeTree(tree->root);
        free(tree);
    }
}

// Função para obter o contador de rotações
int getRotationCount() {
    return rotationCount;
}

// Função para resetar o contador de rotações
void resetRotationCount() {
    rotationCount = 0;
}
// Função para buscar um elemento na árvore AVL
Node* searchInAVL(Node* node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return searchInAVL(node->left, key);
    }
    return searchInAVL(node->right, key);
}

// Função para buscar um elemento na árvore AVL
Node* searchAVL(AVLTree* tree, int key) {
    if (tree == NULL) {
        return NULL;
    }
    return searchInAVL(tree->root, key);
}

