#ifndef MAFIA_FUNCTIONS_H
#define MAFIA_FUNCTIONS_H

using namespace std;
#include <vector>
#include <string>
#include "Game.h"


vector<string> split(string str , char c);
void read_commands(Game &game);
map<string, int> role_numbers(string line);
bool is_a_role(string role);
bool is_number(string s);
int random_generator(int i);

#endif //MAFIA_FUNCTIONS_H
