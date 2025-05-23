﻿#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <regex>
#include <sstream>
#include <functional>


struct Monom {
    int degree = 0;
    double coeff = 0.0;

    friend std::ostream& operator<< (std::ostream& os, const Monom& m) {
        os << "coeff: " << m.coeff << " degree: " << m.degree << std::endl;
        return os;
    }

    friend Monom operator+ (const Monom& m1, const Monom& m2) {
        if (m1.degree != m2.degree) {
            throw std::runtime_error("Can't add monoms with different degrees");
        }
        Monom res;
        res.coeff = m1.coeff + m2.coeff;
        res.degree = m1.degree;
        return res;
    }
    friend Monom operator- (const Monom& m1, const Monom& m2) {
        if (m1.degree != m2.degree) {
            throw std::runtime_error("Can't subtract monoms with different degrees");
        }
        Monom res;
        res.coeff = m1.coeff - m2.coeff;
        res.degree = m1.degree;
        return res;
    }
    friend Monom operator* (const Monom& m1, const double value) {
        Monom res;
        if (value == 0) {
            res.coeff = 0.0;
            res.degree = 0;
            return res;
        }
        res.coeff = m1.coeff * value;
        res.degree = m1.degree;
        return res;
    }
    friend Monom operator* (const Monom& m1, const int value) {
        Monom res;
        if (value == 0) {
            res.coeff = 0;
            res.degree = 0;
            return res;
        }
        res.coeff = m1.coeff * value;
        res.degree = m1.degree;
        return res;
    }
    friend Monom operator*  (const Monom& m1, const Monom& m2) {
        Monom res;
        res.coeff = m1.coeff * m2.coeff;

        int deg1_x = m1.degree / 100;
        int deg1_y = (m1.degree / 10) % 10;
        int deg1_z = m1.degree % 10;

        int deg2_x = m2.degree / 100;
        int deg2_y = (m2.degree / 10) % 10;
        int deg2_z = m2.degree % 10;

        int new_x = deg1_x + deg2_x;
        int new_y = deg1_y + deg2_y;
        int new_z = deg1_z + deg2_z;

        // Проверяем, чтобы каждая степень была ≤ 9
        if (new_x > 9 || new_y > 9 || new_z > 9) {
            throw std::runtime_error("Degree of x, y or z > 9 after multiplication");
        }

        // Формируем итоговую степень
        res.degree = new_x * 100 + new_y * 10 + new_z;
        return res;
    }

    //ИСПРАВЛЕНО 1 9 1 и т д

    Monom() = default;

    explicit Monom(std::string str) {
        if (str[0] == '0') {
            this->coeff = 0.0;
            this->degree = 0;
            return;
        }

        int tmp = 0;

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '^') {
                tmp++;
                this->coeff = std::stod(str.substr(0, i - 1));
                if (tmp == 1) {
                    this->degree += std::stoi(str.substr(i+1, i+2)) * 100;
                } else if (tmp == 2) {
                    this->degree += std::stoi(str.substr(i+1, i+2)) * 10;
                } else if (tmp == 3) {
                    this->degree += std::stoi(str.substr(i+1, i+2)) * 1;
                }
            }
        }
        if (this->degree < 100) {
            throw std::runtime_error("Incorrect input. Please, try again");
        }
    }

    friend bool operator== (const Monom& m1, const Monom& m2) {
        return m1.coeff == m2.coeff && m1.degree == m2.degree;
    }

    friend bool operator> (const Monom& m1, const Monom& m2) {
        if (m1.degree == m2.degree) {
            if (m1.coeff > m2.coeff) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            if (m1.degree > m2.degree) {
                return true;
            }
            else {
                return false;
            }
        }
    }

    friend bool operator< (const Monom& m1, const Monom& m2) {
        if (m1.degree == m2.degree) {
            if (m1.coeff > m2.coeff) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            if (m1.degree > m2.degree) {
                return false;
            }
            else {
                return true;
            }
        }
    }

    friend bool operator<=(const Monom& m1, const Monom& m2) {
        return !(m1 > m2);
    }

    friend bool operator>=(const Monom& m1, const Monom& m2) {
        return !(m1 < m2);
    }
};

class Polinom{
protected:
    std::list<std::string> polinom;
public:
    std::vector<Monom> monoms;
    Polinom() = default;

    explicit Polinom(const std::string& str) {
        validatePolynomial(str);
        parsePolinom(str);
        parseMonom();
    }

    void print() {
        for (const Monom &i : monoms) {
            std::cout << i << std::endl;
        }
        std::cout << std::endl;
    }

    int size() const {
        return monoms.size();
    }

    friend bool operator==(const Polinom& m1, const Polinom& m2) {
        return m1.monoms == m2.monoms;
    }

    friend bool operator!=(const Polinom& m1, const Polinom& m2) {
        return m1.monoms != m2.monoms;
    }

    friend bool operator<(const Polinom& m1, const Polinom& m2) {
        int flag = 0;
        for (int i = 0; i < m1.size(); i++) {
            if (m1.monoms[i] >= m2.monoms[i]) flag = 1;
        }
        
        if (flag == 1) return false;
        return true;
    }

    friend bool operator>(const Polinom& m1, const Polinom& m2) {
        int flag = 0;
        for (int i = 0; i < m1.size(); i++) {
            if (m1.monoms[i] <= m2.monoms[i]) flag = 1;
        }

        if (flag == 1) return false;
        return true;
    }

private:
    void parsePolinom(const std::string& str) {
        std::string substr;
        for (int i = 0; i < str.length(); i++) {
            if ((str[i] == ' ' || (i != 0 && (str[i] == '+' || str[i] == '-')))) {
                if (!substr.empty()) {
                    polinom.push_back(substr);
                    substr = "";
                }
                if (str[i] == '-') {
                    substr = "-";
                }
                continue;
            }
            substr += str[i];
        }
        if (!substr.empty()) {
            polinom.push_back(substr);
        }
    }

    void parseMonom() {
        for (const std::string& it : polinom) {
            Monom res(it);
            monoms.push_back(res);
        }
        std::sort(monoms.begin(), monoms.end(), std::greater<Monom>());
    }

    void validateMonom(const std::string& monomStr) {
        std::regex monomPattern(R"((-?\d+)x\^([0-9])y\^([0-9])z\^([0-9]))");

        if (!std::regex_match(monomStr, monomPattern)) {
            throw std::runtime_error("Invalid monom format: " + monomStr);
        }
    }

    void validatePolynomial(const std::string& polynomialStr) {
        std::stringstream ss(polynomialStr);
        std::string monomStr;

        while (ss >> monomStr) {
            try {
                validateMonom(monomStr);
            }
            catch (const std::runtime_error& e) {
                throw std::runtime_error("Invalid polynomial: " + std::string(e.what()));
            }
        }
    }

public:

    Polinom operator+(const Polinom& other) const {
        Polinom result;
        result.monoms.reserve(this->monoms.size() + other.monoms.size());

        auto it1 = this->monoms.begin();
        auto it2 = other.monoms.begin();

        while (it1 != this->monoms.end() && it2 != other.monoms.end()) {
            if (it1->degree < it2->degree) {
                result.monoms.push_back(*it1);
                ++it1;
            }
            else if (it2->degree < it1->degree) {
                result.monoms.push_back(*it2);
                ++it2;
            }
            else {
                Monom sum = *it1 + *it2;
                if (sum.coeff != 0.0) {
                    result.monoms.push_back(sum);
                }
                ++it1;
                ++it2;
            }
        }

        while (it1 != this->monoms.end()) {
            result.monoms.push_back(*it1);
            ++it1;
        }

        while (it2 != other.monoms.end()) {
            result.monoms.push_back(*it2);
            ++it2;
        }

        return result;
    }

    //O(n) O(n+m)

    Polinom operator- (const Polinom& other) {
        Polinom result;
        int i = 0, j = 0;

        while (i < this->size() && j < other.size()) {
            Monom a = this->monoms[i];
            Monom b = other.monoms[j];

            if (a.degree == b.degree) {
                Monom sub = a - b;
                if (sub.coeff != 0) {
                    result.monoms.push_back(sub);
                }
                i++;
                j++;
            }
            else if (a.degree < b.degree) {
                result.monoms.push_back(a);
                i++;
            }
            else {
                b.coeff = -b.coeff;
                result.monoms.push_back(b);
                j++;
            }
        }

        while (i < this->size()) {
            result.monoms.push_back(this->monoms[i]);
            i++;
        }

        while (j < other.size()) {
            Monom b = other.monoms[j];
            b.coeff = -b.coeff;
            result.monoms.push_back(b);
            j++;
        }

        return result;
    }


    Polinom operator*(const Polinom& other) {
        Polinom result;
        for (const auto& m1 : monoms) {
            for (const auto& m2 : other.monoms) {
                try {
                    Monom product = m1 * m2;
                    // Объединяем мономы с одинаковыми степенями
                    bool found = false;
                    for (auto& m : result.monoms) {
                        if (m.degree == product.degree) {
                            m.coeff += product.coeff;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        result.monoms.push_back(product);
                    }
                }
                catch (const std::runtime_error& e) {
                    // Игнорируем мономы с превышением степени
                }
            }
        }
        // Удаляем нулевые коэффициенты и сортируем
        result.monoms.erase(
            remove_if(result.monoms.begin(), result.monoms.end(),
                [](const Monom& m) { return m.coeff == 0; }),
            result.monoms.end()
        );
        sort(result.monoms.begin(), result.monoms.end(), std::greater<Monom>());
        return result;
    }

    /*friend Polinom operator*(const Polinom& p1, const Polinom& p2) {
        Polinom result;
       
        for (const auto& m1 : p1.monoms) {
            Polinom temp;
            for (const auto& m2 : p2.monoms) {
                Monom product = m1 * m2;
                if (product.coeff != 0) {
                    temp.monoms.push_back(product);
                }
            }
            result = result + temp;
        }

        return result;
    }*/

    friend std::ostream& operator<< (std::ostream& os, Polinom& pol) {
        for (int i = 0; i < pol.size(); i++) {
            std::cout << pol.monoms[i] << std::endl;
        }
        return os;
    }

    std::string toString() const {
        std::stringstream ss;
        for (const auto& monom : monoms) {
            ss << monom.coeff << "x^" << (monom.degree / 100)
                << "y^" << ((monom.degree / 10) % 10)
                << "z^" << (monom.degree % 10) << " ";
        }
        std::string result = ss.str();
        if (!result.empty()) {
            result.pop_back(); // Удаляем последний пробел
        }
        return result;
    }
};