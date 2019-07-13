#ifndef MAFIA_ROOM_H
#define MAFIA_ROOM_H

#include <string>
#include <vector>
#include <map>
#include "Player.h"
#include "Vote.h"

using namespace std;

class Room {

public:
    Room(string room_name);
    void set_role_numbers(map<string, int> role_numbers);
    string get_name() { return room_name;}
    void add_player_name(string name);
    int total_players();
    void set_roles();
    Player* make_new_player(string role, string player_name);
    void announce_roles();
    void start_day();
    bool is_joined(string player_name);
    bool is_alive(string player_name);
    void check_vote_errors(string voter_name, string votee_name);
    void add_vote(string voter_name, string votee_name);
    void count_votes();
    string max_voted();
    void kill_selected_player();
    void kill(string player_name);
    void start_night();
    bool is_mafia(string player_name);
    bool is_villager(string player_name);
    int mafia_counts();
    int villager_counts();
    Player* find_player(string name);
    void check_detect_errors(string detective_name, string suspect_name);
    void detect(string detective_name, string suspect_name);
    bool has_already_asked(string detective_name);
    void check_heal_errors(string doctor_name, string to_be_healed_name);
    void heal(string doctor_name, string to_be_healed_name);
    bool has_already_healed(string doctor_name);
    void check_silence_errors(string silencer_name, string to_be_silenced_name);
    void silence(string silencer_name, string to_silenced);
    bool has_already_silenced(string silencer_name);
    void kill_at_night(string player_name);
    void clear();
    void print_night_events();
    void get_state();
    void check_victory();
    void reset_silents();
    void finish() { is_finished = true;}
    bool get_is_finished() {return is_finished;}
    int alive_role_number(string role);
    bool night_votes_finished;
    void check_night_actions();
    ~Room();

private:
    string room_name;
    vector<Player*> players;
    map<string, int> role_numbers;
    vector<string> player_names;
    string time;
    int day_number;
    vector<string> asked_detectives;
    vector<string> healed_doctors;
    vector<string> silenced_silencers;
    Vote vote;
    string killed_player_at_night;
    string to_be_killed_candidate;
    vector<string> new_silents;
    bool is_finished;


};

#endif //MAFIA_ROOM_H
