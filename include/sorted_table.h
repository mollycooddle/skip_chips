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
    SortedTable (int id, Polinom pol) {
        std::pair<int, Polinom>  temp(id, pol);
    }
    void sort(){
        if (!sql.empty()) {
            quick_sort( 0, sql.size() - 1);
        }

    }

    void quick_sort(int low, int high) {
        if (low < high) {
            int pivot_value = sql[(low + high) / 2].first;
            int i = low - 1;
            int j = high + 1;

            while (true) {
                do {
                    i++;
                } while (sql[i].first < pivot_value);

                do {
                    j--;
                } while (sql[j].first > pivot_value);

                if (i >= j) {
                    break;
                }

                swap(sql[i], sql[j]);
            }

            int pivot_index = j;
            quick_sort( low, pivot_index);
            quick_sort( pivot_index + 1, high);
        }
    }

    void insert(int id, Polinom pol) {
        std::pair<int, Polinom> tmp (id, pol);
        sql.push_back(tmp);
        sort();
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

};