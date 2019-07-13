#include <iostream>
#include <vector>
#include <string>
#include "Tools.h"
using namespace std;

vector<string> Tools::split(string line, char c) {
    vector<string> splitted;
    string word = "";
    for(int iter = 0 ; iter < line.size() ; iter++)
    {
        if(line[iter] == c)
        {
            if(word != "")
                splitted.push_back(word);
            word = "";
        }
        else
        {
            word.push_back(line[iter]);
        }
    }
    if(word != "")
        splitted.push_back(word);
    return splitted;
}
