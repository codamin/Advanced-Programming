#ifndef DRIVE_GROUP_H
#define DRIVE_GROUP_H

#include <vector>
#include "User.h"
#include "FileSystem.h"

class Group {
public:
    Group(std::string name);
    void add_member(User* user);
    std::string get_name() {return name;}
    bool has_member(std::string username);
private:
    std::string name;
    std::string password;
    std::vector<User*> users;

};


#endif //DRIVE_GROUP_H
