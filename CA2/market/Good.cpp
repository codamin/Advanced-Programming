#include <iostream>
#include "header.h"
#include "Good.h"
#include <cstdlib>
#include <vector>
using namespace std;

Good::Good(vector<string> input_data)
{
  on_sale = false;
  sold_number = 0;
  special = false;
  seller_username = input_data[1];
  special_count = 0;
  name = input_data[2];
  price = atoi(input_data[3].c_str());
  count = atoi(input_data[4].c_str());
}

bool Good::requested_already(string buyer_username)
{
  for(int iter = 0 ; iter < sale_requesters.size() ; iter++)
  {
    if(sale_requesters[iter] == buyer_username)
      return true;
  }
  return false;
}

void Good::add_to_sale_requesters(string buyer_username)
{
  if(requested_already(buyer_username))
    cout << FAIL_MESSAGE << endl;
  else
  {
  sale_requesters.push_back(buyer_username);
  cout << OK_MESSAGE << endl;
  }
}

void Good::lower_price()
{
  if(!on_sale){
  on_sale = true;
  float off = float(OFF/100.0);
  price = price * (1 - off);
  }
}

void Good::print()
{
  cout << name << " " << count << " " << price << " " <<
  seller_username << endl;
}
