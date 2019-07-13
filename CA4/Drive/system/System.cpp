#include <iostream>
#include <string>
#include <fstream>
#include "System.hpp"
#include "Tools.h"
#include "Group.h"
#include "Directory.h"

using namespace std;

System::System() {

    User* root_user = new User("root", "root", "superuser");
    users.push_back(root_user);
    Directory* _root_directory = new Directory("root");

    _root_directory->set_user_permission(root_user, "read,write");

    _root_directory->set_parent_directory(NULL);
    root = _root_directory;
    root_user->set_current_directory(root);

    Group* newGroup = new Group("root");
    groups.push_back(newGroup);
    newGroup->add_member(root_user);

}

Group* System::findGroup(string name) {

    for(int itr = 0; itr < groups.size(); itr ++)
        if(groups[itr]->get_name() == name)
            return groups[itr];
        return NULL;

}

User* System::findUser(string username) {

    for(int itr = 0; itr < users.size(); itr ++)
        if(users[itr]->get_username() == username)
            return users[itr];
        return NULL;
}

void System::add_group(string name) {

    if(findGroup(name) != NULL)
        throw runtime_error("This name has alraedy been taken");
    Group* newGroup = new Group(name);
    newGroup->add_member(current_user);
    groups.push_back(newGroup);
}


FileSystem* System::find_element(string path) {

    FileSystem* parent_element;
    FileSystem* found_element;
    if(path[0] == '/') {
        parent_element = root;
        found_element = parent_element;
        vector<string> parsed_path = Tools::split(path, '/');
        for (int itr = 0; itr < parsed_path.size(); itr ++) {
            found_element = parent_element->get_directory(parsed_path[itr]);
            parent_element = found_element;
        }
    }
    else {
        parent_element = current_user->get_current_directory();
        found_element = parent_element;
        vector<string> parsed_path = Tools::split(path, '/');
        for (int itr = 0; itr < parsed_path.size(); itr ++) {
            found_element = parent_element->get_directory(parsed_path[itr]);
            parent_element = found_element;
        }
    }
    if(found_element == NULL)
        throw runtime_error("path does not exist");
    return found_element;

}

Directory* System::add_user_home_directory(string new_directoryName, string sessionId) {

    Directory* new_directory = new Directory(new_directoryName);
    new_directory->set_parent_directory(root);
    new_directory->set_user_permission(onlineUsers[sessionId], "read,write");
    root->add_directory(new_directory);
    return new_directory;
}

Directory* System::add_directory(string new_directoryName, string sessionId) {

      if(onlineUsers[sessionId]->get_current_directory() != root &&
    ! find_element(get_element_path(sessionId))->has_write_permission(onlineUsers[sessionId]))
        throw runtime_error("this user can not write in this directory." + onlineUsers[sessionId]-> get_username() +
      onlineUsers[sessionId]->get_current_directory()->get_name());
    Directory* new_directory = new Directory(new_directoryName);
    new_directory->set_user_permission(onlineUsers[sessionId], "read,write");
    new_directory->set_group_permission(findGroup(onlineUsers[sessionId]->get_username()), "read,write");
    new_directory->set_parent_directory(onlineUsers[sessionId]->get_current_directory());
    new_directory->set_owner_user(onlineUsers[sessionId]);
    new_directory->set_owner_group(findGroup(onlineUsers[sessionId]->get_username()));
    onlineUsers[sessionId]->get_current_directory()->add_directory(new_directory);
    return new_directory;
}

void System::add_user(string username, string password, string sessionId) {

    if(onlineUsers[sessionId]->get_type() != "superuser")
        throw runtime_error("This user can not add user.");
    if(findUser(username) != NULL)
        throw runtime_error("This username has already been taken");

    User* newUser = new User(username, password, "normal");
    newUser->set_current_directory(root);
    Directory* home_directory = add_user_home_directory(username, sessionId);

    newUser->set_current_directory(home_directory);
    users.push_back(newUser);

    Group* newGroup = new Group(username);
    groups.push_back(newGroup);
    newGroup->add_member(newUser);

    home_directory->set_owner_user(newUser);
    home_directory->set_owner_group(newGroup);
    home_directory->set_user_permission(newUser, "read,write");
    home_directory->set_group_permission(newGroup, "read,write");

}

void System::login(string username, string password, string sessionId) {

    User* user = findUser(username);
    if(user == NULL)
        throw runtime_error("Username not found");
    else {
        if (user->get_password() == password) {

            if(username == "root")
                user->set_current_directory(root);
            else
                user->set_current_directory(find_element("/" + username));

            cout << "User successfully logged in " << endl;
            onlineUsers[sessionId] = user;
        }
        else
            throw runtime_error("wrong password");
    }

}

void System::copy(string source_name, string destination_name, string sessionId) {

    FileSystem* source_element = find_element(source_name);
    if(! find_element(get_element_path(sessionId))->has_read_permission(onlineUsers[sessionId]))
        throw runtime_error("this user can not read from source directory.");
    FileSystem* destination_element = find_element(destination_name);
    if(! destination_element->has_write_permission(onlineUsers[sessionId]))
        throw runtime_error("this user can not write in destination directory.");
    FileSystem* copied_element = source_element->get_copy();
    copied_element->set_owner_user(onlineUsers[sessionId]);
    destination_element->add_element(copied_element);
}

string System::get_parent_path(string child_path) {

    vector<string> parsed_path = Tools::split(child_path, '/');
    string parent_path = "";
    for(int itr = 0; itr < parsed_path.size()-1; itr++) {
        parent_path.append("/");
        parent_path.append(parsed_path[itr]);
    }
    if(parent_path == "")
        parent_path = "/";
    return parent_path;
}

void System::remove(string name) {

    FileSystem* source_element = find_element(name);
    FileSystem* source_parent_element = find_element(get_parent_path(name));
    source_parent_element->remove(source_element->get_name());
}

string System::get_element_path(string sessionId) {

    FileSystem* current_element = onlineUsers[sessionId]->get_current_directory();
    string path = "";
    if(current_element == root) {
        path = "/";
    }
    for(; current_element; current_element = current_element->get_parent_directory()) {
        if(current_element != root) {
            path.insert(0, current_element->get_name());
            path.insert(0, "/");
        }
    }
    return path;
}

void System::promote(string username) {

    User* user = findUser(username);
    user->be_promoted();
}

void System::demote(string username) {

  User* user = findUser(username);
  user->be_demoted();
}

void System::upload(string real_file_name, string file, string path, string sessionId) {

    FileSystem* new_file = new File(real_file_name);
    new_file->upload(file, file.size());
    new_file->set_user_permission(onlineUsers[sessionId], "read,write");
    new_file->set_group_permission(findGroup(onlineUsers[sessionId]->get_username()), "read,write");
    new_file->set_parent_directory(onlineUsers[sessionId]->get_current_directory());
    new_file->set_owner_user(onlineUsers[sessionId]);
    new_file->set_owner_group(findGroup(onlineUsers[sessionId]->get_username()));
    find_element(path)->add_file(new_file);
}

void System::download(string path, string output_name) {

    FileSystem* source_file = find_element(path);
    ofstream out;
    out.open(download_directory + "/" + output_name);
    source_file->download(out);
}

void System::logout(string sessionId) {

    onlineUsers[sessionId] = 0;
}
