#ifndef FACTOR_H
#define FACTOR_H
#include "Factor_Good.h"
using namespace std;

class Factor
{
private:
  string buyer_first_name;
  string buyer_last_name;
  string buyer_username;
  string buyer_phone_number;
  vector<Factor_Good> goods;
public:
  static int factor_print_count;
  void add_factor_good(Factor_Good factor_good)
  { goods.push_back(factor_good); }
  Factor(string, string, string, string);
  void print();
  vector<Factor_Good> get_goods(){return goods;}
  string get_buyer_username(){return buyer_username;}
};
#endif
