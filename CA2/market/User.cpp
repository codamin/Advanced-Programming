#include <iostream>
#include "header.h"
#include "User.h"
#include <cstdlib>
#include <vector>
using namespace std;

User::User(vector<string> input_data)
{
  first_name = input_data[1];
  last_name  = input_data[2];
  username = input_data[3];
  phone_number = input_data[4];
  money = atoi(input_data[5].c_str());
  role = input_data[6];
}

bool User::is_same(User other_user)
{
  bool f_name_eq = first_name == other_user.first_name;
  bool l_name_eq = last_name == other_user.last_name;
  bool phone_number_eq = phone_number == other_user.phone_number;

  return f_name_eq && l_name_eq && phone_number_eq;
}

void User::update_role()
{
  role = "buyer-seller";
}

void User::print()
{
  cout << first_name << " " << last_name << " " <<
  username << " " << phone_number << " " << role << " " << money << endl;
}
