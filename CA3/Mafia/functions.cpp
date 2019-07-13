#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <time.h>
#include "Game.h"
using namespace std;


vector<string> split(string str , char c) {
    vector<string> splitted;
    string word = "";
    for(int iter = 0 ; iter < str.size() ; iter++)
    {
        if(str[iter] == c)
        {
            splitted.push_back(word);
            word = "";
        }
        else
        {
            word.push_back(str[iter]);
        }
    }
    splitted.push_back(word);
    return splitted;
}

void read_commands(Game& game) {
    string line;
    while(getline(cin, line))
    {
        try {
            string command = split(line, ' ')[0];
            if (command == "Create_room")
                  game.create_room(line);
            else if (command == "Switch_room")
                  game.switch_room(line);
            else if (command == "Join")
                  game.join_player(line);
              else if(command == "Vote")
                  game.vote(line);
              else if(command == "End_vote")
                  game.end_vote();
              else if(command == "Detect")
                  game.detect(line);
              else if(command == "Heal")
                  game.heal(line);
              else if(command == "Silence")
                   game.silence(line);
              else if(command == "Get_room_state")
                  game.get_room_state();
            else
                throw runtime_error("Invalid command.");

        } catch(exception& error) {
                cerr << error.what() << endl;
        }
    }
}

bool is_a_role(string role) {
    string roles[10] = { "Detective", "Doctor", "RouinTan", "Godfather", "Silencer", "Joker", "Mafia", "Villager",
                        "Simple_mafia", "Simple_Villager"};
    for(int i = 0; i < 10 ; i++ )
    {
        if(roles[i] == role)
            return true;
    }
    return false;
}

bool is_number(string s)
{
    string::iterator it = s.begin();
    while(it != s.end() && isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

map<string , int> role_numbers(string line) {
    string roles[10] = { "Detective", "Doctor", "RouinTan", "Godfather", "Silencer", "Joker", "Mafia", "Villager",
                        "Simple_mafia", "Simple_villager"};
    map<string, int> role_numbers;
    for(int i = 0; i < 10; i++) {
        role_numbers.insert(make_pair(roles[i], 0));
    }
    vector<string> parsed_line = split(line, ' ');
    for(int i = 0; i <= parsed_line.size()/2 - 2; i++) {
        if(parsed_line[2*i + 2][0] != '-') {
            throw runtime_error("Invalid input format.");
        }
        if(! is_a_role(parsed_line[2*i + 2].substr(1)))
            throw runtime_error("Invalid role.");
        if(atoi(parsed_line[2*i + 3].c_str()) < 0 )
            throw runtime_error("Numbers must be positive.");
        if(!is_number(parsed_line[2*i + 3]))
            throw runtime_error("Invalid number.");
        role_numbers[parsed_line[2*i + 2].substr(1)] = atoi(parsed_line[2*i + 3].c_str());
    }
    int villagers_number = role_numbers["Detective"] + role_numbers["Doctor"] + role_numbers["RouinTan"];
    int mafias_number = role_numbers["Godfather"] + role_numbers["Silencer"];
    if(villagers_number > role_numbers["Villager"]
    || mafias_number > role_numbers["Mafia"])
        throw runtime_error("Invalid number of roles.");
    role_numbers["Simple_villager"] = role_numbers["Villager"] - villagers_number;
    role_numbers["Simple_mafia"] = role_numbers["Mafia"] - mafias_number;
    return role_numbers;
}

int random_generator(int i) {
    srand(time(NULL));
    return rand()%i;
}
