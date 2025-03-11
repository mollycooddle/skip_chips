#pragma once

#include "polinom.h"
#include <sstream>
#include <algorithm>

class DataBaseVector : public Polinom<std::string> {

    std::vector<Polinom<std::string>> sql;

public:
    DataBaseVector(const std::string& str = "") {
        sql.push_back(Polinom(str));
    }
protected:
    void sortPolynomialsByString() {
        auto compareByString = [](Polinom<std::string> p1, Polinom<std::string> p2) {
            std::ostringstream oss1, oss2;
            oss1 << p1;
            oss2 << p2;
            return oss1.str() < oss2.str();
            };

        std::sort(sql.begin(), sql.end(), compareByString);
    }
public:
    Polinom& operator[](size_t ind)
    {
        if ((ind >= size()) || (ind < 0))
            throw "Index out of range";

        return sql[ind];
    }
    const Polinom& operator[](size_t ind) const
    {
        if ((ind >= size()) || (ind < 0))
            throw "Index out of range";

        return sql[ind];
    }

    void insert(const Polinom<std::string>& pol) {
        sql.push_back(pol);
        sortPolynomialsByString();
    }

    void erase(int i) {
        if (i >= 0 && i < sql.size()) {
            sql.erase(sql.begin() + i);
        }
        else {
            throw std::runtime_error("Index out of range");
        }
    }

    int find(Polinom<std::string> pol) {
        int left = 0;
        int right = sql.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            std::ostringstream ossMid, ossTarget;
            ossMid << sql[mid];
            ossTarget << pol;

            if (ossMid.str() == ossTarget.str()) {
                return mid;
            }

            if (ossMid.str() < ossTarget.str()) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return -1;
    }

    size_t size() const {
        return sql.size();
    }

    friend std::ostream& operator<< (std::ostream& os, DataBaseVector& sql) {
        for (int i = 1; i < sql.size(); i++) {
            os << i - 1 << "   ";
            os << sql[i];
        }
        return os;
    }
};