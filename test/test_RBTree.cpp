#include "polinom.h"
#include <gtest.h>
#include "RBTree.h"

void CheckBlackHeight(RBTree<int, Polinom>::node* n, int bh, int current) {
    using TreeType = RBTree<int, Polinom>;
    using Color = typename TreeType::Color;

    if (n->fict) {
        EXPECT_EQ(current, bh);
        return;
    }
    if (n->color == Color::BLACK) {
        current++;
    }
    CheckBlackHeight(n->left, bh, current);
    CheckBlackHeight(n->right, bh, current);
}

//Пустое дерево
TEST(RBTreeTest, EmptyTreeEmpty) {
    RBTree<int, Polinom> tree;

    EXPECT_TRUE(tree.empty());
}

TEST(RBTreeTest, EmptyTreeSize) {
    RBTree<int, Polinom> tree;

    EXPECT_EQ(tree.size(), 0);
}

TEST(RBTreeTest, EmptyTreeFind) {
    RBTree<int, Polinom> tree;

    EXPECT_EQ(tree.find(1), tree.end());
}

//Вставка элементов
TEST(RBTreeTest, InsertionEmpty) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");

    tree.insert(1, p1);

    EXPECT_FALSE(tree.empty());

}

TEST(RBTreeTest, InsertionSize) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");

    tree.insert(1, p1);

    EXPECT_EQ(tree.size(), 1);
}

TEST(RBTreeTest, InsertionFind) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");

    tree.insert(1, p1);

    EXPECT_NE(tree.find(1), tree.end());
}

TEST(RBTreeTest, InsertionSize2) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");

    tree.insert(1, p1);
    tree.insert(2, p2);

    EXPECT_EQ(tree.size(), 2);
}

TEST(RBTreeTest, InsertionDuplicate) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");

    tree.insert(1, p1);
    tree.insert(2, p2);

    ASSERT_ANY_THROW(tree.insert(1, p3));
}

//Поиск элементов
TEST(RBTreeTest, FindNoThrow) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");

    tree.insert(1, p1);
    tree.insert(2, p2);
    tree.insert(3, p3);

    ASSERT_NO_THROW(tree.find(2));
}

TEST(RBTreeTest, FindKey) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(1, p1);
    tree.insert(2, p2);
    tree.insert(3, p3);
    auto it = tree.find(2);

    EXPECT_EQ((*it).key, 2);
}

TEST(RBTreeTest, FindValue) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(1, p1);
    tree.insert(2, p2);
    tree.insert(3, p3);
    auto it = tree.find(2);

    EXPECT_EQ(it->value.monoms[0].coeff, p2.monoms[0].coeff);
}

TEST(RBTreeTest, FindAnyThrow) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(1, p1);
    tree.insert(2, p2);
    tree.insert(3, p3);
    auto it = tree.find(4);

    EXPECT_EQ(it, tree.end());
}

//Удаление элементов
TEST(RBTreeTest, EraseSize) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(1, p1);
    tree.insert(2, p2);
    tree.insert(3, p3);
    tree.erase(2);

    EXPECT_EQ(tree.size(), 2);
}

TEST(RBTreeTest, EraseFindEnd) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(1, p1);
    tree.insert(2, p2);
    tree.insert(3, p3);
    tree.erase(2);

    EXPECT_EQ(tree.find(2), tree.end());
}

TEST(RBTreeTest, EraseAnyThrow) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(1, p1);
    tree.insert(2, p2);
    tree.insert(3, p3);
    tree.erase(2);

    ASSERT_ANY_THROW(tree.erase(5));
}

//Итерации по дереву
TEST(RBTreeTest, Iteration) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(3, p3);
    tree.insert(1, p1);
    tree.insert(4, p4);
    tree.insert(2, p2);

    //Проверка порядка обхода
    auto it = tree.begin();
    EXPECT_EQ((*it).key, 1);
    ++it;
    EXPECT_EQ((*it).key, 2);
    ++it;
    EXPECT_EQ((*it).key, 3);
    ++it;
    EXPECT_EQ((*it).key, 4);
    ++it;
    EXPECT_EQ(it, tree.end());
}

//Свойства красно-черного дерева
TEST(RBTreeTest, RBPropertiesRoot) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(3, p3);
    tree.insert(1, p1);
    tree.insert(4, p4);
    tree.insert(2, p2);

    using TreeType = RBTree<int, Polinom>;
    using Color = typename TreeType::Color;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        //1. Корень черный
        if (!it->parent) {
            EXPECT_EQ(it->color, Color::BLACK);
        }
    }
}

TEST(RBTreeTest, RBPropertiesBlackProgeny) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(3, p3);
    tree.insert(1, p1);
    tree.insert(4, p4);
    tree.insert(2, p2);

    using TreeType = RBTree<int, Polinom>;
    using Color = typename TreeType::Color;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        //2. Если узел красный, то оба его потомка черные
        if (it->color == Color::RED) {
            if (!it->left->fict) {
                EXPECT_EQ(it->left->color, Color::BLACK);
            }
            if (!it->right->fict) {
                EXPECT_EQ(it->right->color, Color::BLACK);
            }
        }
    }
}

TEST(RBTreeTest, RBPropertiesBlackHeight) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree.insert(3, p3);
    tree.insert(1, p1);
    tree.insert(4, p4);
    tree.insert(2, p2);

    using TreeType = RBTree<int, Polinom>;
    using Color = typename TreeType::Color;

    //Чёрная высота
    if (!tree.empty()) {
        int blackHeight = 0;
        auto node = tree.begin().ptr;
        while (node && !node->fict) {
            if (node->color == Color::BLACK) {
                blackHeight++;
            }
            node = node->left;
        }
        CheckBlackHeight(tree.begin().ptr, blackHeight, 0);
    }
}

//Копирование дерева
TEST(RBTreeTest, CopySize) {
    RBTree<int, Polinom> tree1;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree1.insert(1, p1);
    tree1.insert(2, p2);
    tree1.insert(3, p3);

    RBTree<int, Polinom> tree2(tree1);
    EXPECT_EQ(tree2.size(), 3);
}

TEST(RBTreeTest, CopyFind) {
    RBTree<int, Polinom> tree1;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree1.insert(1, p1);
    tree1.insert(2, p2);
    tree1.insert(3, p3);

    RBTree<int, Polinom> tree2(tree1);
    EXPECT_NE(tree2.find(1), tree2.end());
    EXPECT_NE(tree2.find(2), tree2.end());
    EXPECT_NE(tree2.find(3), tree2.end());
}

TEST(RBTreeTest, CopyAssignment) {
    RBTree<int, Polinom> tree1;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    Polinom p3("1x^3y^3z^1");
    Polinom p4("4x^1y^1z^1");
    tree1.insert(1, p1);
    tree1.insert(2, p2);
    tree1.insert(3, p3);

    RBTree<int, Polinom> tree3;
    tree3 = tree1;
    EXPECT_EQ(tree3.size(), 3);
}

//Работа с полиномами
TEST(RBTreeTest, PolynomialOperationsNE) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    tree.insert(1, p1);
    tree.insert(2, p2);

    auto it = tree.find(1);
    ASSERT_NE(it, tree.end());
}

TEST(RBTreeTest, PolynomialOperationsPlus) {
    RBTree<int, Polinom> tree;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^2y^1z^4");
    tree.insert(1, p1);
    tree.insert(2, p2);

    auto it = tree.find(1);
    Polinom result = it.ptr->value + p2;
    EXPECT_EQ(result.monoms.size(), 2);
}