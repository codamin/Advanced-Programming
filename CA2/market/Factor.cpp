#include <iostream>
#include "header.h"
#include "Factor.h"
#include "Factor_Good.h"
#include <vector>
using namespace std;

Factor::Factor(string _buyer_first_name, string _buyer_last_name,
string _buyer_username, string _buyer_phone_number)
{
 buyer_first_name = _buyer_first_name;
 buyer_last_name = _buyer_last_name;
 buyer_username = _buyer_username;
 buyer_phone_number = _buyer_phone_number;
}

void Factor::print()
{
  cout << "Factor number #"<< factor_print_count << endl;
  cout << buyer_first_name << " " << buyer_last_name
  << " " << buyer_username << " " << buyer_phone_number << endl;
  float goods_sum = 0;
  cout << "#. Goods Name | Goods Count | Goods Price | Seller Username |"<<
  "Sum (count * price )" << endl;
  for(int idx = 0 ; idx < goods.size() ; idx++)
  {
    cout << idx + 1 << "." << " ";
    int sum = goods[idx].get_price() * goods[idx].get_count();
    goods_sum += sum;
    cout << goods[idx].get_name() << " | " << goods[idx].get_count() << " | " <<
    goods[idx].get_price() << " | " << goods[idx].get_seller_username() <<
    " | " << sum << endl;
    factor_print_count ++;
  }
  cout << "Goods_sum = " << goods_sum << endl;
  cout << "Total_sum = " << goods_sum * (1.0 + float(STORE_SHARE/100.0)) << endl << endl;}
