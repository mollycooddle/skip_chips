#ifndef POLINOM_HASH_TABLE_H
#define POLINOM_HASH_TABLE_H

#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include "polinom1.h"
#include <tuple>
#include <list>
#include <stdexcept>

template <typename TKey, typename TValue, typename TFlag>
class HashTable {
private:
    std::vector<std::vector<std::tuple<TKey, TValue, TFlag >>> table; // метод цепочек
    size_t count_element = 0;
    double MAX_LOAD_FACTOR = 0.7;



    bool fullTable() {
        if (count_element == 0) return false;
        if (count_element / table.size() <= MAX_LOAD_FACTOR) return false;
        return true;
    }

    void rehash() {
        size_t new_size = table.size() * 2 + 1;
        std::vector<std::vector<std::tuple<TKey, TValue, TFlag>>> new_table(new_size);

        for (auto& bucket : table) {
            for (auto& entry : bucket) {
                if (std::get<2>(entry)) {
                    // Вычисляем хеш для новой таблицы
                    size_t new_index = std::hash<TKey>{}(std::get<0>(entry)) % new_size; // Вычисляем индекс в новой таблице
                    new_table[new_index].push_back(entry);
                }
            }
        }
        table = std::move(new_table);
    }


public:
    size_t hash_function(const TKey& key) const {
        return std::hash<TKey>{}(key) % table.size();
    }

    HashTable& operator=(const HashTable& other) {
        table = other.table;
        count_element = other.count_element;
        return *this;
    }

    HashTable() {
        table.resize(1); // Устанавливает размер вектора
        count_element = 0;
    }

    HashTable(int n) {
        count_element = 0; // Инициализируем count_element нулём
        table.resize(n);   // Устанавливаем размер таблицы
    }

    ~HashTable() = default;

    //Средний случай: O(1)
    void insert(TKey key, TValue value) {
        if (fullTable()) {
            rehash();
        }

        size_t index = hash_function(key);
        for (auto& entry : table[index]) {
            if (std::get<0>(entry) == key && !std::get<2>(entry)) { // флаг равен false
                std::get<1>(entry) = value;
                std::get<2>(entry) = true;
                count_element++;
                return;
            }
        }

        table[index].emplace_back(key, value, true); // Добавление нового элемента в кортеже
        count_element++;
    }

    //Средний случай: O(1)
    TValue find(const TKey& key) {
        if (table.empty()) {
            throw std::runtime_error("Key not found in table");
        }

        size_t index = hash_function(key);
       // std::cout << "Erasing key " << key << " at bucket " << index << std::endl;
        for (auto& entry : table[index]) {
            if (std::get<0>(entry) == key && std::get<2>(entry)) { // Проверка активного флага (bool)
                return std::get<1>(entry);
            }
        }

        throw std::runtime_error("Key not found in table");
    }

    //Средний случай: O(1)
    void erase(const TKey& key) {
        if (table.empty()) {
            throw std::runtime_error("Table is empty");
        }

        size_t index = hash_function(key);


        for (auto& entry : table[index]) {
            if (std::get<0>(entry) == key && std::get<2>(entry)) { // Проверяем активный флаг
                std::get<2>(entry) = false;
                count_element--;
                return;
            }
        }

        throw std::runtime_error("Key not found in table");
    }

    int size() {
        return table.size();
    }

    int count() {
        return count_element;
    }

    bool empty() {
        return count_element == 0;

    }

};
#endif //POLINOM_HASH_TABLE_H
