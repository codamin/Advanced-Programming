#include <iostream>
#include "Request.h"
#include "Request_Good.h"
#include "header.h"
#include <vector>
using namespace std;

Request::Request(string _id, string _buyer_username)
{
  id = _id;
  buyer_username = _buyer_username;
  active = true;
}

void Request::print()
{
  for(int idx = 0 ; idx < goods.size() ; idx++)
  {
    Request_Good good = goods[idx];
    string name = good.get_good_name();
    int count = good.get_good_count();
    string seller_username = good.get_seller_username();
    cout << "#" << idx + 1 << ". " << name << " " << count <<
     " " << seller_username << endl;
  }
}
