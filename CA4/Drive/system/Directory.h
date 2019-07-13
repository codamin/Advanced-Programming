#ifndef DRIVE_DIRECTORY_H
#define DRIVE_DIRECTORY_H

#include <vector>
#include <string>
class Directory;
#include "FileSystem.h"
#include "File.h"


class Directory :public FileSystem {
public:
    Directory(std::string name);
    ~Directory();
    FileSystem* get_directory(std::string name);
    virtual void add_directory(Directory* new_directory);
    std::string get_type();
    void add_element(FileSystem*& new_element);
    virtual void remove(std::string child_name);
    virtual void print_elements_info();
    void upload(std::string buffer, int size);
    void download(std::ofstream& out);
    virtual int get_size();
    virtual void add_file(FileSystem*);

private:

};



#endif //DRIVE_DIRECTORY_H
