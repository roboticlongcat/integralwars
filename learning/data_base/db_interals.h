#ifndef DB_INTERALS_H
#define DB_INTERALS_H

#include <vector>
#include <string>

namespace db {
    class base_line {
        std::pair<std::string, std::string> p;
        bool is_learned;
        bool type = false; // 0-int, 1-diff
    public:
        base_line(const std::pair<std::string, std::string>& new_one, bool l)
            : p(new_one), is_learned(l) {}

        bool operator==(const std::string& rhs) const {
            return p.first == rhs;
        }
        std::pair<std::string, std::string> get_p() const { return p; }

        std::string ans_card() const {
            return p.second;
        }
         bool st() const { return is_learned; }
        void change_state(bool st) {
            is_learned = st;
        }

        friend std::ostream& operator<<(std::ostream& os, const base_line& bl);
    };

    extern std::vector<base_line> Data_base;
    extern std::vector<base_line> Data_base_Diff;

    void fill(int size_table, std::vector<base_line>& q, bool type_id);
    void print(std::vector<base_line>& q);
    int find_card(std::vector<base_line>& q,std::string img_name);
}

#endif // DB_INTERALS_H
