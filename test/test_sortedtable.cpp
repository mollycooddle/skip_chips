
#include "sorted_table.h"
#include "polinom.h"
#include <gtest.h>

TEST (SortedTable, can_create_sortedTable) {
    Polinom pol ("2x^6y^7z^8+2x^6y^7z^8+2x^6y^7z^8");
    ASSERT_NO_THROW(SortedTable s(1, pol));
}
TEST (SortedTable, can_create_null_sortedTable) {
    Polinom pol ("");
    ASSERT_NO_THROW(SortedTable s(0, pol));
}
TEST(SortedTable, can_get_size_of_empty_table) {
    SortedTable table;
    EXPECT_EQ(table.size(), 0);
}
TEST (SortedTable, can_get_size_of_not_empty_table) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8+2x^9y^7z^8");
    table.insert(1, p);
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTable, can_insert_pair_in_empty_table) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8+2x^9y^7z^8");
    table.insert(1, p);
    ASSERT_EQ(table.size(), 1);
}
TEST(SortedTable, can_insert_pair_in_not_empty_table) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8+2x^9y^7z^8");
    table.insert(1, p);
    Polinom p1("2x^6y^7z^8+8x^5y^7z^8+2x^7y^7z^7");
    table.insert(67, p1);
    Polinom p3("2x^1y^7z^8+8x^5y^7z^8+2x^7y^7z^7");
    table.insert(78, p1);
    ASSERT_EQ(table.size(), 3);
}

TEST(SortedTableTest, insert_same_pair) {
    SortedTable table;
    Polinom p;
    table.insert(1, p);
    ASSERT_ANY_THROW(table.insert(1, p));
}

TEST(SortedTable, can_erase_pair_1) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8+2x^9y^7z^8");
    table.insert(1, p);

    Polinom p1("2x^6y^7z^8+8x^5y^7z^8+2x^7y^7z^7");
    table.insert(5, p1);

    table.erase(5);

    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTable, can_erase_pair_2) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8+2x^9y^7z^8");
    table.insert(1, p);

    Polinom p1("2x^6y^7z^8+8x^5y^7z^8+2x^7y^7z^7");
    table.insert(5, p1);

    table.erase(1);

    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTable, super_test) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8+2x^9y^7z^8");
    table.insert(1, p);
    table.erase(1);
    EXPECT_EQ(table.size(), 0);
}
TEST(SortedTable, super_test_2) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8+2x^9y^7z^8");
    table.insert(1, p);
    Polinom p2("2x^9y^7z^8+8x^5y^7z^8+78x^9y^7z^8");
    table.insert(4, p);
    table.erase(1);
    table.erase(4);
    EXPECT_EQ(table.size(), 0);
}
TEST(SortedTable, erase_in_empty_table) {
    SortedTable table;
    ASSERT_ANY_THROW(table.erase(1));
}

TEST(SortedTable, erase_not_existing_element) {
    SortedTable table;
    Polinom p;
    table.insert(1, p);
    ASSERT_ANY_THROW(table.erase(2));
}

TEST(SortedTable, find_existing_element) {
    SortedTable table;
    Polinom p;
    table.insert(5, p);
    auto it = table.find(5);
    EXPECT_EQ(it, table.find(5));
}

TEST(SortedTable, find_not_existing_element) {
    SortedTable table;
    Polinom p;
    table.insert(5, p);
    ASSERT_ANY_THROW(auto it = table.find(10));
}

TEST(SortedTable, sort) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8");
    Polinom p1("5x^9y^7z^8+8x^5y^7z^8+2x^7y^7z^7");
    Polinom p2("14x^9y^7z^8+11x^7y^7z^8");

    table.insert(3, p);
    table.insert(1, p1);
    table.insert(2, p2);


    EXPECT_EQ(table.find(1),p1);
    EXPECT_EQ(table.find(2), p2);
    EXPECT_EQ(table.find(3), p);
}
TEST(SortedTable, sort_1) {
    SortedTable table;
    Polinom p("2x^6y^7z^8+8x^5y^7z^8");
    Polinom p1("5x^9y^7z^8+8x^5y^7z^8+2x^7y^7z^7");
    Polinom p2("14x^9y^7z^8+11x^7y^7z^8");

    table.insert(3, p);
    table.insert(1, p1);
    table.insert(2, p2);
    table.erase(2);

    EXPECT_EQ(table.find(1),p1);
    EXPECT_ANY_THROW(table.find(2));
    EXPECT_EQ(table.find(3), p);
}


TEST(SortedTable, operatorEqualWhenEqual) {
    SortedTable t1, t2;
    Polinom p;
    t1.insert(1, p);
    t2.insert(1, p);
    EXPECT_TRUE(t1 == t2);
}

TEST(SortedTable, OperatorNotEqualWhenDifferent) {
    SortedTable t1, t2;
    Polinom p;
    t1.insert(1, p);
    t2.insert(2, p);
    EXPECT_TRUE(t1 != t2);
}

TEST(SortedTable, ConstructorWithParametersAddsElement) {
    Polinom p;
    SortedTable t(1, p);
    EXPECT_EQ(t.size(), 1);
}