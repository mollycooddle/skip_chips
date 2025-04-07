//
// Created by Софья Фролова  on 26.03.2025.
//
#include <gtest.h>
#include "avl_tree.h"


TEST(AVLTreeTest, Initialization) {
    AVLTree<int, std::string> t1;
   ASSERT_NO_THROW(t1);
}

TEST(AVLTreeTest, Insertion) {
    AVLTree<int, std::string> t1;
    t1.insert(1, "");
    t1.insert(4, "1");
    ASSERT_EQ(t1.size(), 3);
}

// Тест на вставку и поиск
TEST(AVLTreeTest, InsertAndFind) {
    AVLTree<int, std::string> tree;
    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree.insert(5, "Five");

    EXPECT_EQ(tree.find(10), "Ten");
    EXPECT_EQ(tree.find(5), "Five");
    EXPECT_EQ(tree.find(20),"Twenty" );
}

// Тест на дублирование ключей
TEST(AVLTreeTest, InsertDuplicateKey) {
    AVLTree<int, std::string> tree;
    tree.insert(10, "Ten");
    EXPECT_THROW(tree.insert(10, "Duplicate"), std::runtime_error);
}

 //Тест на удаление
TEST(AVLTreeTest, Erase) {
    AVLTree<int, std::string> tree;
    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree.insert(5, "Five");


    ASSERT_ANY_THROW(tree.erase(0));
    EXPECT_EQ(tree.find(20), "Twenty");
    EXPECT_EQ(tree.find(10), "Ten");
}

// Тест на печать
TEST(AVLTreeTest, Print) {
    testing::internal::CaptureStdout(); // Захватываем вывод в stdout
    AVLTree<int, std::string> tree;
    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree.insert(5, "Five");
    tree.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("5 Five") != std::string::npos);
    EXPECT_TRUE(output.find("10 Ten") != std::string::npos);
    EXPECT_TRUE(output.find("20 Twenty") != std::string::npos);
}

// Тест на сравнение деревьев
TEST(AVLTreeTest, CompareTrees) {
    AVLTree<int, std::string> tree;
    AVLTree<int, std::string> tree2;
    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree2.insert(10, "Ten");
    tree2.insert(20, "Twenty");

    EXPECT_TRUE(tree == tree2);
}

// Тест на размер дерева
TEST(AVLTreeTest, Size) {
    AVLTree<int, std::string> tree;
    EXPECT_EQ(tree.size(), 1);
    tree.insert(10, "Ten");
    EXPECT_EQ(tree.size(), 2);
    tree.insert(20, "Twenty");
    EXPECT_EQ(tree.size(), 3);
    tree.erase(10);
    EXPECT_EQ(tree.size(), 2);
}

TEST(AVLTreeTest, super_test) {
    AVLTree<int, std::string> tree;

    for (int i = 1; i < 10000; i++) {
        tree.insert(i, "12");
    }
    std::cout <<tree.size();

    for (int i = 1; i < 10000; i++) {
        tree.erase(i);
    }
    EXPECT_EQ(tree.size(), 1);
}

TEST(AVLTreeTest, super_test_1) {
    AVLTree<int, std::string> tree;
    tree.insert(3, "val");
    tree.insert(9, "val");
    tree.insert(4, "val");
    tree.insert(1, "val");
    tree.insert(2, "val");
    tree.insert(5, "val");

    std::cout <<tree.size();

    //EXPECT_EQ(tree.size(), 1);
}

