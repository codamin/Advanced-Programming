#ifndef MAFIA_GAME_H
#define MAFIA_GAME_H

#include <string>
#include "Room.h"
using namespace std;

class Game
{
public:
    void create_room(string line);
    void switch_room(string line);
    void join_player(string line);
    int room_index(string room_name);
    void vote(string line);
    void check_vote_errors(string line);
    void end_vote();
    bool is_mafia(string player_name);
    void detect(string line);
    void check_detect_errors(string line);
    void heal(string line);
    void check_heal_errors(string line);
    void silence(string line);
    void check_silence_errors(string line);
    void get_room_state();
    void check_finished_game();

private:
    vector<Room> rooms;
    string current_room;
};

#endif //MAFIA_GAME_H
