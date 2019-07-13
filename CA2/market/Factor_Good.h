#ifndef FACTOR_GOOD_H
#define FACTOR_GOOD_H
using namespace std;

class Factor_Good
{
private:
  string good_name;
  int good_count;
  float good_price;
  string seller_username;
public:
  Factor_Good(string _good_name, int _good_count,
    float _good_price, string _seller_username);
  string get_name(){return good_name;}
  int get_count(){return good_count;}
  float get_price(){return good_price;}
  string get_seller_username(){return seller_username;}
};
#endif
