#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "Store.h"
#include "Good.h"
using namespace std;

void print_vector(vector<string> v);
vector<string> split(string str, char c);
void read_inputs(Store& store);
void sort_goods(vector<Good> &goods);
vector<vector<string>> get_buy_commands(string line);
vector< vector<string> > merge_buy_commands(vector< vector<string> > buy_commands);
vector< vector<string> > get_request_commands(string line);
#endif
