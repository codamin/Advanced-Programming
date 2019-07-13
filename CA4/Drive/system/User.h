#ifndef DRIVE_USER_H
#define DRIVE_USER_H

#include <string>
#include "Directory.h"

class User {
public:
    User(std::string username, std::string password, std::string type);
    std::string get_username() {return username;}
    std::string get_password() {return password;}
    virtual std::string get_type() {return type;}
    FileSystem* get_current_directory() { return current_directory;}
    void set_current_directory(FileSystem*);
    void be_promoted();
    void be_demoted();

private:
    std::string type;
    FileSystem* current_directory;
    std::string username;
    std::string password;
};


#endif
