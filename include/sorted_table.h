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

    void insert(int id, Polinom pol) {
        if (this->find(id) != sql.end()) {
            return;
        }
        std::pair<int, Polinom> tmp (id, pol);
        /*for (int i = sql.size(); i > 0; i--) {
            if (id < )
        };*/

    }

    void erase(int id) {
        auto it = find(id);
        if (it != sql.end()) {
            sql.erase(it);
        }
    }


    std::vector<std::pair<int, Polinom> >::const_iterator find(int target_id) {
        int left = 0;
        int right = static_cast<int>(sql.size()) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            const int current_id = sql[mid].first;

            if (current_id == target_id) {
                return sql.begin() + mid;
            }

            if (current_id < target_id) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return sql.end();
    }

    int size() {
        return sql.size();
    }

    friend bool operator==(SortedTable& t1, SortedTable& t2) {
        if (t1.size() != t2.size()) {
            return false;
        }
        for (int i = 0; i < t1.size(); i++) {
            if (t1.sql[i]!= t2.sql[i]) return false;
        }
        return true;
    }

    friend bool operator!=(SortedTable t1, SortedTable t2) {
        return !(t1 == t2);
    }


};