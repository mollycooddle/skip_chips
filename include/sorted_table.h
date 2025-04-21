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

        for (auto it = sql.end() - 1; it > sql.begin(); --it) {
            auto prev_it = it - 1;
            if (it->first < prev_it->first) {
                swap(*it, *prev_it);
            } else if (prev_it->first == id) {
                throw std::runtime_error("Element with id " + std::to_string(id) + " already exists");
            }
        }
    }

    //Удаление элемента из таблицы за O(n)
    void erase (int id) {
        if (sql.empty()) {
            throw std::runtime_error("Table is empty");
        }

        for (auto it = sql.begin(); it != sql.end(); ++it) {
            if (it->first == id) {
                sql.erase(it);
                return;
            }
        }
        throw std::runtime_error("Element with id " + std::to_string(id) + " not found");
    }

    //Использую бинарынй поиск, который выполняется за O(log n)
    Polinom find(int id) {
        auto begin = sql.begin();
        auto end = sql.end() - 1;

        while (begin <= end) {
            auto mid = begin + std::distance(begin, end) / 2; //std::distance(begin, end) вычисляет, сколько элементов в контейнере

            if (mid->first == id) {
                return mid->second;
            }
            else if (mid->first < id) {
                begin = mid + 1;
            }
            else {
                end = mid - 1;
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
    void print() {
        for (auto it = sql.begin(); it != sql.end(); ++it) {
            std::cout << it->first << " " << it->second << std::endl;
        }
    }

    class Iterator {
        std::vector<std::pair<int, Polinom>>::iterator iter;

    public:
        Iterator(std::vector<std::pair<int, Polinom>>::iterator it) : iter(it) {}

        Iterator() : iter(){}

        std::pair<int, Polinom>& operator*() { return *iter; }

        Iterator& operator++() { ++iter; return *this; }

        bool operator!=(const Iterator& other) const { return iter != other.iter; }

        bool operator==(const Iterator& other) const { return iter == other.iter; }

        std::pair<int, Polinom>* operator->() { return &(*iter); }
    };

    Iterator begin() { return Iterator(sql.begin()); }

    Iterator end() { return Iterator(sql.end()); }


};