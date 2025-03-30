//
// Created by Софья Фролова  on 26.03.2025.
//
#include <gtest.h>
#include "avl_tree.h"
using namespace std;

TEST(AVLTreeTest, Initialization) {
    AVLTree<int, std::string> t1;
    ASSERT_NO_THROW(t1);
}

/*TEST(AVLTreeTest, Insertion) {
    AVLTree<int, std::string> t1;
    AVLTree<int, std::string> t2;

    t1.insert(1, "1");
    t2.insert(1, "1");

    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;

    ASSERT_EQ(t1, t2);
}*/

