#include <iostream>
#include "Store.h"
#include "User.h"
#include "Good.h"
#include "Request_Good.h"
#include "Request.h"
#include "Factor_Good.h"
#include "Factor.h"
#include "functions.h"
#include "header.h"
#include <vector>
using namespace std;

void Store::add_user(vector<string> input_data)
{
  User new_user(input_data);
  if(exist(new_user.get_username()) != -1)
  {
    int user_index = registration_num(new_user);
    if(user_index != -1 && new_user.get_role() != users[user_index].get_role())
    {
      users[user_index].update_role();
      cout << OK_MESSAGE << endl;
      return;
    }
    else
    {
      cout << FAIL_MESSAGE << endl;
      return;
    }
  }
  users.push_back(new_user);
  cout << OK_MESSAGE << endl;
}

int Store::exist(string username)
{
  for(int iter = 0 ; iter < users.size() ; iter++)
  {
    if(users[iter].get_username() == username)
    {
       return iter;
    }
  }
return -1;
}

void Store::print_users()
{
  for(int i=0;i<users.size();i++)
  {
    cout<< i <<endl;
    users[i].print();
  }
}

int Store::registration_num(User new_user)
{
  for(int iter = 0 ; iter < users.size() ; iter++)
  {
    if(users[iter].is_same(new_user))
    {
       return iter;
    }
  }
return -1;
}

bool Store::exist(Good good)
{
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_seller_username() == good.get_seller_username())
      if(goods[iter].get_name() == good.get_name())
        {
           return true;
        }
  }
  return false;
}

void Store::add_good(vector<string> input_data)
{
  Good new_good(input_data);
  if(exist(new_good) || (exist(new_good.get_seller_username()) == -1)
  || users[exist(new_good.get_seller_username())].get_role() == "buyer")
  {
    cout << FAIL_MESSAGE << endl;
    return;
  }
  goods.push_back(new_good);
  cout << OK_MESSAGE << endl;
}

void Store::print_goods(vector<Good> &goods)
{
  sort_goods(goods);
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    cout << "#" << iter + 1 << "." << " ";
    goods[iter].print();
  }
}

void Store::search_good_by_name(vector<string> input_data)
{
  string good_name = input_data[1];
  int count = atoi(input_data[2].c_str());
  vector<Good> found_goods;
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_name() == good_name && goods[iter].get_count() >= count)
      found_goods.push_back(goods[iter]);
  }
  print_goods(found_goods);
}

int Store::search_good_without_count(string good_name, string seller_username)
{
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_name() == good_name &&
       goods[iter].get_seller_username() == seller_username)
       return iter;
  }
  return -1;
}

int Store::search_good_by_sellerUN(string good_name, int good_count,
string seller_username)
{
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_name() == good_name &&
     goods[iter].get_count() >= good_count &&
     goods[iter].get_seller_username() == seller_username)
       return iter;
  }
  return -1;
}

/*void Store::take_from_goods(string good_name, int good_count, string seller_username)
{
  int good_index = search_good_by_sellerUN(good_name, good_count,
     seller_username);
  if(good_index == -1)
  {
    cout << FAIL_MESSAGE << endl;
    return;
  }
  else
  goods[good_index].decreas_count(good_count);
}*/

bool Store::check_enough_good(const vector< vector<string> >& buy_commands)
{
  for(int idx = 0 ; idx < buy_commands.size() ; idx++)
  {
      //cout<<buy_commands[idx][0] << buy_commands[idx][1] << buy_commands[idx][2] << endl;
    if(search_good_by_sellerUN(buy_commands[idx][0],
      atoi(buy_commands[idx][1].c_str()),
      buy_commands[idx][2]) == -1)
    {
      return false;
    }
  }
  return true;
}

bool Store::check_enough_money(vector< vector<string> > buy_commands,
string buyer_username)
{
  int buyer_idx = exist(buyer_username);
  float buyer_money = users[buyer_idx].get_money();
  float needed_money = 0;
  float store_share = STORE_SHARE/100.0;
  for(int idx = 0; idx < buy_commands.size(); idx++)
  {
    needed_money += atoi(buy_commands[idx][1].c_str())
    * goods[search_good_by_sellerUN(buy_commands[idx][0],
    atoi(buy_commands[idx][1].c_str()), buy_commands[idx][2])].get_price()
    * (1 + store_share);
  }
  if(buyer_money < needed_money)
    return false;
  else
  {
   money += needed_money * store_share;
   users[buyer_idx].use_money(needed_money);
   return true;
  }
}

void Store::add_factor_goods(vector< vector<string> > buy_commands,
Factor& new_factor)
{
  for(int idx = 0 ; idx < buy_commands.size() ; idx++)
  {
    float good_price = goods[search_good_without_count(buy_commands[idx][0],
       buy_commands[idx][2])].get_price();
    Factor_Good new_factor_good(buy_commands[idx][0], atoi(buy_commands[idx][1].c_str()), good_price,
      buy_commands[idx][2]);
      new_factor.add_factor_good(new_factor_good);
  }
}

Factor Store::make_factor(string buyer_username, vector< vector<string> > buy_commands)
{
  User buyer_user = users[exist(buyer_username)];
  if(buyer_user.get_role() == "seller")
  {
    cout << FAIL_MESSAGE << endl;
  }
  else
  {
    Factor new_factor(buyer_user.get_first_name(), buyer_user.get_last_name(),
    buyer_user.get_username(), buyer_user.get_phone_number());
    add_factor_goods(buy_commands, new_factor);
    return new_factor;
  }
}


void Store::take_from_goods(vector< vector<string> > buy_commands)
{
  float profit = 0;
  for(int idx = 0 ; idx < buy_commands.size() ; idx++)
  {
    float store_share = STORE_SHARE/100.0;
    goods[search_good_by_sellerUN(buy_commands[idx][0],
    atoi(buy_commands[idx][1].c_str()),
    buy_commands[idx][2])].decreas_count(atoi(buy_commands[idx][1].c_str()));

    goods[search_good_by_sellerUN(buy_commands[idx][0],
    atoi(buy_commands[idx][1].c_str()),
    buy_commands[idx][2])].increment_sold_number();
  }
  money += profit;
}

void Store::sell(vector< vector<string> > buy_commands, string buyer_username)
{
  vector< vector<string> > merged_buy_commands = merge_buy_commands(buy_commands);
  if(exist(buyer_username) == -1 ||
  users[exist(buyer_username)].get_role() == "seller")
  {
    cout << FAIL_MESSAGE << endl;
    return;
  }
  if(!check_enough_good(merged_buy_commands) ||
  !check_enough_money(merged_buy_commands, buyer_username))
  {
    cout << FAIL_MESSAGE << endl;
    return;
  }
  take_from_goods(merged_buy_commands);
  Factor new_factor = make_factor(buyer_username, buy_commands);
  factors.push_back(new_factor);
  new_factor.print();
}

void Store::add_money_to_user(vector<string> input_data)
{
  string username = input_data[1];
  float added_money = atoi(input_data[2].c_str());
  users[exist(username)].add_money(added_money);
}

void Store::check_for_sales()
{
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_num_of_sale_requesters() >= REQUEST_FOR_SALE_LIMIT)
    {
      goods[iter].lower_price();
      goods[iter].make_on_sale();
    }
  }
}

void Store::check_for_offs()
{
  check_for_sales();
  check_best_sellers();
  check_number_of_good();
  check_special();
}

void Store::check_number_of_good()
{
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_count() >= GOODS_IN_STOCK_LIMIT)
    {
      if(!goods[iter].is_on_sale())
      {
        goods[iter].lower_price();
        goods[iter].make_on_sale();
      }
    }
  }
}

void Store::add_sale_request(vector<string> input_data)
{
  string buyer_username = input_data[1];
  if(exist(buyer_username) == -1 ||
  users[exist(buyer_username)].get_role() == "seller")
  {
    cout << FAIL_MESSAGE << endl;
    return;
  }
  string good_name = input_data[2];
  string seller_username = input_data[3];
  goods[search_good_without_count(good_name,
    seller_username)].add_to_sale_requesters(buyer_username);
}

void Store::check_best_sellers()
{
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_sold_number() >= BEST_SELLER_LIMIT)
      if(!goods[iter].is_on_sale())
      {
        goods[iter].lower_price();
        goods[iter].make_on_sale();
      }
  }
}

void Store::check_special()
{
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].is_special())
      if(!goods[iter].is_on_sale())
      {
        goods[iter].lower_price();
        goods[iter].make_on_sale();
      }
  }
}

void Store::add_special(vector<string> input_data)
{
  string seller_username = input_data[1];
  string good_name = input_data[2];
  int count = atoi(input_data[3].c_str());
  int good_index = search_good_without_count(good_name, seller_username);
  goods[good_index].make_special(count);
}

void Store::remove_special(vector<string> input_data)
{
  string seller_username = input_data[1];
  string good_name = input_data[2];
  int count = atoi(input_data[3].c_str());
  int good_index = search_good_without_count(good_name, seller_username);
  goods[good_index].remove_special();
}

void Store::add_request_goods(vector< vector<string> > request_commands,
  Request& new_request)
{
  for(int idx = 0 ; idx < request_commands.size() ; idx++)
  {
    Request_Good new_request_good(request_commands[idx][0],
    atoi(request_commands[idx][1].c_str()), request_commands[idx][2]);
    new_request.add_request_good(new_request_good);
  }
}

Request Store::make_request(string buyer_username,
vector< vector<string> > request_commands, string id)
{
  Request new_request(id, buyer_username);
  add_request_goods(request_commands, new_request);
  return new_request;
}


void Store::add_request(vector< vector<string> > request_commands,
string id, string buyer_username)
{
  if(exist(buyer_username) == -1 ||
  users[exist(buyer_username)].get_role() == "seller")
  {
    cout << FAIL_MESSAGE <<" 1" << endl;
    return;
  }
  Request new_request = make_request(buyer_username, request_commands, id);
  requests.push_back(new_request);
}

void Store::take_from_goods(Request request)
{
  vector<Request_Good> requested_goods = request.get_goods();

  for(int good_num = 0 ; good_num < requested_goods.size() ; good_num++)
  {
    goods[search_good_by_sellerUN(requested_goods[good_num].get_good_name(),
    requested_goods[good_num].get_good_count(),
    requested_goods[good_num].get_seller_username())]
    .decreas_count(requested_goods[good_num].get_good_count());

    goods[search_good_by_sellerUN(requested_goods[good_num].get_good_name(),
    requested_goods[good_num].get_good_count(),
    requested_goods[good_num].get_seller_username())]
    .increment_sold_number();
  }

}

void Store::answer_request(Request request)
{

}

void Store::check_requests()
{
  for(int idx = 0 ; idx < requests.size() ; idx++)
  {
    if(!requests[idx].get_active())
      continue;
    if(is_available(requests[idx]))
    {
      if(!check_enough_money(requests[idx]))
      {
        requests[idx].deactive();
        return;
      }
      else
        answer_request(requests[idx]);
        requests[idx].deactive();
    }
  }
}

bool Store::is_available(Request request)
{
  vector<Request_Good> requested_goods = request.get_goods();
  for(int good_num = 0 ; good_num < requested_goods.size() ; good_num++)
  {
    if(search_good_by_sellerUN(requested_goods[good_num].get_good_name(),
    requested_goods[good_num].get_good_count(),
    requested_goods[good_num].get_seller_username()) == -1)
    {
      return false;
    }
  }
  return true;
}

bool Store::check_enough_money(Request request)
{
  int buyer_idx = exist(request.get_buyer_username());
  float buyer_money = users[buyer_idx].get_money();
  vector<Request_Good> requested_goods = request.get_goods();
  float needed_money = 0;
  for(int good_num = 0 ; good_num < requested_goods.size() ; good_num++)
  {
    needed_money += goods[search_good_by_sellerUN(requested_goods[good_num].get_good_name(),
    requested_goods[good_num].get_good_count(),
    requested_goods[good_num].get_seller_username())].get_price();
  }
  //cout << needed_money << "  " << buyer_money << endl;
  if(buyer_money < needed_money)
    return false;
  else
  return true;
}

void Store::print_request(vector<string> input_data)
{
  string buyer_username = input_data[1];
  for(int idx = 0 ; idx < requests.size() ; idx++)
  {
    string id = requests[idx].get_id();
    cout << "Request #" << idx + 1 << " " << id << " " << buyer_username << endl;
    if(requests[idx].get_buyer_username() == buyer_username)
    requests[idx].print();
  }
}

void Store::print_factors(vector<string> input_data)
{
  string buyer_username = input_data[1];
  for(int idx = 0 ; idx < factors.size() ; idx++)
  {
    if(factors[idx].get_buyer_username() == buyer_username)
    {
      cout << "Factor " << idx + 1 << endl;
      vector<Factor_Good> goods = factors[idx].get_goods();
      int goods_sum = 0;
      for(int good_num = 0 ; good_num < goods.size() ; good_num++)
      {
        cout << good_num + 1 << "." << " ";
        int sum = goods[good_num].get_price() * goods[good_num].get_count();
        goods_sum += sum;
        cout << goods[good_num].get_name() << " " << goods[good_num].get_count() << " " <<
        goods[good_num].get_price() << " " << goods[good_num].get_seller_username() <<
        " " << sum << endl;
      }
      cout << "Goods_sum = " << goods_sum << endl;
      cout << "Total_sum = " << goods_sum * (1.0 + float(STORE_SHARE/100.0)) << endl << endl;
    }
  }
}

void Store::search_sale()
{
  vector<Good> sale_goods;
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_num_of_sale_requesters() >= REQUEST_FOR_SALE_LIMIT)
    {
      sale_goods.push_back(goods[iter]);
    }
  }
  print_goods(sale_goods);
}

void Store::search_bestseller()
{
  vector<Good> best_seller_goods;
  for(int iter = 0 ; iter < goods.size() ; iter++)
  {
    if(goods[iter].get_sold_number() >= BEST_SELLER_LIMIT)
      best_seller_goods.push_back(goods[iter]);
  }
  print_goods(best_seller_goods);
}
