//
// Created by Софья Фролова  on 10.03.2025.
//

#ifndef POLINOM_DATABASEVECTOR_H
#define POLINOM_DATABASEVECTOR_H

#include "polinom.h"

class DataBaseVector : public Polinom<std::string> {
public:
    DataBaseVector(const std::string& str) : Polinom<std::string>(str) {}
    void sort() {
        for (int i = 0; i < monoms.size(); i++) {
            for (int j = i + 1; j < monoms.size(); j++) {
                if (monoms[i] > monoms[j]) {
                    std::swap(monoms[i], monoms[j]);
                }
            }
        }
    }
    void insert (Monom m) {
        monoms.push_back(m);
        sort();
    }

    void erase (Monom m) {
        for (int i = 0; i < monoms.size(); i++) {
            if (monoms[i] == m) {
                monoms.erase(monoms.begin() + i);
            }
        }
    }

    int find(Monom m) {
        for (int i = 0; i < monoms.size(); i++) {
            if (monoms[i] == m) {
                return i;
            }
        }
        return -1;
    }
};
#endif //POLINOM_DATABASEVECTOR_H
