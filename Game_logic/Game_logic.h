#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

namespace db {
    // объявления функций из кода Ани
    extern const int size_table;
    extern std::map<std::string, std::string> base1;
    extern bool is_learned[];

    void fill(std::map<std::string, std::string> base);
    bool check_ans(std::map<std::string,std::string> base ,std::string a,std::string b);
    void cards(std::map<std::string, std::string> base,std::string integ, bool flag);
    void print(std::map<std::string, std::string> base);
}

// объявления функции из сpp
void playGame();

#endif // GAME_LOGIC_H
