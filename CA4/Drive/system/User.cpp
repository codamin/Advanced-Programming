#include <iostream>
#include "User.h"
#include <string>
using namespace std;
User::User(std::string _username, std::string _password, string _type) {

    username = _username;
    password = _password;
    type = _type;
}

void User::set_current_directory(FileSystem* _current_directory) {

    current_directory = _current_directory;
}



void User::be_promoted() {

  if(type == "normal")
    type = "admin";
  else if(type == "admin")
    type = "superuser";
  else
    throw(runtime_error("superuser can not be promoted"));
}

void User::be_demoted() {

  if(type == "superuser")
    type = "admin";
  else if(type == "admin")
    type = "normal";
  else
    throw(runtime_error("normal user can not be demoted"));
}
