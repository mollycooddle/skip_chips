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
            height = 0;
            data.key = 0;
            data.value = "";
        }

        Node(Tkey nkey, Tvalue nvalue) {
            left = nullptr;
            right = nullptr;
            height = 1;
            data.key = nkey;
            data.value = nvalue;
        }

        bool operator== (Node*b){
            // Оба узла nullptr
            if (!this && !b) return true;

            // Один из узлов nullptr
            if (!this || !b) return false;

            // Сравниваем данные текущего узла
            if (this->data.key != b->data.key || this->data.value != b->data.value) {
                return false;
            }

            // Рекурсивно сравниваем левые и правые поддеревья
            return (this->left == b->left) && (this->right == b->right);
        }
    };

    Node* root;

//    Node* balance(Node* curr) {
//
//        if (curr->left == nullptr || curr->right == nullptr) return nullptr;
//
//        int hl = curr->left->height;
//        int hr = curr->right->height;
//
//        if (hr-hl == 2 || hr-hl == -2) {
//            if (hr-hl == 2) {
//                if(curr->left->left->height - curr->left->right->height == -1) {
//                    curr->left = rotateLeft(curr->left);
//                    balance (curr->left);
//                }
//
//                if(curr->left->left->height - curr->left->right->height == 1) {
//                    curr->right = rotateRight(curr);
//                    balance (curr->right);
//                }
//            }
//
//            if (hr-hl == -2) {
//                if(curr->left->left->height - curr->left->right->height == 1) {
//                    curr->left = rotateRight(curr->right);
//                    balance (curr->left);
//
//                }
//
//                if(curr->left->left->height - curr->left->right->height == 1) {
//                    curr->right = rotateLeft(curr);
//                    balance (curr->right);
//                }
//            }
//        }
//        return curr;
//    }
//
//    Node* rotateRight(Node* a) {
//        Node * b = a->left;
//        a->left = b->right;
//        b->right = a;
//        a->height = std::max(a->left->height, a->right->height);
//        b->height = std::max(b->left->height, b->right->height);
//        return b;
//    }
//
//    Node* rotateLeft(Node* a) {
//        Node * b = a->right;
//        a->right = b->left;
//        b->left = a;
//        updateHeight(a);
//        updateHeight(b);
//        return b;
//    }

    int height(Node* node) {
        return node ? node->height : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);

        // Left Heavy
        if (bf > 1) {
            if (balanceFactor(node->left) >= 0)
                return rightRotate(node);
            else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        // Right Heavy
        if (bf < -1) {
            if (balanceFactor(node->right) <= 0)
                return leftRotate(node);
            else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    int balanceFactor(Node* node) {
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

     Tvalue find (Tkey key, Node* curr) {
        if (!curr) throw "This tree doesn't exist";
        if (key == curr->data.key) {return curr->data.value;}
        if (key < curr->data.key) {return find(key, curr->left);}
        if (key > curr->data.key) {return find(key, curr->right);}
    }

    // Работает за O(log n)
    Node* insert(Node* curr, Tkey key, Tvalue value) {
        if (!curr) {
            curr = new Node(key, value);
        }
        else {
            if (key == curr->data.key) throw std::runtime_error("This key already exists");
            if (key < curr->data.key) {
                curr->left = insert(curr->left, key, value);
                balance(curr);
                updateHeight(curr);
            } else {
                curr->right = insert(curr->right, key, value);
                balance(curr);
                updateHeight(curr);
            }
        }
        balance(curr);
        updateHeight(curr);
        return curr;
    }

    //Работает за O(log n)
    Node* erase (Node* curr, Tkey key) {
        //if (!curr) throw std::runtime_error("This tree doesn't exist");
        if (key == root->data.key) throw std::runtime_error("Can't delete root");
        if (key < curr->data.key) {

            curr->left = erase(curr->left, key);
        } else if (key > curr->data.key) {
            curr->right = erase(curr->right, key);
        } else {
            // Удаление листа
            if (curr->left == nullptr && curr->right == nullptr) {
                delete curr;
                return nullptr;
            }
            // Удаление узла, если нет левого поддерева
            if (curr->left == nullptr) {
                Node* tmp = curr->right;
                delete curr;
                return balance(tmp);
            }
            // Удаление узла, если нет правого поддерева
            if (curr->right == nullptr) {
                Node* tmp = curr->left;
                delete curr;
                return balance(tmp);
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
        updateHeight(curr);
        return balance(curr);
    }

    void print(Node* curr) {
        if (!curr) return;
        print(curr->left);
        std::cout << curr->data.key << " " << curr->data.value << std::endl;
        print(curr->right);
    }

    bool compareNodes(const Node* a, const Node* b) const {
        // Оба узла nullptr
        if (!a && !b) return true;

        // Один из узлов nullptr
        if (!a || !b) return false;

        // Сравниваем данные текущего узла
        if (a->data.key != b->data.key || a->data.value != b->data.value) {
            return false;
        }

        // Рекурсивно сравниваем левые и правые поддеревья
        return compareNodes(a->left, b->left) && compareNodes(a->right, b->right);
    }

    int size(Node* node) {
        if (node == nullptr) return 0;  // База рекурсии: высота NIL-узла = 0
        int leftHeight = size(node->left);
        int rightHeight = size(node->right);
        return 1 + std::max(leftHeight, rightHeight);  // Выбираем максимальную высоту
    }


public:

     AVLTree() {
        root = new Node();
     }

    void insert(Tkey key, Tvalue value) {
        insert(root, key, value);
    }

    void erase(Tkey key) {
         erase(root, key);
     }

    Tvalue find (Tkey key) {
        return find(key, root);
    }
    void print () {
        print(root);
    }


   bool operator!= (AVLTree& other) {
       return !(this == other);
   }

    friend std::ostream& operator<< (std::ostream& os, const TTableRec& t) {
        os << "key: " << t.key << " value: " << t.value << std::endl;
        return os;
        }

    int size() {
         return size(root);
     }

    bool operator==(const AVLTree<Tkey, Tvalue>& other) const {
        return compareNodes(root, other.root);
    }

    bool operator!=(const AVLTree<Tkey, Tvalue>& other) const {
        return !(*this == other);
    }

//    void updateHeight(Node* node) {
//         if (node) {
//             if (!node->left && !node->right) {
//                 node->height = 1;
//             }
//             else if (node->left && !node->right) {
//                 node->height = 1 + node->left->height;
//             }
//             else if (!node->left && node->right) {
//                 node->height = 1 + node->right->height;
//             }
//             else node->height = 1 + std::max(node->left->height, node->right->height);
//        }
//    }



};
#endif //POLINOM_AVL_TREE_H
