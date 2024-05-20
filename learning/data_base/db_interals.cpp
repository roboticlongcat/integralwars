#include "db_interals.h"
#include <algorithm>
#include <iostream>

namespace db{
  std::vector<base_line> Data_base;
    std::vector<base_line> Data_base_Diff;
std::ostream & operator<<(std::ostream & os, const base_line & bl) {
    os << bl.p.first << ": " << bl.p.second;
    return os;
}

void fill(int size_table, std::vector<base_line>& q,bool type_id) {
    for (int i = 1; i <= size_table; i++) {
        std::pair<std::string, std::string> new_one;
        if (type_id == false)
        {   //list_img/1.png
            new_one.first = "list_img/"+std::to_string(i) + ".png";
            new_one.second = "list_img/ans" + std::to_string(i) + ".png";
        }
        else
        {
            new_one.first = "list_img/"+std::to_string(i) + "_dif.png";
            new_one.second = "list_img/ans" + std::to_string(i) + "_dif.png";
        }

        q.push_back(base_line(new_one, false));
    }
}



void cards(const std::string & integ, bool flag , std::vector<base_line>& q) {
    auto it = std::find(q.begin(), q.end(), integ);
    if (it != q.end())
    {
        it->change_state(flag);
        std::cout << it->ans_card() << std::endl;
    }
}

void print(std::vector<base_line>& q) {
    for (const auto& it : q) std::cout << it<<"   "<<it.st() << std::endl;
}

int find_card(std::vector<base_line>& q, std::string img_name) {
    for (auto it = q.begin(); it != q.end(); ++it) {
        if (it->get_p().first == img_name) return distance(q.begin(), it);
    }
    return -1; // элемент не найден
}
}
