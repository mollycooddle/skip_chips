#include <gtest.h>
#include "avl_tree.h"
#include <vector>
#include <stdexcept>


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

    //std::cout << tree.height();

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

//Test for iterators

TEST(Iterator, tree_is_empty) {
    AVLTree<int, std::string> tree;
    // Проверка begin() == end() для пустого дерева
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST(Iterator, only_one_element) {
    AVLTree<int, std::string> tree;
    tree.insert(42, "Answer");

    auto it = tree.begin();
    // Проверка разыменования
    EXPECT_EQ(it->key, 42);
    EXPECT_EQ((*it).value, "Answer");

    // Проверка инкремента
    ++it;
    EXPECT_EQ(it, tree.end());
}

TEST(Iterator, right_inOrder_traversal_random) {

    AVLTree<int, std::string> tree;
    std:: vector<std::pair<int, std::string> > data;
    data.push_back(std::make_pair(3, "C"));
    data.push_back(std::make_pair(1, "A"));
    data.push_back(std::make_pair(4, "D"));
    data.push_back(std::make_pair(2, "B"));
    data.push_back(std::make_pair(5, "E"));

    //Цикл for с диапазоном (range-based for loop) для вставки
    for (const auto& [k, v] : data) tree.insert(k, v);

    // Ожидаемый порядок ключей: 1, 2, 3, 4, 5
    std::vector<int> expected_keys;
    expected_keys.push_back(1);
    expected_keys.push_back(2);
    expected_keys.push_back(3);
    expected_keys.push_back(4);
    expected_keys.push_back(5);

    auto it = tree.begin();

    for (size_t i = 0; i < expected_keys.size(); ++i) {
        ASSERT_NE(it, tree.end());
        EXPECT_EQ(it->key, expected_keys[i]);
        ++it;
    }
    EXPECT_EQ(it, tree.end());
}

TEST(Iterator, check_empty_end) {
    AVLTree<int, std::string> tree;
    auto it = tree.end();

    // Проверка исключения при разыменовании end()
    EXPECT_THROW(*it, std::out_of_range);
    EXPECT_THROW(it.operator->(), std::out_of_range);
}

TEST(Iterator, right_inOrder_traversal_reverse) {
    AVLTree<int, std::string> tree;
    // Вставка в обратном порядке
    for (int i = 5; i >= 1; --i) {
        tree.insert(i, std::to_string(i));
    }

    std::vector<int> expected;

    for (int i = 1; i <= 5; ++i) {
        expected.push_back(i);
    }

    auto it = tree.begin();

    for (const auto& k : expected) {
        ASSERT_NE(it, tree.end());
        EXPECT_EQ(it->key, k);
        ++it;
    }
}