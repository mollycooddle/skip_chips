
#include <gtest.h>
#include "hash_table.h"
#include <vector>
#include <stdexcept>

TEST(HashTable, can_create_empty_hash_table) {
    HashTable <int, std::string, bool> t1;
    ASSERT_TRUE(t1.empty());
}

TEST(HashTable, can_create_hash_table_with_size) {
    HashTable <int, std::string, bool> t1(10);
    EXPECT_TRUE(t1.empty());
}

TEST(HashTable, can_insert_element) {
    HashTable <int, std::string, bool> t1;
    t1.insert(1, "1");
    ASSERT_EQ(t1.count(), 1);
}

TEST(HashTable, can_delete_element_from_table) {
    HashTable <int, std::string, bool> t1;
    t1.insert(1, "1");
    t1.erase(1);
    ASSERT_TRUE(t1.empty());
}

TEST(HashTable, cant_delete_element_from_empty_table) {
    HashTable <int, std::string, bool> t1;
    ASSERT_ANY_THROW(t1.erase(15));
}

TEST(HashTable, EraseKey) {
    HashTable<int, std::string, bool> table;
    table.insert(1, "value1");
    table.erase(1);
    EXPECT_THROW(table.find(1), std::runtime_error);
    EXPECT_EQ(table.count(), 0);
}

TEST(HashTable, CountAndSize) {
    HashTable<int, std::string, bool> table(5);
    EXPECT_EQ(table.size(), 5);

    table.insert(1, "value1");
    table.insert(2, "value2");
    table.insert(3, "value3");
    EXPECT_EQ(table.count(), 3);

    table.erase(2);
    EXPECT_EQ(table.count(), 2);
}

TEST(HashTable, can_insert_and_delete_element_2_) {
    HashTable <int, std::string, bool> t1;
    t1.insert(1, "1");
   // std::cout << t1.count() << std::endl;
    t1.insert(2, "4");
   // std::cout << t1.count() << std::endl;
    t1.erase(2);
   // std::cout << t1.count() << std::endl;
    ASSERT_EQ(t1.count(), 1);
}
TEST(HashTable, can_insert_and_delete_element_3) {
    HashTable <int, std::string, bool> t1;
    t1.insert(1, "1");
   // std::cout << t1.count() << std::endl;
    t1.insert(2, "4");
   // std::cout << t1.count() << std::endl;
    t1.insert(3, "4");
  //  std::cout << t1.count() << std::endl;
    t1.erase(3);
   // std::cout << t1.count() << std::endl;
    ASSERT_EQ(t1.count(), 2);
}
TEST(HashTable, can_insert_and_delete_element_2) {
    HashTable <int, std::string, bool> t1;
    t1.insert(1, "1");
    //std::cout << t1.count() << std::endl;
    t1.insert(2, "4");
   // std::cout << t1.count() << std::endl;
    t1.insert(3, "3");
   // std::cout << t1.count() << std::endl;
    t1.erase(2);
    //std::cout << t1.count() << std::endl;
    ASSERT_EQ(t1.count(), 2);
}
TEST(HashTable, can_insert_and_delete_element_1) {
    HashTable <int, std::string, bool> t1;
    t1.insert(1, "1");
    std::cout << t1.count() << std::endl;
    t1.insert(2, "4");
    std::cout << t1.count() << std::endl;
    t1.insert(3, "3");
    std::cout << t1.count() << std::endl;
    t1.erase(1);
    std::cout << t1.count() << std::endl;
    ASSERT_EQ(t1.count(), 2);
}


TEST(HashTable, can_find_element) {
    HashTable <int, std::string, bool> t1;
    t1.insert(1, "1");
    ASSERT_EQ(t1.find(1), "1");
}

//Проверка на вставку элементов с одинаковыми индексами после хэш-функции
TEST(HashTable, can_find_element_in_big_table) {
    HashTable <int, std::string, bool> t1;
    t1.insert(1, "1");
    std::cout<< "Хэш - функция для key = 1: " << t1.hash_function(1) << std::endl;

    t1.insert(4, "14");
    std::cout<< "Хэш - функция для key = 4: "<< t1.hash_function(4) << std::endl;

    t1.insert(2, "12");
    std::cout<< "Хэш - функция для key = 2: "<< t1.hash_function(2) << std::endl;

    t1.insert(3, "13");
    std::cout<< "Хэш - функция для key = 3: "<< t1.hash_function(3) << std::endl;

    t1.insert(7, "17");
    std::cout<< "Хэш - функция для key = 7: "<< t1.hash_function(7) << std::endl;

   //std::cout << t1.count() << std::endl;

    ASSERT_EQ(t1.find(1), "1");
    ASSERT_EQ(t1.find(3), "13");
    ASSERT_EQ(t1.find(2), "12");
    ASSERT_EQ(t1.find(4), "14");
    ASSERT_EQ(t1.find(7), "17");
}

TEST(HashTable, stress_test) {
    HashTable <int, std::string, bool> t1;
    for (int i = 0; i < 1000000; i++) {
        t1.insert(i, std::to_string(i));
    }
    for (int i = 0; i < 1000000; i++) {
        ASSERT_EQ(t1.find(i), std::to_string(i));
        t1.erase(i);
    }
    ASSERT_TRUE(t1.empty());
}

TEST(HashTable, collision_test) {
    HashTable <int, std::string, bool> t1;
    for (int i = 0; i < 10000; i++) {
        t1.insert(i, std::to_string(i));
    }
    std::cout<< t1.count() << std::endl;
    std::cout << t1.size() << std::endl;
}










