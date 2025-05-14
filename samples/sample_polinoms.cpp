#include "polinom1.h"
#include "unsorted_table.h"
#include "sorted_table.h"
#include "RBTree.h"
#include "avl_tree.h"
#include "hash_table.h"
#include "hash_table1.h"
#include <locale.h>

using namespace std;

// Базовый интерфейс для работы с разными базами данных
template <typename TKey, typename TValue>
class IDatabase {
public:
    virtual void insert(const TKey& key, const TValue& value) = 0;
    virtual void erase(const TKey& key) = 0;
    virtual TValue find(const TKey& key) = 0;
    virtual ~IDatabase() = default;
};

// Реализация для AVLTree
template <typename TKey, typename TValue>
class AVLTreeWrapper : public IDatabase<TKey, TValue> {
    AVLTree<TKey, TValue> avlTree;
public:
    void insert(const TKey& key, const TValue& value) override {
        avlTree.insert(key, value);
    }
    void erase(const TKey& key) override {
        avlTree.erase(key);
    }
    TValue find(const TKey& key) override {
        return avlTree.find(key);
    }
};

// Реализация для HashTable (из hash_table.h)
template <typename TKey, typename TValue>
class HashTableWrapper : public IDatabase<TKey, TValue> {
    HashTable<TKey, TValue, bool> hashTable;
public:
    void insert(const TKey& key, const TValue& value) override {
        hashTable.insert(key, value);
    }
    void erase(const TKey& key) override {
        hashTable.erase(key);
    }
    TValue find(const TKey& key) override {
        return hashTable.find(key);
    }
};

// Реализация для HashO (из hash_table1.h)
template <typename TKey, typename TValue>
class HashOWrapper : public IDatabase<TKey, TValue> {
    HashO<TKey, TValue> hashO;
public:
    void insert(const TKey& key, const TValue& value) override {
        hashO.insert(key, value);
    }
    void erase(const TKey& key) override {
        TKey nonConstKey = key;
        hashO.erase(nonConstKey);
    }
    TValue find(const TKey& key) override {
        return hashO.find(key);
    }
};

// Реализация для RBTree
template <typename TKey, typename TValue>
class RBTreeWrapper : public IDatabase<TKey, TValue> {
    RBTree<TKey, TValue> rbTree;
public:
    void insert(const TKey& key, const TValue& value) override {
        rbTree.insert(key, value);
    }
    void erase(const TKey& key) override {
        rbTree.erase(key);
    }
    TValue find(const TKey& key) override {
        auto it = rbTree.find(key);
        if (it == rbTree.end()) {
            throw runtime_error("Key not found");
        }
        return it->value;
    }
};

// Реализация для SortedTable
class SortedTableWrapper : public IDatabase<string, Polinom> {
    SortedTable sortedTable;
public:
    void insert(const string& key, const Polinom& value) override {
        sortedTable.insert(key, value);
    }
    void erase(const string& key) override {
        sortedTable.erase(key);
    }
    Polinom find(const string& key) override {
        return sortedTable.find(key);
    }
};

// Реализация для UnsortedTable (DataBaseVector)
class UnsortedTableWrapper : public IDatabase<string, Polinom> {
    DataBaseVector unsortedTable;
public:
    void insert(const string& key, const Polinom& value) override {
        unsortedTable.insert(key, value);
    }
    void erase(const string& key) override {
        unsortedTable.erase(key);
    }
    Polinom find(const string& key) override {
        auto it = unsortedTable.find(key);
        if (it == unsortedTable.sql.end()) {
            throw runtime_error("Key not found");
        }
        return it->second;
    }
};

// Главное меню
int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Выберите структуру данных:\n";
    cout << "1. AVLTree\n";
    cout << "2. HashTable (цепочки)\n";
    cout << "3. HashTable1 (открытая адресация)\n";
    cout << "4. RBTree\n";
    cout << "5. SortedTable\n";
    cout << "6. UnsortedTable\n";

    int choice;
    cin >> choice;

    unique_ptr<IDatabase<string, Polinom>> stringDb;

    switch (choice) {
        case 1: stringDb = make_unique<AVLTreeWrapper<string, Polinom>>(); break;
        case 2: stringDb = make_unique<HashTableWrapper<string, Polinom>>(); break;
        case 3: stringDb = make_unique<HashOWrapper<string, Polinom>>(); break;
        case 4: stringDb = make_unique<RBTreeWrapper<string, Polinom>>(); break;
        case 5: stringDb = make_unique<SortedTableWrapper>(); break;
        case 6: stringDb = make_unique<UnsortedTableWrapper>(); break;
        default: 
            cout << "Неверный выбор!\n"; 
            return 1;
    }

    while (true) {
        cout << "\nВыберите действие:\n";
        cout << "1. Добавить полином (insert)\n";
        cout << "2. Удалить полином по ID (erase)\n";
        cout << "3. Найти полином по ID (find)\n";
        cout << "4. Выход\n";

        int action;
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера

        if (action == 4) break;

        try {
            if (action == 1) {
                cout << "Введите ID полинома: ";
                    string id;
                    getline(cin, id);
                    cout << "Введите полином (например, '2x^3y^1z^2 1x^1y^1z^1'): ";
                    string polyStr;
                    getline(cin, polyStr);
                    Polinom poly(polyStr);
                    stringDb->insert(id, poly);
                    cout << "Полином добавлен!\n";
            } else if (action == 2) {
                    cout << "Введите ID для удаления: ";
                    string id;
                    getline(cin, id);
                    stringDb->erase(id);
                    cout << "Полином удалён.\n";
            } else if (action == 3) {
                    cout << "Введите ID для поиска: ";
                    string id;
                    getline(cin, id);
                    Polinom result = stringDb->find(id);
                    cout << "Найден полином: " << result << "\n";
            } else {
                cout << "Неверное действие!\n";
                return 1;
            }
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << "\n";
        }
    }

    return 0;
}