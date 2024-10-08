#ifndef AVL_H
#define AVL_H

#include <vector>

template <typename T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(T value);
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    // Funciones auxiliares
    int height(AVLNode<T>* node) const;
    int getBalance(AVLNode<T>* node) const;

    AVLNode<T>* rightRotate(AVLNode<T>* y);
    AVLNode<T>* leftRotate(AVLNode<T>* x);

    AVLNode<T>* minValueNode(AVLNode<T>* node);

    AVLNode<T>* insert(AVLNode<T>* node, T key);
    AVLNode<T>* remove(AVLNode<T>* node, T key);
    bool search(AVLNode<T>* node, T key) const;

    void inorder(AVLNode<T>* node, std::vector<T>& ret) const;

public:
    AVLTree();

    void insert(T key);
    void remove(T key);
    bool search(T key) const;
    std::vector<T> inorderTraversal() const;
    int height() const;
};

#include "avl_impl.h"

#endif