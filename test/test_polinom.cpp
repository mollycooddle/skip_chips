
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
TEST(polinom, can_mul_monom_special) {
    Monom m1("2x^4y^7z^5");
    Monom m2("3x^9y^2z^2");
    //Monom m3 ("6x^8y^9z^7");
    ASSERT_ANY_THROW(m1*m2);
}
TEST(polinom, can_mul_monom_special_1) {
    Monom m1("2x^1y^8z^0");
    Monom m2("3x^1y^8z^0");
    //Monom m3 ("6x^8y^9z^7");
    ASSERT_ANY_THROW(m1*m2);
}
TEST (polinom, can_plus_polinom_with_different_monoms_and_sizes) {
    Polinom m1("4x^4y^3z^2+8x^5y^3z^2");
    Polinom m2("6x^9y^3z^2");
    Polinom m3;
    m3 = m1 + m2;
    Polinom exp ("6x^9y^3z^2+8x^5y^3z^2+4x^4y^3z^2");
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
    Polinom exp ("-6x^9y^3z^2+8x^5y^3z^2+4x^4y^3z^2");
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
    Polinom exp ("2x^5y^7z^8-2x^4y^3z^2");
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
    Polinom exp("24x^9y^6z^4+24x^8y^6z^4");
    ASSERT_EQ(m3.monoms, exp.monoms);
}

TEST (polinom, can_mul_polinom_with_high_degrees) {
    Polinom m1("4x^4y^3z^2+4x^5y^3z^2");
    Polinom m2("6x^9y^3z^2");
    ASSERT_ANY_THROW(m1*m2);
}

TEST(polinom, mult_two_pols_example) {
    std::string str1 = "x^3y^0z^0+x^1y^0z^0+x^0y^0z^0";
    std::string str2 = "x^2y^0z^0+x^0y^0z^0";
    std::string chekStr = "x^5y^0z^0+2x^3y^0z^0+x^2y^0z^0+x^1y^0z^0+x^0y^0z^0";

    Polinom p1(str1);
    Polinom p2(str2);
    Polinom chek(chekStr);
    ASSERT_EQ(p1*p2, chek);

}

TEST(polinom, zero_polinom_plus) {
    Polinom p1("0");
    Polinom p2("0");
    Polinom result = p1 + p2;
    ASSERT_EQ(result.monoms.size(), 0);
}

TEST(polinom, auto_remove_zero_monoms_after_operations) {
    Polinom p1("3x^2y^3z^4");
    Polinom p2("-3x^2y^3z^4");
    Polinom result = p1 + p2;
    ASSERT_TRUE(result.monoms.empty());
}

TEST(polinom, correct_monom_ordering) {
    Polinom p("x^3y^2z^1+x^1y^5z^9+x^9y^0z^2");

    std::vector<int> expected_degrees;
    expected_degrees.push_back(902); // x^9y^0z^2
    expected_degrees.push_back(321); // x^3y^2z^1
    expected_degrees.push_back(159); // x^1y^5z^9

    std::vector<int> actual_degrees;
    for(const auto& m : p.monoms) {
        actual_degrees.push_back(m.degree);
    }

    ASSERT_EQ(expected_degrees.size(), actual_degrees.size());
    ASSERT_EQ(expected_degrees, actual_degrees);

}


TEST(polinom, floating_point_coeff) {
    Polinom p1("2.5x^3y^2z^1");
    Polinom p2("1.5x^3y^2z^1");
    Polinom result = p1 + p2;
    Monom expected("4.0x^3y^2z^1");
    ASSERT_EQ(result.monoms[0].coeff, expected.coeff);
}


TEST(polinom, polinom_copy_operations) {
    Polinom p1("3x^2y^3z^4+2x^5y^1z^2");
    Polinom p2(p1);
    Polinom p3 = p1;
    ASSERT_EQ(p1.monoms, p2.monoms);
    ASSERT_EQ(p1.monoms, p3.monoms);
}


TEST(polinom, multiply_by_zero_polinom) {
    Polinom p1("3x^2y^3z^4+2x^5y^1z^2");
    Polinom zero("0");
    Polinom result = p1 * zero;
    ASSERT_TRUE(result.monoms.empty());
}


TEST(polinom, can_parse_different_spaces) {
    Polinom p1(" 3x^2y^3z^4 + 2x^5y^1z^2 ");
    Polinom p2("3x^2y^3z^4+2x^5y^1z^2");
    ASSERT_EQ(p1.monoms, p2.monoms);
}


TEST(polinom, not_equal_polinoms) {
    Polinom p1("3x^2y^3z^4");
    Polinom p2("3x^2y^3z^5");
    ASSERT_TRUE(p1 != p2);
}


TEST(polinom, add_empty_polinom) {
    Polinom p1("3x^2y^3z^4");
    Polinom p2("");
    Polinom result = p1 + p2;
    ASSERT_EQ(result.monoms, p1.monoms);
}

TEST(polinom, super_test_1) {
    std::string str1 = "x^3y^0z^0+x^1y^0z^0+x^0y^0z^0";
    std::string str2 = "x^2y^0z^0+x^0y^0z^0";
    std::string chekStr = "x^5y^0z^0+2x^3y^0z^0+x^2y^0z^0+x^1y^0z^0+x^0y^0z^0";
    Polinom p1(str1);
    Polinom p2(str2);
    Polinom chek(chekStr);
    EXPECT_EQ(p1*p2, chek);

}

TEST(polinom, super_test_2) {
    std::string str1 = "x^3y^0z^0+x^1y^0z^0+x^0y^0z^0";
    std::string str2 = "x^2y^0z^0+x^0y^0z^0";
    std::string chekStr = "x^5y^0z^0+2x^3y^0z^0+x^2y^0z^0+x^1y^0z^0+x^0y^0z^0";
    Polinom p1(str1);
    Polinom p2(str2);
    Polinom chek(chekStr);
    EXPECT_EQ(p1*p2, chek);

}