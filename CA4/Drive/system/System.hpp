#ifndef DRIVE_HOME_H
#define DRIVE_HOME_H

#include <vector>
#include <map>
#include "User.h"
#include "Group.h"
#include "File.h"
#include "Directory.h"
#include "FileSystem.h"

class System {

public:
     System();
     void set_download_directory(std::string path) {download_directory = path;}
     void get_commands();
     void add_user(std::string username, std::string password, std::string sessionId);
     User* findUser(std::string username);
     void login(std::string username, std::string password, std::string sessionId);
     void logout(std::string sessionId);
     void add_group(std::string line);
     Group* findGroup(std::string name);
     void add_to_group(std::string line);
     Directory* add_user_home_directory(std::string new_directoryName, std::string sessionId);
     Directory* add_directory(std::string new_directoryName, std::string sessionId);
     FileSystem* find_element(std::string path);
     void copy(std::string source_name, std::string destination_name, std::string sessionId);
     void remove(std::string path);
     void move(std::string line);
     std::string get_element_path();
     std::string get_element_path(std::string sessionId);
     std::string get_parent_path(std::string child_path);
     void print_directory();
     void change_directory(std::string line);
     void print_elem_info(std::string line);
     void promote(std::string username);
     void demote(std::string username);
     void print_user_list();
     void download(std::string paht, std::string output_name);
     void upload(std::string real_file_name, std::string file, std::string path, std::string sessionId);
     void change_mode(std::string line);
     void file_size(std::string line);
     void change_group(std::string line);
     void change_owner(std::string line);
     void storage();
     User* get_user(std::string sessionId) {return onlineUsers[sessionId];}
     std::vector<User*> get_users() {return users;}
     std::string get_downlaod_directory() {return download_directory;}

private:
    std::string download_directory;
    User* current_user;
    std::vector<User*> users;
    std::vector<Group*> groups;
    FileSystem* root;
    std::map<std::string, User*> onlineUsers;
};


#endif //DRIVE_HOME_H
