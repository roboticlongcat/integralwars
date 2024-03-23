#include <map>
#include <string>
#include <iostream>

namespace db
{
  const int size_table = 10;
  std:: map<std::string, std::string> base1;
  bool is_learned[200];
  void fill(std::map<std::string, std::string> base)
  {
	  for (int i = 0; i < size_table; i++)
	  {
		  is_learned[i] = false;
		  base[(std::to_string(i)+".png")] = ("ans"+std::to_string(i) + ".png");
	  }
  }
  bool check_ans(std::map<std::string,std::string> base ,std::string a,std::string b) //проверка ответа
  {
	  auto it = base.find(a);
	  if (it->second == b)
	  {
		  return true;
	  }
	  else 
	  {
		  return false;
	  }
  }
  void cards(std::map<std::string, std::string> base,std::string integ, bool flag) //переворот карточки и изменение состояния
  {
	  auto it = base.find(integ);
	  int num = distance(base.begin(),it);
	  is_learned[num] = flag;
	  std::cout <<  it->second  << std::endl;

  }
  void print(std::map<std::string, std::string> base) //вывод всей базы данных 
  {
	  auto it = base.begin();
	  for (int i = 0 ; it != base.end(); it++, i++) {  
		  std::cout << i << "   " << it->first << "   " << it->second <<" "<<is_learned[i]<< std::endl;
	  }
	  
  }
  
}
