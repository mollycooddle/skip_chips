#pragma once

#include "polinom.h"

class DataBaseVector {

public:
    std::vector<std::pair<std::string, Polinom>> sql;
    DataBaseVector() = default;

    DataBaseVector(std::string id, Polinom pol) {
        sql.push_back(std::pair<std::string, Polinom>(id, pol));
    }

    void insert (std::string id, const Polinom& pol) {
        for (const auto& entry : sql) {
            if (entry.first == id) {
                throw std::runtime_error("Duplicate ID: " + id);
            }
        }
        sql.push_back(std::pair<std::string, Polinom>(id, pol));
    }
    
    void insert_no_check(std::string id, const Polinom& pol) {
        sql.emplace_back(id, pol);
    }

    // ИСПРАВЛЕНО с проверкой; без проверки

    void erase(std::string id) {
        auto it = std::find_if(sql.begin(), sql.end(), [&id](const auto& entry) { return entry.first == id; });

        if (it == sql.end()) {
            throw std::runtime_error("Element with id " + id + " not found");
        }

        std::iter_swap(it, std::prev(sql.end()));
        sql.pop_back();
    }

    // ИСПРАВЛЕНО переставить удаляемый с последним

    std::vector<std::pair<std::string, Polinom>>::iterator find(std::string id) {
        int f = 0;
        for (auto it = sql.begin(); it != sql.end(); ++it) {
            if (it->first == id) {
                f = 1;
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