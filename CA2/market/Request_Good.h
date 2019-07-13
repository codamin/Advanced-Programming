#ifndef REQUEST_GOOD_H
#define REQUEST_GOOD_H
using namespace std;

class Request_Good
{
private:
  string good_name;
  int good_count;
  string seller_username;
public:
  Request_Good(string good_name, int good_count, string seller_username);
  string get_good_name(){return good_name;}
  int get_good_count(){return good_count;}
  string get_seller_username(){return seller_username;}
  void print();
};
#endif
