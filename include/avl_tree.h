//
// Created by Софья Фролова  on 26.03.2025.
//

#ifndef POLINOM_AVL_TREE_H
#define POLINOM_AVL_TREE_H

#include <iostream>
#include <algorithm>
#include <queue>

template <typename TKey, typename TValue>
struct TTableRec {
    TKey key;
    TValue value;

    TTableRec() = default;
    TTableRec(const TKey& k, const TValue& v) : key(k), value(v) {}

    bool operator==(const TTableRec& other) const {
        return key == other.key && value == other.value;
    }

    bool operator!=(const TTableRec& other) const {
        return !(*this == other);
    }
};

template <typename TKey, typename TValue>
struct Node {
    TTableRec<TKey, TValue> data;
    Node* left;
    Node* right;
    int height;

    Node(const TKey& key, const TValue& value)
            : data(key, value), left(nullptr), right(nullptr), height(1) {}
};

template <typename TKey, typename TValue>
class AVLTree {
private:
    Node<TKey, TValue>* root;
    size_t treeSize;

    int getHeight(Node<TKey, TValue>* node) const {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node<TKey, TValue>* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(Node<TKey, TValue>* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    Node<TKey, TValue>* rightRotate(Node<TKey, TValue>* y) {
        Node<TKey, TValue>* x = y->left;
        Node<TKey, TValue>* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node<TKey, TValue>* leftRotate(Node<TKey, TValue>* x) {
        Node<TKey, TValue>* y = x->right;
        Node<TKey, TValue>* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node<TKey, TValue>* balance(Node<TKey, TValue>* node) {
        if (!node) return nullptr;

        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }
        return node;
    }

    Node<TKey, TValue>* insert(Node<TKey, TValue>* node, const TKey& key, const TValue& value) {
        if (!node) {
            treeSize++;
            return new Node<TKey, TValue>(key, value);
        }

        if (key < node->data.key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->data.key) {
            node->right = insert(node->right, key, value);
        } else {
            throw std::runtime_error("Key already exists");
        }

        return balance(node);
    }

    Node<TKey, TValue>* findMin(Node<TKey, TValue>* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Node<TKey, TValue>* erase(Node<TKey, TValue>* node, const TKey& key) {
        if (!node) return nullptr;

        if (key < node->data.key) {
            node->left = erase(node->left, key);
        } else if (key > node->data.key) {
            node->right = erase(node->right, key);
        } else {
            if (!node->left || !node->right) {
                Node<TKey, TValue>* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
                treeSize--;
            } else {
                Node<TKey, TValue>* temp = findMin(node->right);
                node->data = temp->data;
                node->right = erase(node->right, temp->data.key);
            }
        }

        if (!node) return nullptr;

        return balance(node);
    }

    bool isEqual(Node<TKey, TValue>* node1, Node<TKey, TValue>* node2) const {
        if (!node1 && !node2) return true;
        if (!node1 || !node2) return false;
        return node1->data == node2->data &&
               isEqual(node1->left, node2->left) &&
               isEqual(node1->right, node2->right);
    }

    void print(Node<TKey, TValue>* node, std::ostream& os) const {
        if (node) {
            print(node->left, os);
            os << node->data.key << ": " << node->data.value << "\n";
            print(node->right, os);
        }
    }

    Node<TKey, TValue>* copyTree(Node<TKey, TValue>* node) const {
        if (!node) return nullptr;
        Node<TKey, TValue>* newNode = new Node<TKey, TValue>(node->data.key, node->data.value);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        newNode->height = node->height;
        return newNode;
    }

    void clearTree(Node<TKey, TValue>* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr), treeSize(0) {}
    AVLTree(const AVLTree& other) : root(copyTree(other.root)), treeSize(other.treeSize) {}
    ~AVLTree() { clearTree(root); }

    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            clearTree(root);
            root = copyTree(other.root);
            treeSize = other.treeSize;
        }
        return *this;
    }

    void insert(const TKey& key, const TValue& value) {
        root = insert(root, key, value);
    }

    void erase(const TKey& key) {
        root = erase(root, key);
    }

    size_t size() const {
        return treeSize;
    }

    int height() const {
        return getHeight(root);
    }

    TValue find(const TKey& key) const {
        Node<TKey, TValue>* current = root;
        while (current) {
            if (key < current->data.key) {
                current = current->left;
            } else if (key > current->data.key) {
                current = current->right;
            } else {
                return current->data.value;
            }
        }
        throw std::runtime_error("Key not found");
    }

    bool operator==(const AVLTree& other) const {
        return isEqual(root, other.root);
    }

    bool operator!=(const AVLTree& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const AVLTree& tree) {
        tree.print(tree.root, os);
        return os;
    }
};

#endif // POLINOM_AVL_TREE_H
