//
// Created by Софья Фролова  on 09.03.2025.
//
#include "polinom.h"
#include <gtest.h>

TEST(polinom, can_create_polinom_WITH_UNARY_MINUS) {
    ASSERT_NO_THROW(Polinom  p1("-2x^6y^7z^8"));
}

TEST(polinom, can_create_polinom) {
    ASSERT_NO_THROW(Polinom  p1("2x^6y^7z^8"));
}
TEST(polinom, can_parse_polinom) {
    Polinom p1("2x^6y^7z^8+2x^6y^7z^8+2x^6y^7z^8");
    ASSERT_EQ(3, p1.size());
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
TEST (polinom, can_plus_polinom_with_different_monoms_and_sizes) {
    Polinom m1("4x^4y^3z^2+8x^5y^3z^2");
    Polinom m2("6x^9y^3z^2");
    Polinom m3;
    m3 = m1 + m2;
    Polinom exp ("4x^4y^3z^2+8x^5y^3z^2+6x^9y^3z^2");
    ASSERT_EQ(m3.monoms, exp.monoms);

}
TEST (polinom, can_plus_polinom_with_same_monoms) {
    Polinom m1("4x^4y^3z^2");
    Polinom m2("6x^4y^3z^2");
    Polinom m3;
    m3 = m1 + m2;
    Polinom exp ("10x^4y^3z^2");
    ASSERT_EQ(m3.monoms, exp.monoms);

}
TEST (polinom, can_plus_polinom_with_same_monoms_and_different_sizes) {
    Polinom m1("4x^4y^3z^2+2x^5y^7z^8");
    Polinom m2("6x^4y^3z^2");
    Polinom m3;
    m3 = m1 + m2;
    Polinom exp ("10x^4y^3z^2+2x^5y^7z^8");
    ASSERT_EQ(m3.monoms, exp.monoms);

}
TEST (polinom, can_sub_polinom_with_different_monoms_and_sizes) {
    Polinom m1("4x^4y^3z^2+8x^5y^3z^2");
    Polinom m2("6x^9y^3z^2");
    Polinom m3;
    m3 = m1 - m2;
    Polinom exp ("4x^4y^3z^2+8x^5y^3z^2-6x^9y^3z^2");
    ASSERT_EQ(m3.monoms, exp.monoms);

}
TEST (polinom, can_sub_polinom_with_same_monoms) {
    Polinom m1("4x^4y^3z^2");
    Polinom m2("6x^4y^3z^2");
    Polinom m3;
    m3 = m1 - m2;
    Polinom exp ("-2x^4y^3z^2");
    ASSERT_EQ(m3.monoms, exp.monoms);

}
TEST (polinom, can_sub_polinom_with_same_monoms_and_different_sizes) {
    Polinom m1("4x^4y^3z^2+2x^5y^7z^8");
    Polinom m2("6x^4y^3z^2");
    Polinom m3;
    m3 = m1 - m2;
    Polinom exp ("-2x^4y^3z^2+2x^5y^7z^8");
    ASSERT_EQ(m3.monoms, exp.monoms);

}
TEST (polinom, can_mul_polinom_with_same_monoms) {
    Polinom m1("4x^4y^3z^2");
    Polinom m2("6x^4y^3z^2");
    Polinom m3;
    m3 = m1 * m2;
    Polinom exp ("24x^8y^6z^4");
    ASSERT_EQ(m3.monoms, exp.monoms);
}

TEST (polinom, can_mul_polinom_) {
    Polinom m1("4x^4y^3z^2+4x^5y^3z^2");
    Polinom m2("6x^4y^3z^2");
    Polinom m3;
    m3 = m1 * m2;
    Polinom exp ("24x^8y^6z^4+24x^9y^6z^4");
    ASSERT_EQ(m3.monoms, exp.monoms);
}

TEST (polinom, can_mul_polinom_with_high_degrees) {
    Polinom m1("4x^4y^3z^2+4x^5y^3z^2");
    Polinom m2("6x^9y^3z^2");
    Polinom m3;
    m3 = m1 * m2;
    Polinom exp ("24x^3y^6z^4+24x^4y^6z^4");
    ASSERT_EQ(m3.monoms, exp.monoms);
}

