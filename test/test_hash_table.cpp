#include <gtest.h>
#include "hash_table.h"
#include "polinom.h"

// Тесты для хеш-таблицы с ключами типа std::string

// Тест на вставку
TEST(HashTablePolinomTest, InsertNoThrow) {
    HashO<std::string, Polinom> table;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^4y^5z^6");

    ASSERT_NO_THROW(table.insert("poly1", p1));
}

TEST(HashTablePolinomTest, InsertAndFindSize) {
    HashO<std::string, Polinom> table;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^4y^5z^6");

    table.insert("poly1", p1);
    table.insert("poly2", p2);

    Polinom found_p1 = table.find("poly1");
    Polinom found_p2 = table.find("poly2");

    EXPECT_EQ(found_p1.monoms.size(), 1);
}

TEST(HashTablePolinomTest, InsertAndFindEQ) {
    HashO<std::string, Polinom> table;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^4y^5z^6");

    table.insert("poly1", p1);
    table.insert("poly2", p2);

    Polinom found_p1 = table.find("poly1");
    Polinom found_p2 = table.find("poly2");

    EXPECT_EQ(found_p1.monoms[0].coeff, 2);
}

TEST(HashTablePolinomTest, InsertAndFindUnknownKey) {
    HashO<std::string, Polinom> table;
    Polinom p1("2x^1y^2z^3");
    Polinom p2("3x^4y^5z^6");

    table.insert("poly1", p1);
    table.insert("poly2", p2);

    Polinom found_p1 = table.find("poly1");
    Polinom found_p2 = table.find("poly2");

    EXPECT_THROW(table.find("unknown_key"), std::runtime_error);
}

// Тест на удаление полинома
TEST(HashTablePolinomTest, EraseThrow) {
    HashO<std::string, Polinom> table;
    Polinom p("1x^1y^1z^1");
    table.insert("to_delete", p);

    table.erase("to_delete");
    EXPECT_THROW(table.find("to_delete"), std::runtime_error);
}

TEST(HashTablePolinomTest, EraseSize) {
    HashO<std::string, Polinom> table;
    Polinom p("1x^1y^1z^1");
    table.insert("to_delete", p);

    table.erase("to_delete");
    EXPECT_EQ(table.getSize(), 0);
}

// Тест на перезапись значения
TEST(HashTablePolinomTest, OverwriteValue) {
    HashO<std::string, Polinom> table;
    Polinom p1("1x^1y^1z^1");
    Polinom p2("2x^2y^2z^2");

    table.insert("key", p1);
    ASSERT_ANY_THROW(table.insert("key", p2)); // Перезаписываем значение
}

// Тест на обработку коллизий
TEST(HashTablePolinomTest, CollisionHandling1) {
    HashO<std::string, Polinom> table(2); // Маленький размер для гарантии коллизий
    Polinom p1("1x^1y^1z^1");
    Polinom p2("2x^2y^2z^2");

    table.insert("key1", p1);
    table.insert("key2", p2); // Коллизия гарантирована

    EXPECT_EQ(table.find("key1").monoms[0].coeff, 1);
}

TEST(HashTablePolinomTest, CollisionHandling2) {
    HashO<std::string, Polinom> table(2); // Маленький размер для гарантии коллизий
    Polinom p1("1x^1y^1z^1");
    Polinom p2("2x^2y^2z^2");

    table.insert("key1", p1);
    table.insert("key2", p2); // Коллизия гарантирована

    EXPECT_EQ(table.find("key2").monoms[0].coeff, 2);
}

// Тест на рехеширование при заполнении
TEST(HashTablePolinomTest, RehashCapacity) {
    HashO<std::string, Polinom> table(3); // Маленький начальный размер
    Polinom p("1x^1y^1z^1");

    table.insert("k1", p);
    table.insert("k2", p);
    table.insert("k3", p); // Вызовет rehash()

    EXPECT_GT(table.getCapacity(), 3);
}

TEST(HashTablePolinomTest, RehashEQ1) {
    HashO<std::string, Polinom> table(3); // Маленький начальный размер
    Polinom p("1x^1y^1z^1");

    table.insert("k1", p);
    table.insert("k2", p);
    table.insert("k3", p); // Вызовет rehash()

    EXPECT_EQ(table.find("k1").monoms[0].coeff, 1);
}

TEST(HashTablePolinomTest, RehashEQ2) {
    HashO<std::string, Polinom> table(3); // Маленький начальный размер
    Polinom p("1x^1y^1z^1");

    table.insert("k1", p);
    table.insert("k2", p);
    table.insert("k3", p); // Вызовет rehash()

    EXPECT_EQ(table.find("k2").monoms[0].coeff, 1);
}

TEST(HashTablePolinomTest, RehashEQ3) {
    HashO<std::string, Polinom> table(3); // Маленький начальный размер
    Polinom p("1x^1y^1z^1");

    table.insert("k1", p);
    table.insert("k2", p);
    table.insert("k3", p); // Вызовет rehash()

    EXPECT_EQ(table.find("k3").monoms[0].coeff, 1);
}