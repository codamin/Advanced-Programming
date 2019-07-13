using namespace std;
#include <vector>
#include <string>
#include <iostream>
class Game;
#include "functions.h"
#include "Room.h"
#include "Game.h"


void Game::create_room(string line) {
    vector<string> parsed_line = split(line, ' ');
    string room_name = parsed_line[1];
    if(room_index(room_name) != -1)
        throw runtime_error("Room name already exist.");
    Room new_room(room_name);
    role_numbers(line);
    new_room.set_role_numbers(role_numbers(line));
    rooms.push_back(new_room);
    current_room = room_name;

}

int Game::room_index(string room_name) {

    for(int itr = 0; itr < rooms.size(); itr++)
    {
        if(rooms[itr].get_name() == room_name)
            return itr;
    }

    return -1;
}


void Game::switch_room(string line) {

    vector<string> parsed_line = split(line, ' ');
    if(parsed_line.size() > 2)
        throw runtime_error("Invalid number of inputs.");
    string new_room_name = parsed_line[1];
    if(room_index(new_room_name) == -1)
        throw runtime_error("Invalid room name.");
    current_room = new_room_name;
}
void Game::check_finished_game() {

    if(rooms.empty())
        throw runtime_error("Invalid current room");
    if(rooms[room_index(current_room)].get_is_finished())
        throw runtime_error("The game in this room has already finished. Switch room or create an other.");
}

void Game::join_player(string line) {

    check_finished_game();
    rooms[room_index(current_room)].add_player_name(line);
}

bool Game::is_mafia(string player_name) {

    return rooms[room_index(current_room)].is_mafia(player_name);
}

void Game::vote(string line) {

    check_finished_game();
    vector<string> parsed_line = split(line, ' ');
        if(parsed_line.size() > 3)
            throw runtime_error("many inputs");
    string voter_name = parsed_line[1];
    string votee_name = parsed_line[2];
    rooms[room_index(current_room)].add_vote(voter_name, votee_name);
}

void Game::end_vote() {

    check_finished_game();
    rooms[room_index(current_room)].kill_selected_player();
}

void Game::detect(string line) {

    check_finished_game();
    vector<string> parsed_line = split(line, ' ');
    if(parsed_line.size() > 3)
        throw runtime_error("many inputs");
    string detective_name = parsed_line[1];
    string suspect_name = parsed_line[2];
    rooms[room_index(current_room)].detect(detective_name, suspect_name);
}

void Game::heal(string line) {

    check_finished_game();
    vector<string> parsed_line = split(line, ' ');
    if(parsed_line.size() > 3)
        throw runtime_error("many inputs");
    string doctor_name = parsed_line[1];
    string to_be_healed_name = parsed_line[2];
    rooms[room_index(current_room)].heal(doctor_name, to_be_healed_name);
}

void Game::silence(string line) {

    check_finished_game();
    vector<string> parsed_line = split(line, ' ');
    if(parsed_line.size() > 3)
        throw runtime_error("many inputs");
    string silencer_name = parsed_line[1];
    string to_be_silenced_name = parsed_line[2];
    rooms[room_index(current_room)].silence(silencer_name, to_be_silenced_name);
}

void Game::get_room_state() {
    rooms[room_index(current_room)].get_state();
}

