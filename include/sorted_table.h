#pragma once

#include "polinom.h"
#include <sstream>
#include <algorithm>
#include <utility>

class SortedTable {
private:
    std::vector<std::pair<int, Polinom> > sql;

public:

    SortedTable() = default;
    SortedTable(int id, Polinom pol) {
        sql.push_back(std::pair<int, Polinom> (id, pol));
    }

    //Вставка элемента в таблицу за O(n)
    void insert(int id, Polinom pol) {

        sql.push_back(std::pair<int, Polinom> (id, pol));

        for (int i = sql.size() - 1; i > 0; i--) {
            if (sql[i].first < sql[i - 1].first) {
                std::swap(sql[i], sql[i - 1]);
            }
            else if (sql[i-1].first == id) {
                this->erase(id);
                throw std::runtime_error("Element with id " + std::to_string(id) + " already exists");
            }
        }
    }

    //Удаление элемента из таблицы за O(n)
    void erase (int id) {
        if (sql.empty()) {
            throw std::runtime_error("Table is empty");
        }

        for (int i = 0; i < sql.size(); i++) {
            if (sql[i].first == id) {
                sql.erase(sql.begin() + i);
                return;
            }
            else throw std::runtime_error("Element with id " + std::to_string(id) + " not found");
        }
    }

    //Использую бинарынй поиск, который выполняется за O(log n)
    Polinom find(int id) {
    int left = 0;
    int right = sql.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int current_id = sql[mid].first;

        if (current_id == id) {
            return sql[mid].second;  // метод для std::pair
        } else if (current_id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    throw std::out_of_range("Element with id " + std::to_string(id) + " not found");
    }

    int size() {
        return sql.size();
    }

    bool empty() {
        return sql.empty();
    }

    bool operator==(const SortedTable& other) const {
        return sql == other.sql;
    }

    bool operator!=(const SortedTable& other) const {
        return !(sql == other.sql);
    }

};