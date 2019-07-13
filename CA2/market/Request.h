#ifndef REQUEST_H
#define REQUEST_H
#include <vector>
#include "Request_Good.h"
using namespace std;

class Request
{
private:
  string id;
  string buyer_username;
  vector<Request_Good> goods;
  bool active;
public:
  Request(string id, string buyer_username);
  void add_request_good(Request_Good request_good){
  goods.push_back(request_good);}
  string get_id(){return id;}
  string get_buyer_username(){return buyer_username;}
  vector<Request_Good> get_goods(){return goods;}
  bool get_active(){return active;}
  void deactive(){active = false;}
  void print();
};
#endif
