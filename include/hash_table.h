#pragma once
#include <vector>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include "polinom.h"

template <class Tkey, class Tvalue>
class HashO {
    struct tuple {
        Tkey key;
        Tvalue value;
        bool flag;              // Флаг удаления (true - удалён)
        bool empty;             // Флаг пустой ячейки

        Tkey getKey() const { return key; }
        Tvalue getValue() const { return value; }
        bool getFlag() const { return flag; }
        bool getEmpty() const { return empty; }

        tuple() : flag(false), empty(true) {}
        tuple(Tkey key) : key(key), value(Tvalue()), flag(false), empty(true) {}
        tuple(Tkey key, Tvalue value) : key(key), value(value), flag(false), empty(false) {}
    };

    std::vector<tuple> table;
    int size;
    int capacity;
    long long a, b;
    const int simpleNum = 1'000'000'007;

public:
    HashO(int initialCapacity = 157) : size(0), capacity(initialCapacity) {
        table.resize(capacity);
        std::srand(std::time(NULL));
        //a = (std::abs(std::rand()) % (simpleNum - 1)) + 1;              // a ∈ [1, simpleNum-1]
        //b = std::abs(std::rand()) % simpleNum;                          // b ∈ [0, simpleNum-1]
        a = simpleNum;
        b = simpleNum;
    }

    // Хеш-функция для строк (ключей)
    int Hash(const std::string& s) const {
        unsigned long long x = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            x = (x * 31 + s[i]) % simpleNum;                // Полиномиальное хеширование
        }
        return ((a * x + b) % simpleNum) % capacity;
    }

    void insert(const Tkey& key, const Tvalue& value) {
        if (size >= capacity * 0.6) { rehash(); }               // Рехеширование при заполнении >60%

        int index = Hash(key);
        int startIndex = index;
        bool foundDeleted = false;
        int deletedIndex = -1;

        // Поиск места для вставки
        while (!table[index].getEmpty()) {
            if (!table[index].getFlag() && table[index].getKey() == key) {
                throw std::runtime_error("Key already exists");
            }
            if (table[index].getFlag() && !foundDeleted) {
                foundDeleted = true;
                deletedIndex = index;               // Запомнить первую удаленную ячейку
            }
            index = (index + 1) % capacity;             // Линейное пробирование
            if (index == startIndex) {
                throw std::runtime_error("Hash table is full");
            }
        }

        // Вставка в удаленную или пустую ячейку
        if (foundDeleted) {
            index = deletedIndex;
        }

        table[index] = tuple(key, value);
        size++;
    }

    Tvalue find(const Tkey& key) const {
        int index = Hash(key);
        int startIndex = index;

        do {
            if (table[index].getEmpty() && !table[index].getFlag()) {
                throw std::runtime_error("Key not found");
            }
            if (!table[index].getFlag() && !table[index].getEmpty() && table[index].getKey() == key) {
                return table[index].getValue();
            }
            index = (index + 1) % capacity;             // Линейное пробирование
        } while (index != startIndex);

        throw std::runtime_error("Key not found");
    }

    void erase(const Tkey& key) {
        int index = Hash(key);
        int startIndex = index;

        do {
            if (table[index].getEmpty() && !table[index].getFlag()) {
                throw std::runtime_error("Key not found");
            }
            if (!table[index].getFlag() && !table[index].getEmpty() && table[index].getKey() == key) {
                table[index].flag = true;               // Пометить как удаленный
                size--;
                return;
            }
            index = (index + 1) % capacity;
        } while (index != startIndex);

        throw std::runtime_error("Key not found");
    }

    Tvalue& operator[](const Tkey& key) {
        int index = Hash(key);
        int startIndex = index;

        do {
            if (table[index].getEmpty() && !table[index].getFlag()) {
                throw std::runtime_error("Key not found");
            }
            if (!table[index].getFlag() && !table[index].getEmpty() && table[index].getKey() == key) {
                return table[index].value;
            }
            index = (index + 1) % capacity;
        } while (index != startIndex);

        throw std::runtime_error("Key not found");
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    class iterator {
        friend class HashO;

        typename std::vector<tuple>::iterator table_it;
        typename std::vector<tuple>::iterator table_end;

        // Приватный конструктор (может вызывать только HashO)
        iterator(typename std::vector<tuple>::iterator it,
            typename std::vector<tuple>::iterator end)
            : table_it(it), table_end(end)
        {
            // Пропускаем пустые и удалённые элементы
            while (table_it != table_end &&
                (table_it->getEmpty() || table_it->getFlag())) {
                ++table_it;
            }
        }

    public:
        iterator() = delete;

        iterator& operator++() {
            do {
                ++table_it;
            } while (table_it != table_end &&
                (table_it->getEmpty() || table_it->getFlag()));

            return *this;
        }

        std::pair<const Tkey&, Tvalue&> operator*() {
            return { table_it->key, table_it->value };
        }

        std::pair<const Tkey*, Tvalue*> operator->() {
            return { &table_it->key, &table_it->value };
        }

        bool operator==(const iterator& other) const {
            return table_it == other.table_it;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    iterator begin() {
        return iterator(table.begin(), table.end());
    }

    iterator end() {
        return iterator(table.end(), table.end());
    }

private:
    void rehash() {
        int newCapacity = capacity * 2 + 1;             // Увеличение размера
        std::vector<tuple> newTable(newCapacity);

        // Перенос элементов в новую таблицу
        for (const auto& item : table) {
            if (!item.getEmpty() && !item.getFlag()) {
                int index = Hash(item.getKey()) % newCapacity;
                while (!newTable[index].getEmpty()) {
                    index = (index + 1) % newCapacity;
                }
                newTable[index] = item;
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }
};