#include <string>
#include "Group.h"
using namespace std;

Group::Group(string _name) {

    name = _name;
}

void Group::add_member(User *user) {

    users.push_back(user);
}

bool Group::has_member(std::string username) {

    for(int itr = 0; itr < users.size(); itr++) {
        if (users[itr]->get_username() == username)
            return true;
    }
    return false;

}
