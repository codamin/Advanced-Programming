#ifndef GOOD_H
#define GOOD_H
using namespace std;
class Good
{
private:
  string seller_username;
  string name;
  float price;
  int count;
  bool on_sale;
  vector<string> sale_requesters;
  int sold_number;
  bool special;
  int special_count;
public:
  Good(vector<string> input_data);
  string get_seller_username(){ return seller_username; }
  string get_name(){ return name; }
  float get_price(){ return price; }
  int get_count(){ return count; }
  string set_seller_username(string _seller_username)
  { seller_username = _seller_username; }
  string set_name(string _name){ name = _name; }
  int set_price(int _price){ price = _price; }
  int set_count(int _count){ count = _count; }
  friend bool sort_type(const Good& , const Good&);
  void increment_sold_number(){ sold_number++ ;}
  void decreas_count(int _count){ count -= _count; }
  void print();
  bool requested_already(string buyer_username);
  void add_to_sale_requesters(string buyer_username);
  void lower_price();
  int get_sold_number(){ return sold_number;}
  int get_num_of_sale_requesters(){ return sale_requesters.size();}
  void make_on_sale(){ on_sale = true;}
  void make_special(int _special_count)
  { special = true; special_count = _special_count;}
  void remove_special(){ special = false;}
  bool is_special(){ return special;}
  bool is_on_sale(){ return on_sale;}
  void remove_from_sale(){on_sale = false;}
};
#endif
