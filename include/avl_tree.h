//
// Created by Софья Фролова  on 26.03.2025.
//

#ifndef POLINOM_AVL_TREE_H
#define POLINOM_AVL_TREE_H

#include "polinom.h"
#include "list.h"
#include <list>
#include <algorithm>
#include <utility>

template <class Tkey, class Tvalue>
class AVLTree {
private:
    struct TTableRec {
        Tkey key;
        Tvalue value;
    };

    struct Node {
        TTableRec data;
        Node* left;
        Node* right;
        int height;

        Node() {
            left = nullptr;
            right = nullptr;
            height = 1;
            data.key = 1;
            data.value = "";
        }
    };

    Node* root;

     Tvalue find (Tkey key, Node* curr) {
        if (!curr) throw "This tree doesn't exist";
        if (key == curr->data.key) {return curr->data.value;}
        if (key < curr->data.key) {return find(key, curr->left);}
        if (key > curr->data.key) {return find(key, curr->right);}
    }

    Node* insert(Node* curr, Tkey key, Tvalue value) {
        if (!curr) {
            curr = new Node();
        }
        if (key == curr->data.key) throw std::runtime_error("This key already exists");
        if (key < curr->data.key) {
            curr->left = insert(curr->left, key, value);
        } else {
            curr->right = insert(curr->right, key, value);
        }
        balance(curr);
        return curr;
    }

    void print(Node* curr) {
        if (!curr) throw "This tree doesn't exist";
        print(curr->left);
        std::cout << curr->data.key << " " << curr->data.value << std::endl;
        print(curr->right);
    }


public:
     AVLTree() {
        root = new Node();
     }

    Node* balance(Node* curr) {
        int h = curr->height;
        if (curr->left == nullptr && curr->right == nullptr) return nullptr;
            int hl = curr->left->height;
            int hr = curr->right->height;
        if (hr-hl == 2 || hr-hl == -2) {
            if (hr-hl == 2) {
                if(curr->left->left->height - curr->left->right->height == -1) {
                    curr->left = rotateLeft(curr->left);
                }
                curr = rotateRight(curr);
            }
            if (hr-hl == -2) {
                if(curr->left->left->height - curr->left->right->height == 1) {
                    curr->left = rotateRight(curr->right);
                }
                curr = rotateLeft(curr);
            }
        }
        return curr;
    }

    Node* rotateRight(Node* a) {
        Node * b = a->left;
        a->left = b->right;
        b->right = a;
        a->height = std::max(a->left->height, a->right->height);
        b->height = std::max(b->left->height, b->right->height);
        return b;
    }

    Node* rotateLeft(Node* a) {
        Node * b = a->right;
        a->right = b->left;
        b->left = a;
        a->height = std::max(a->left->height, a->right->height);
        b->height = std::max(b->left->height, b->right->height);
        return b;
    }

    void insert(Tkey key, Tvalue value) {
        insert(root, key, value);
    }

    void erase (Node* curr, Tkey key) {
        if (!curr) throw "This tree doesn't exist";
        if (key < curr->data.key) {
            curr->left = erase(curr->left, key);
        } else if (key > curr->data.key) {
            curr->right = erase(curr->right, key);
        } else {
            // Удаление листа
            if (curr->left == nullptr && curr->right == nullptr) {
                delete curr;
                return;
            }
            // Удаление узла, если нет левого поддерева
            if (curr->left == nullptr) {
                Node* tmp = curr->right;
                delete curr;
                return tmp;
            }
            // Удаление узла, если нет правого поддерева
            if (curr->right == nullptr) {
                Node* tmp = curr->left;
                delete curr;
                return tmp;
            }
            // Удаление узла с двумя поддеревьями
            Node* tmp = curr->right;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            curr->data.key = tmp->data.key;
            curr->data.value = tmp->data.value;
            curr->right = erase(curr->right, tmp->data.key);


        }
        balance(curr);
    }

    Tvalue find (Tkey key) {
        return find(key, root);
    }
    void print () {
        print(root);
    }

   bool operator== (AVLTree& other) {
       if (this->root->data.key != other.root->data.key) {
           return false;
       }
       if (this->root->data.value != other.root->data.value) {
           return false;
       }
       if (this->root->left != other.root->left) {
           return false;
       }
       if (this->root->right != other.root->right) {
           return false;
       }
       return true;

   }

   bool operator!= (AVLTree& other) {
       return !(this == other);
   }

};
#endif //POLINOM_AVL_TREE_H
