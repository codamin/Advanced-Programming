#ifndef STORE_H
#define STORE_H
#include <vector>
#include <iostream>
#include <string>
#include "User.h"
#include "Good.h"
#include "Request_Good.h"
#include "Request.h"
#include "Factor_Good.h"
#include "Factor.h"
class Store;
#include "functions.h"
#include "header.h"
using namespace std;

class Store
{
private:
  vector<User> users;
  vector<Good> goods;
  vector<Factor> factors;
  vector<Request> requests;
  float money = 0;
public:
  void search_good_by_name(vector<string> input_data);
  int search_good_by_sellerUN(string good_name, int good_count,
  string seller_username);
  int search_good_without_count(string good_name, string seller_username);
  bool check_enough_money(vector< vector<string> > buy_commands,
  string username);
  bool check_enough_good(const vector< vector<string> >& buy_commands);
  void take_from_goods(vector< vector<string> > buy_commands);
  Factor make_factor(string buyer_username,
  vector< vector<string> > buy_commands);
  void sell(vector< vector<string> > buy_commands, string buyer_username);
  int exist(string username);
  bool exist(Good good);
  int registration_num(User new_user);
  void add_user(vector<string> input_data);
  void add_good(vector<string> input_data);
  void add_money_to_user(vector<string> added_money);
  void add_factor_goods(vector< vector<string> > buy_commands,
  Factor& new_factor);
  void print_users();
  void check_for_offs();
  void check_number_of_good();
  void check_for_sales();
  void check_best_sellers();
  void add_sale_request(vector<string> input_data);
  void print_goods(){for(int i=0;i<goods.size();i++){goods[i].print();}}
  void print_goods(vector<Good> &goods);
  void add_special(vector<string> input_data);
  void remove_special(vector<string> input_data);
  void check_special();
  void add_request(vector< vector<string> > request_commands,
  string id, string buyer_username);
  Request make_request(string buyer_username,
  vector< vector<string> > request_commands, string id);
  void check_requests();
  void add_request_goods(vector< vector<string> > request_commands,
  Request& new_request);
  void take_from_goods(Request request);
  void answer_request(Request request);
  bool is_available(Request request);
  bool check_enough_money(Request request);
  void print_request(vector<string> input_data);
  void print_factors(vector<string> input_data);
  void search_sale();
  void search_bestseller();
};
#endif
