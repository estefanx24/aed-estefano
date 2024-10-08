#ifndef AVL_IMPL_H
#define AVL_IMPL_H

#include <algorithm>

#include "avl.h"

// Constructor de AVLNode
template <typename T>
AVLNode<T>::AVLNode(T value)
        : data(value), left(nullptr), right(nullptr), height(1) {} // Altura inicial es 1

// Constructor de AVLTree
template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

// Función para obtener la altura de un nodo
template <typename T>
int AVLTree<T>::height(AVLNode<T>* node) const {
    if (node == nullptr)
        return 0; // La altura de un árbol vacío es 0
    return node->height;
}

// Función para obtener el factor de balance de un nodo
template <typename T>
int AVLTree<T>::getBalance(AVLNode<T>* node) const {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Rotación a la derecha
template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y) {
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    // Realizar rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}

// Rotación a la izquierda
template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x) {
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    // Realizar rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;
}

// Función para encontrar el nodo con el valor mínimo
template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
    AVLNode<T>* current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Inserción en el árbol AVL
template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T key) {
    // 1. Realizar inserción BST normal
    if (node == nullptr)
        return new AVLNode<T>(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else // No se permiten valores duplicados
        return node;

    // 2. Actualizar la altura del nodo actual
    node->height = 1 + std::max(height(node->left), height(node->right));

    // 3. Obtener el factor de balance
    int balance = getBalance(node);

    // 4. Balancear el árbol
    // Caso Izquierda Izquierda
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // Caso Derecha Derecha
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // Caso Izquierda Derecha
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Derecha Izquierda
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Eliminación en el árbol AVL
template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* node, T key) {
    // 1. Realizar eliminación BST normal
    if (node == nullptr)
        return node;

    if (key < node->data)
        node->left = remove(node->left, key);
    else if (key > node->data)
        node->right = remove(node->right, key);
    else {
        // Nodo con solo un hijo o sin hijos
        if ((node->left == nullptr) || (node->right == nullptr)) {
            AVLNode<T>* temp = node->left ? node->left : node->right;

            // Sin hijo
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else { // Un hijo
                *node = *temp;
            }
            delete temp;
        } else {
            // Nodo con dos hijos: Obtener el sucesor en inorden
            AVLNode<T>* temp = minValueNode(node->right);

            // Copiar los datos del sucesor al nodo actual
            node->data = temp->data;

            // Eliminar el sucesor
            node->right = remove(node->right, temp->data);
        }
    }

    if (node == nullptr)
        return node;

    // 2. Actualizar la altura del nodo actual
    node->height = 1 + std::max(height(node->left), height(node->right));

    // 3. Obtener el factor de balance
    int balance = getBalance(node);

    // 4. Balancear el árbol
    // Izquierda Izquierda
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // Izquierda Derecha
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Derecha Derecha
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // Derecha Izquierda
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Búsqueda en el árbol AVL
template <typename T>
bool AVLTree<T>::search(AVLNode<T>* node, T key) const {
    if (node == nullptr)
        return false;
    if (key == node->data)
        return true;
    else if (key < node->data)
        return search(node->left, key);
    else
        return search(node->right, key);
}

// Recorrido inorder
template <typename T>
void AVLTree<T>::inorder(AVLNode<T>* node, std::vector<T>& ret) const {
    if (node != nullptr) {
        inorder(node->left, ret);
        ret.push_back(node->data);
        inorder(node->right, ret);
    }
}

// Funciones públicas

template <typename T>
void AVLTree<T>::insert(T key) {
    root = insert(root, key);
}

template <typename T>
void AVLTree<T>::remove(T key) {
    root = remove(root, key);
}

template <typename T>
bool AVLTree<T>::search(T key) const {
    return search(root, key);
}

template <typename T>
std::vector<T> AVLTree<T>::inorderTraversal() const {
    std::vector<T> result;
    inorder(root, result);
    return result;
}

template <typename T>
int AVLTree<T>::height() const {
    return height(root);
}

#endif