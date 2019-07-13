#include <algorithm>
#include <iostream>
#include <string>
#include "Store.h"
#include "User.h"
#include "Good.h"
#include "Request_Good.h"
#include "Request.h"
#include "Factor_Good.h"
#include "Factor.h"
#include "functions.h"
#include "header.h"
using namespace std;

vector<string> split(string str , char c)
{
  vector<string> splitted;
  string word = "";
  for(int iter = 0 ; iter < str.size() ; iter++)
  {
    if(str[iter] == c)
    {
       splitted.push_back(word);
       word = "";
    }
    else
    {
      word.push_back(str[iter]);
    }
  }
  splitted.push_back(word);
  return splitted;
}

void print_vector(vector<string> v)
{
  for(int iter = 0 ; iter < v.size() ; iter++)
  {
    cout<<v[iter];
  }
}

void read_inputs(Store &store)
{
  string line;
  while(getline(cin, line))
  {
    store.check_for_offs();
    vector<string> input_data = split(line, ' ');
    string command = input_data[0];
    if(command == "add_user" && input_data.size() == ADD_USER_INPUT_SIZE )
      store.add_user(input_data);
    else if(command == "add_good" && input_data.size() == ADD_GOOD_INPUT_SIZE)
      store.add_good(input_data);
    else if(command == "search" && input_data.size() == SEARCH_INPUT_SIZE)
      store.search_good_by_name(input_data);
    else if(command == "buy")
    {
      string buyer_username = split(line, ' ')[1];
      vector< vector<string> > buy_commands = get_buy_commands(line);
      store.sell(buy_commands, buyer_username);
    }
    else if(command == "sale")
      store.add_sale_request(input_data);
    else if(command == "add_money")
      store.add_money_to_user(input_data);
    else if(command == "add_special")
      store.add_special(input_data);
    else if(command == "remove_special")
      store.remove_special(input_data);
    else if(command == "request")
    {
      string buyer_username = split(line, ' ')[2];
      string id = split(line, ' ')[1];
      vector< vector<string> > request_commands = get_request_commands(line);
      store.add_request(request_commands, id, buyer_username);
    }
    else if(command == "print_request")
      store.print_request(input_data);
    else if(command == "print_factor")
      store.print_factors(input_data);
    else if(command == "search_sale")
      store.search_sale();
    else if(command == "‫‪search_bestseller‬‬")
      store.search_bestseller();
    else
      cout << FAIL_MESSAGE << endl;
  }
  return;
}

vector< vector<string> > get_buy_commands(string line)
{
  vector< vector<string> > buy_commands;
  char buy_continue = line.back();
  line.pop_back();
  vector<string> first_command = split(line, ' ');
  first_command.erase(first_command.begin() , first_command.begin() + 2 );
  buy_commands.push_back(first_command);
  string new_line;
  while(buy_continue == ',')
  {
    getline(cin, new_line);
    buy_continue = new_line.back();
    new_line.pop_back();
    buy_commands.push_back(split(new_line, ' '));
  }
  return buy_commands;
}

vector< vector<string> > merge_buy_commands(vector< vector<string> >buy_commands)
{
  vector< vector<string> > merged_buy_commands;
  for(int first = 0 ; first < buy_commands.size() ; first++)
  {
    for(int second = first+1 ; second <buy_commands.size() ; second++ )
    {
      if(buy_commands[first][0] == buy_commands[second][0] &&
         buy_commands[first][2] == buy_commands[second][2])
         {
           buy_commands[first][1] += buy_commands[second][1];
           buy_commands.erase(buy_commands.begin() + second + 1);
         }
    }
  }
  return buy_commands;
}

bool sort_type(const Good &a , const Good &b)
{
  if(a.count != b.count)
    return a.count > b.count;
  else
  {
    if(a.price != b.price)
      return a.price > b.price;
    else
      return a.name >= b.name;
  }
}

vector< vector<string> > get_request_commands(string line)
{
  vector< vector<string> > request_commands;
  char request_continue = line.back();
  line.pop_back();
  vector<string> first_command = split(line, ' ');
  first_command.erase(first_command.begin() , first_command.begin() + 3 );
  request_commands.push_back(first_command);
  string new_line;
  while(request_continue == ',')
  {
    getline(cin, new_line);
    request_continue = new_line.back();
    new_line.pop_back();
    request_commands.push_back(split(new_line, ' '));
  }
  return request_commands;
}

void sort_goods(vector<Good> &goods)
{
  sort(goods.begin() , goods.end() , sort_type);
}
