#include <map>
#include <string>
#include <iostream>

namespace db
{
  const int size_table = 10;
  std:: map<std::string, std::string> base1;
  bool is_learned[200];
  void fill(std::map<std::string, std::string> base);
  bool check_ans(std::map<std::string,std::string> base ,std::string a,std::string b) ;
  void cards(std::map<std::string, std::string> base,std::string integ, bool flag) ;
  void print(std::map<std::string, std::string> base) ;
  
}
