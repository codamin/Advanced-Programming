#include <iostream>
#include "Request_Good.h"
#include <vector>
#include "header.h"
using namespace std;

Request_Good::Request_Good(string _good_name, int _good_count, string _seller_username)
{
  good_name = _good_name;
  good_count = _good_count;
  seller_username = _seller_username;
};
