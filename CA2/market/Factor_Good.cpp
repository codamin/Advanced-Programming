#include <iostream>
#include <vector>
#include "Factor_Good.h"
#include "header.h"

using namespace std;


Factor_Good::Factor_Good(string _good_name, int _good_count,
 float _good_price, string _seller_username)
  {
    good_name = _good_name;
    good_count = _good_count;
    good_price = _good_price;
    seller_username = _seller_username;
  }
