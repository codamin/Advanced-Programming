#ifndef USER_H
#define USER_H
using namespace std;
class User
{
private:
  string first_name;
  string last_name;
  string username;
  string phone_number;
  string role;
  float money;
public:
  bool is_same(User other_user);
  void update_role();
  User(vector<string> input_data);
  string get_first_name(){ return first_name; }
  string get_last_name(){ return last_name; }
  string get_username(){ return username; }
  string get_phone_number(){ return phone_number; }
  string get_role(){ return role; }
  float get_money(){ return money; }
  void add_money(float added_money){money += added_money;}
  void use_money(float used_money){money -= used_money;}
  string set_first_name(string _first_name){ first_name = _first_name; }
  string set_last_name(string _last_name){ last_name = _last_name; }
  string set_username(string _username){ username = _username; }
  string set_phone_number(string _phone_number)
  { phone_number = _phone_number; }
  string set_role(string _role){ role = _role; }
  int set_money(int _money){ money = _money; }
  void print();
};
#endif
