#pragma once

#include "polinom.h"

class DataBaseVector : public Polinom<std::string> {
    
    std::vector<Polinom<std::string>> sql;

public:
    DataBaseVector(const std::string& str = "") {
        sql.push_back(Polinom(str));
    }

    Polinom& operator[](size_t ind)
    {
        if ((ind >= size()) || (ind < 0))
            throw std::runtime_error("Index out of range");

        return sql[ind];
    }
    const Polinom& operator[](size_t ind) const
    {
        if ((ind >= size()) || (ind < 0))
            throw std::runtime_error("Index out of range");

        return sql[ind];
    }

    void insert (int i, const Polinom<std::string>& pol) {
        sql.insert(sql.begin() + i, pol);
    }

    void erase (int i) {
        if (i >= 0 && i < sql.size()) {
            sql.erase(sql.begin() + i);
        }
        else {
            throw std::runtime_error("Index out of range");
        }
    }

    int find(Polinom<std::string> pol) {
        for (int i = 0; i < sql.size(); i++) {
            if (sql[i] == pol) {
                return i;
            }
        }
        return -1;
    }

    size_t size() const{
        return sql.size();
    }

    friend std::ostream& operator<< (std::ostream& os, DataBaseVector& sql) {
        for (int i = 0; i < sql.size() - 1; i++) {
            os << i << "   ";
            os << sql[i];
        }
        return os;
    }
};