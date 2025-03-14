#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <regex>
#include <sstream>


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
        res.degree = m1.degree + m2.degree;
        return res;
    }

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

template <typename T>
class Polinom{
protected:
    std::list<std::string> polinom;
    std::vector<Monom> monoms;

public:
    Polinom() = default;

    explicit Polinom(const std::string& str) {
        validatePolynomial(str);
        parsePolinom(str);
        parseMonom();
    }
    struct Node {
        T data;
        Node *next;

        Node() {
            data = 0;
            next = nullptr;
        }

        Node(T d, Node *n) {
            data = d;
            next = n;
        }
    };


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

    friend bool operator<(const Polinom& m1, const Polinom& m2) {
        int flag = 0;
        for (int i = 0; i < m1.size(); i++) {
            if (m1.monoms[i] >= m2.monoms[i]) flag = 1;
        }
        
        if (flag == 1) return false;
        return true;
    }

    friend bool operator>(const Polinom<std::string>& m1, const Polinom<std::string>& m2) {
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

            if (str[i] == '+') {
                polinom.push_back(substr);
                substr = "";
                continue;
            } else if (str[i] == '-') {
                polinom.push_back(substr);
                substr = "-";
                continue;
            } else if (i == str.length() - 1) {
                substr += str[i];
                polinom.push_back(substr);
                substr = "";
                continue;
            }
            substr += str[i];
        }
    }

    void parseMonom() {
        std::string temp = "";

        for (const std::string &it : polinom) {
            temp += it;
            
            Monom res;
            int tmp = 0;
            for (int i = 0; i < it.length(); i++) {
                if (it[i] == '^') {
                    tmp++;
                    res.coeff = std::stod(it.substr(0, i - 1));
                    if (tmp == 1) {
                        res.degree += std::stoi(it.substr(i+1, i+2)) * 100;
                    } else if (tmp == 2) {
                        res.degree += std::stoi(it.substr(i+1, i+2)) * 10;
                    } else if (tmp == 3) {
                        res.degree += std::stoi(it.substr(i+1, i+2)) * 1;
                    }
                }
            }
            if (res.degree > 999) {
                throw std::runtime_error("Incorrect input. Please, try again");
            }

            monoms.push_back(res);
        }

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
    friend std::ostream& operator<< (std::ostream& os, Polinom& pol) {
        for (const std::string& term : pol.polinom) {
            os << term << "   ";
        }

        os << std::endl;
        return os;
    }
};