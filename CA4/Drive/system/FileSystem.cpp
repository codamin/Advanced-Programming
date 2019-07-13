#include <iostream>
#include <vector>
#include "FileSystem.h"
#include "Directory.h"
#include "Group.h"

using namespace std;

FileSystem::FileSystem(std::string _name) {

    name = _name;
}

FileSystem* FileSystem::get_copy() {

    if(this->get_type() == "File") {
        FileSystem* new_file = new File(get_name());
        return new_file;
    }
    else {

        FileSystem* new_directory = new Directory(get_name());
        vector<FileSystem*> sub_directories_copy;
        for(int itr = 0; itr < get_sub_directories().size(); itr ++) {

            sub_directories_copy.push_back(get_sub_directories()[itr]->get_copy());
        }
        new_directory->set_sub_directories(sub_directories_copy);
        return new_directory;
    }
}

void FileSystem::set_parent_directory(FileSystem* parent) {

    parent_directory = parent;
}

void FileSystem::print_info() {

    string type =get_type() == "Directory" ? "dir" : "file";
    cout << type << " " << user_permissions[owner_user] << " " << group_permissions[owner_group];
    cout << " " << owner_user->get_username() << " " << owner_group->get_name() << " ";
    cout << parent_directory->get_name() << "/" << get_name() << endl;
}

void FileSystem::set_user_permission(User* user, string permission) {

    user_permissions[user] = permission;
}

void FileSystem::set_group_permission(Group* group, string permission) {

    group_permissions[group] = permission;
}

bool FileSystem::has_read_permission(User* user) {
    if(user_permissions[user] == "read,-" || user_permissions[user] == "read,write" )
        return true;
    else {
        map<Group *, string>::iterator itr;
        for (itr = group_permissions.begin(); itr != group_permissions.end(); itr ++) {
            if ((itr->first)->has_member(user->get_username())) {
                if (itr->second == "read,-" || itr->second == "read,write")
                    return true;
            }
        }
        return false;
    }
}

bool FileSystem::has_write_permission(User* user) {
    if(user_permissions[user] == "-,write" || user_permissions[user] == "read,write" )
        return true;
    else {
        map<Group *, string>::iterator itr;
        for (itr = group_permissions.begin(); itr != group_permissions.end(); itr ++) {
            if ((itr->first)->has_member(user->get_username())) {
                if (itr->second == "-,write" || itr->second == "read,write")
                    return true;
            }
        }
        return false;
    }
}

void FileSystem::change_owner_mode(std::string type, std::string difference, std::string mode) {

    if (type == "user") {
        if (difference == "+") {
            if (mode == "read") {
                if (user_permissions[owner_user] == "-,write")
                    user_permissions[owner_user] = "read,write";
            } else if (user_permissions[owner_user] == "read,-")
                user_permissions[owner_user] = "read,write";
        } else if (difference == "-") {
            if (mode == "read") {
                if (user_permissions[owner_user] == "read,write")
                    user_permissions[owner_user] = "-,write";
            } else if (user_permissions[owner_user] == "read,write")
                user_permissions[owner_user] = "read,-";
        }
    }
    if (type == "group") {
        if (difference == "+") {
            if (mode == "read") {
                if (group_permissions[owner_group] == "-,write")
                    group_permissions[owner_group] = "read,write";
            } else if (group_permissions[owner_group] == "read,-")
                group_permissions[owner_group] = "read,write";
        } else if (difference == "-") {
            if (mode == "read") {
                if (group_permissions[owner_group] == "read,write")
                    group_permissions[owner_group] = "-,write";
            } else if (group_permissions[owner_group] == "read,write")
                group_permissions[owner_group] = "read,-";
        }
    }
}

int FileSystem::get_size() {
}

string FileSystem::get_info() {
    string body = "";
    body += "<p>";
    body += "type";
    body += "</nbsp>:";
    body += "</nbsp>";
    body += get_type();
    body += "</p>";
    body += "<p>";
    body += "owner_user_permissions";
    body += "</nbsp>:</nbsp>";
    body +=  user_permissions[owner_user];
    body += "</p>";

    body += "<p>";
    body += "owner_group_permissions";
    body += "</nbsp>:</nbsp>";
    body +=  group_permissions[owner_group];
    body += "</p>";

    body += "<p>";
    body += "owner_user";
    body += "</nbsp>:</nbsp>";
    body +=  owner_user->get_username();
    body += "</p>";

    body += "<p>";
    body += "owner_group";
    body += "</nbsp>:</nbsp>";
    body += owner_group->get_name();
    body += "</p>";

    body += "<p>";
    body += "file_name";
    body += "</nbsp>:</nbsp>";
    body += parent_directory->get_name();
    body += "/";
    body += get_name();
    body += "</p>";
    return body;
  }
