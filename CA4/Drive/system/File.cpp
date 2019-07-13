#include <string>
#include <fstream>
#include "File.h"
#include "Directory.h"
using namespace std;

File::File(string name) : FileSystem(name){

}

void File::add_directory(Directory* new_directory) {

}

string File::get_type() {
    string type = "File";
    return type;
}

void File::add_element(FileSystem*& new_element) {

    throw runtime_error("Destination is not a directory.");

}

void File::remove(std::string child_name) {

}

File::~File() {

}

void File::print_elements_info() {

    throw runtime_error("This path is not for a directory.");
}

void File::upload(string buffer, int _size) {

    data.contents = buffer;
    data.size = _size;
}

void File::download(ofstream& out) {

  out << data.contents;
  out.close();
}

void File::add_file(FileSystem* new_file) {

    throw runtime_error("this path does not belong to a directory.");
}
