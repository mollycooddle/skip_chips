#pragma once

#include "polinom.h"

class DataBaseVector {
    
    std::vector<std::pair<int, Polinom>> sql;

public:
    DataBaseVector() = default;

    DataBaseVector(int id, Polinom pol) {
        sql.push_back(std::pair<int, Polinom>(id, pol));
    }

    void insert (int id, const Polinom& pol) {
        for (const auto& entry : sql) {
            if (entry.first == id) {
                throw std::runtime_error("Duplicate ID: " + std::to_string(id));
            }
        }
        sql.push_back(std::pair<int, Polinom>(id, pol));
    }

    void erase(int id) {
        for (const auto& entry : sql) {
            if (entry.first != id) {
                throw std::runtime_error("Not find ID: " + std::to_string(id));
            }
        }

        for (auto it = sql.begin(); it != sql.end(); ) {
            if (it->first == id) {
                it = sql.erase(it);
                return;
            }
            else {
                ++it;
            }
        }
        throw std::runtime_error("Element with id " + std::to_string(id) + " not found");
    }

    std::vector<std::pair<int, Polinom>>::iterator find(int id) {
        for (auto it = sql.begin(); it != sql.end(); ++it) {
            if (it->first == id) {
                return it;
            }
        }
        return sql.end();
    }

    size_t size() const{
        return sql.size();
    }

    friend bool operator==(DataBaseVector& t1, DataBaseVector& t2) {
        if (t1.size() != t2.size()) {
            return false;
        }
        for (int i = 0; i < t1.size(); i++) {
            if (t1.sql[i] != t2.sql[i]) return false;
        }
        return true;
    }

    friend bool operator!=(DataBaseVector t1, DataBaseVector t2) {
        return !(t1 == t2);
    }
};