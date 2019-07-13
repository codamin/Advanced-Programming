#include <fstream>
#include <cassert>
#include <iostream>
#include "System.hpp"
using namespace std;

int main(int argc, char** argv) {

    try {
    System system;
    if(argc == 1)
        throw runtime_error("please enter a path.");
    system.set_download_directory(argv[1]);
    cout << argv[1] << endl;
    system.get_commands();
    } catch(exception& error) {
        cerr << error.what() << endl;
    }
}
