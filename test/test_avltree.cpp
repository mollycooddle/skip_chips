#include <gtest.h>
#include "avl_tree.h"


TEST(AVLTree, Initialization) {
    AVLTree<int, std::string> t1;
    ASSERT_NO_THROW(t1);
}

TEST(AVLTree, Insertion) {
    AVLTree<int, std::string> t1;
    t1.insert(1, "");
    t1.insert(4, "1");
    ASSERT_EQ(t1.size(), 2);
}

// Тест на вставку и поиск
TEST(AVLTree, InsertAndFind) {
    AVLTree<int, std::string> tree;
    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree.insert(5, "Five");

    EXPECT_EQ(tree.find(10), "Ten");
    EXPECT_EQ(tree.find(5), "Five");
    EXPECT_EQ(tree.find(20),"Twenty" );
}

// Тест на дублирование ключей
TEST(AVLTree, InsertDuplicateKey) {
    AVLTree<int, std::string> tree;
    tree.insert(10, "Ten");
    EXPECT_THROW(tree.insert(10, "Duplicate"), std::runtime_error);
}

//Тест на удаление
TEST(AVLTree, Erase) {
    AVLTree<int, std::string> tree;
    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree.insert(5, "Five");

    tree.erase(5);
    EXPECT_EQ(tree.size(), 2);
}

// Тест на сравнение деревьев
TEST(AVLTree, CompareTrees) {
    AVLTree<int, std::string> tree;
    AVLTree<int, std::string> tree2;
    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree2.insert(10, "Ten");
    tree2.insert(20, "Twenty");

    EXPECT_TRUE(tree == tree2);
}

// Тест на размер дерева
TEST(AVLTree, Size) {
    AVLTree<int, std::string> tree;
    EXPECT_EQ(tree.size(), 0);
    tree.insert(10, "Ten");
    EXPECT_EQ(tree.size(), 1);
    tree.insert(20, "Twenty");
    EXPECT_EQ(tree.size(), 2);
    tree.erase(20);
    EXPECT_EQ(tree.size(), 1);
}

#define MAX_NODES 1000000
TEST(AVLTree, super_test) {
    AVLTree<int, std::string> tree;

    for (int i = 0; i < MAX_NODES; i++) {
        tree.insert(i, "12");
    }

    for (int i = 0; i < MAX_NODES / 2; ++i) {
        tree.erase(i);
    }

    for (int i = 0; i < MAX_NODES / 2; ++i) {
        tree.insert(i, "12");
    }

    for (int i = MAX_NODES; i < MAX_NODES + MAX_NODES / 2; ++i) {
        tree.insert(i, "12");
    }

    std::cout << tree.height();

    EXPECT_EQ(tree.height(), 21);
}

TEST(AVLTree, super_test_1) {
    AVLTree<int, std::string> tree;
    tree.insert(3, "val");
    tree.insert(9, "val");
    tree.insert(4, "val");
    tree.insert(1, "val");
    tree.insert(2, "val");
    tree.insert(5, "val");

    EXPECT_EQ(tree.height(), 3);
}

