#include <string>
#include "Directory.h"
#include "File.h"
#include "FileSystem.h"
using namespace std;

Directory::Directory(string name) : FileSystem(name){

}

FileSystem* Directory::get_directory(string name) {

    for(int itr = 0; itr < sub_directories.size(); itr ++) {
        if(sub_directories[itr]->get_name() == name)
            return sub_directories[itr];
    }
    return NULL;
}


void Directory::add_directory(Directory* new_directory) {

    sub_directories.push_back(new_directory);
}

string Directory::get_type() {
    string type = "Directory";
    return type;

}

void Directory::add_element(FileSystem*& new_element) {

    this->sub_directories.push_back(new_element);
}

void Directory::remove(string child_name) {

    for (int itr = 0; itr < sub_directories.size(); itr ++) {

        if (sub_directories[itr]->get_name() == child_name)
            sub_directories.erase(sub_directories.begin() + itr);
    }
}

Directory::~Directory() {

    for(int itr = 0; itr < sub_directories.size(); itr++) {
        delete sub_directories[itr];
    }
}

void Directory::print_elements_info() {

    for(int itr = 0; itr < sub_directories.size(); itr++)
        sub_directories[itr]->print_info();
}

void Directory::upload(string buffer, int size) {

    throw runtime_error("this path does not belong to a file.");
}

void Directory::download(ofstream& out) {

    throw runtime_error("this is not a file");
}

int Directory::get_size() {

    int sum = 0;
    for(int itr = 0; itr < sub_directories.size(); itr++)
        sum += sub_directories[itr]->get_size();
    return sum;
}

void Directory::add_file(FileSystem* new_file) {

    sub_directories.push_back(new_file);

}
