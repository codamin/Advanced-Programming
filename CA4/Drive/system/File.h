#ifndef DRIVE_FILE_H
#define DRIVE_FILE_H

#include <string>
#include <map>
class File;
#include "FileSystem.h"
#include "Directory.h"


class File : public FileSystem {
public:
    File(std::string name);
    ~File();
    struct Data {
        std::string contents;
        int size;
    };
    virtual FileSystem* get_directory(std::string name) {};
    virtual void add_directory(Directory* new_directory);
    std::string get_type();
    void add_element(FileSystem*& new_element);
    void remove(std::string);
    virtual void print_elements_info();
    void upload(std::string buffer,int size);
    void download(std::ofstream& out);
    virtual int get_size() {return data.size;}
    virtual void add_file(FileSystem*);

private:
    File::Data data;
    std::map<std::string, std::string> permissions;

};

#endif //DRIVE_FILE_H
