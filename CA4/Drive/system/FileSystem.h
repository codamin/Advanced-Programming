#ifndef DRIVE_FILESYSTEM_H
#define DRIVE_FILESYSTEM_H


#include <string>
#include <vector>
#include <map>
class User;
class Group;

class Directory;
class FileSystem {

public:
    FileSystem(std::string name);
    virtual ~FileSystem() {
        for(int itr = 0; itr < sub_directories.size(); itr++) {
            delete sub_directories[itr];
        }
    };
    std::string get_name() {return name;}
    virtual std::string get_type() = 0;
    virtual FileSystem* get_directory(std::string name) = 0;
    virtual void add_directory(Directory*) = 0;
    std::vector<FileSystem*> get_sub_directories() {return sub_directories;}
    void set_sub_directories(std::vector<FileSystem*> _sub_directories) {sub_directories = _sub_directories;}
    FileSystem* get_copy();
    virtual void add_element(FileSystem*& new_element) = 0;
    virtual void remove(std::string child_name) = 0;
    void set_parent_directory(FileSystem*);
    FileSystem* get_parent_directory() { return  parent_directory;}
    virtual void print_elements_info() = 0;
    void print_info();
    void set_user_permission(User*, std::string permission);
    void set_group_permission(Group*, std::string permission);
    virtual void upload(std::string buffer, int size) = 0;
    virtual void download(std::ofstream& out) = 0;
    User* get_owner_user() {return owner_user;}
    bool has_read_permission(User*);
    bool has_write_permission(User*);
    void set_owner_user(User* user) {owner_user = user;}
    void set_owner_group(Group* group) {owner_group = group;}
    void change_owner_mode(std::string type, std::string difference, std::string mode);
    virtual int get_size() = 0;
    virtual void add_file(FileSystem*) = 0;
    std::string get_info();

protected:
    User* owner_user;
    Group* owner_group;
    std::string name;
    std::vector<FileSystem*> sub_directories;
    FileSystem* parent_directory;
    std::map<User*, std::string> user_permissions;
    std::map<Group*, std::string> group_permissions;
};


#endif //DRIVE_FILESYSTEM_H
