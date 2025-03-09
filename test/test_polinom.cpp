//
// Created by Софья Фролова  on 09.03.2025.
//
#include "polinom.h"
#include <gtest.h>

TEST(polinom, can_create_polinom) {
    ASSERT_NO_THROW(Polinom <std::string> p1("2x^6y^7z^8"););
}
TEST(polinom, can_parse_polinom) {
    Polinom<std::string> p1("2x^6y^7z^8+2x^6y^7z^8+2x^6y^7z^8");
    ASSERT_EQ(3, p1.length());
}

TEST(polinom, can_add_monom) {
    Monom m1("2x^6y^7z^8");
    Monom m2("2x^6y^7z^8");
    Monom m3 ("4x^6y^7z^8");
    ASSERT_EQ(m1 + m2, m3);
}
TEST(polinom, cant_add_monom_with_different_degree) {
    Monom m1("2x^4y^7z^8");
    Monom m2("2x^6y^7z^8");
    ASSERT_ANY_THROW(m1 + m2);
}
TEST(polinom, can_sub_monom) {
    Monom m1("6x^6y^7z^8");
    Monom m2("2x^6y^7z^8");
    Monom m3 ("4x^6y^7z^8");
    ASSERT_EQ(m1 - m2, m3);
}
TEST(polinom, cant_sub_monom_with_different_degree) {
    Monom m1("2x^4y^7z^8");
    Monom m2("5x^6y^7z^8");
    ASSERT_ANY_THROW(m1 - m2);
}
TEST(polinom, can_mul_monom_with_const) {
    Monom m1("2x^4y^7z^8");
    int a = 3;
    Monom m3 ("6x^4y^7z^8");
    ASSERT_EQ(m1 * a, m3);
}
TEST(polinom, can_mul_monom_with_null) {
    Monom m1("2x^4y^7z^8");
    int a = 0;
    Monom m3 ("0");
    ASSERT_EQ(m1 * a, m3);
}
TEST(polinom, can_mul_monom) {
    Monom m1("2x^4y^7z^5");
    Monom m2("3x^4y^2z^2");
    Monom m3 ("6x^8y^9z^7");
    ASSERT_EQ(m1 * m2, m3);
}