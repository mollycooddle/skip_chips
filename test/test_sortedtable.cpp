
#include "sorted_table.h"
#include "polinom.h"
#include <gtest.h>

/*TEST (SortedTable, can_create_sortedTable) {
    Polinom pol ("2x^6y^7z^8+2x^6y^7z^8+2x^6y^7z^8");
    ASSERT_NO_THROW(SortedTable s(1, pol));
}
TEST (SortedTable, can_create_null_sortedTable) {
    Polinom pol ("");
    ASSERT_NO_THROW(SortedTable s(0, pol));
}
TEST(SortedTableTest, DefaultConstructorIsEmpty) {
    SortedTable table;
    EXPECT_EQ(table.size(), 0);
}

/*TEST(SortedTableTest, InsertIncreasesSize) {
    SortedTable table;
    Polinom p;
    table.insert(1, p);
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTableTest, InsertDuplicateDoesNotChangeSize) {
    SortedTable table;
    Polinom p;
    table.insert(1, p);
    table.insert(1, p);
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTableTest, EraseExistingDecreasesSize) {
    SortedTable table;
    Polinom p;
    table.insert(1, p);
    table.erase(1);
    EXPECT_EQ(table.size(), 0);
}

/*TEST(SortedTableTest, EraseNonExistingNoChange) {
    SortedTable table;
    Polinom p;
    table.insert(1, p);
    table.erase(2);
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTableTest, FindExistingReturnsCorrectIterator) {
    SortedTable table;
    Polinom p;
    table.insert(5, p);
    auto it = table.find(5);
    EXPECT_EQ(it, table.find(5));
}

TEST(SortedTableTest, FindNonExistingReturnsEnd) {
    SortedTable table;
    Polinom p;
    table.insert(5, p);
    auto it = table.find(10);
    EXPECT_NE(it, table.find(5));
}

TEST(SortedTableTest, SortMaintainsOrder) {
    SortedTable table;
    Polinom p;
    table.insert(3, p);
    table.insert(1, p);
    table.insert(2, p);

    // Проверка порядка через find
    EXPECT_EQ(table.find(1)->first, 1);
    EXPECT_EQ(table.find(2)->first, 2);
    EXPECT_EQ(table.find(3)->first, 3);
}

TEST(SortedTableTest, OperatorEqualWhenEqual) {
    SortedTable t1, t2;
    Polinom p;
    t1.insert(1, p);
    t2.insert(1, p);
    EXPECT_TRUE(t1 == t2);
}

TEST(SortedTableTest, OperatorNotEqualWhenDifferent) {
    SortedTable t1, t2;
    Polinom p;
    t1.insert(1, p);
    t2.insert(2, p);
    EXPECT_TRUE(t1 != t2);
}

TEST(SortedTableTest, ConstructorWithParametersAddsElement) {
    Polinom p;
    SortedTable t(1, p);
    EXPECT_EQ(t.size(), 1);
}*/