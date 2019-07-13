#include <iostream>
#include <string>
#include "Room.h"
#include <algorithm>
#include <cstdlib>
#include "functions.h"
#include "Detective.h"
#include "Doctor.h"
#include "Joker.h"
#include "Silencer.h"
#include "Godfather.h"
#include "RouinTan.h"
#include "Simple_mafia.h"
#include "Simple_villager.h"
using namespace std;

Room::Room(string _room_name) {
    day_number = 1;
    room_name = _room_name;
    is_finished = 0;
    night_votes_finished = false;
}

Room::~Room() {

    for(int itr = 0; itr < players.size(); itr ++)
        delete players[itr];
}

void Room::set_role_numbers(map<string, int> _role_numbers) {

    role_numbers = _role_numbers;
}

int Room::total_players() {

    int total_num_of_players = 0;
    map<string, int>::iterator itr;
    for(itr = role_numbers.begin() ; itr != role_numbers.end(); itr++)
    {
        if(itr->first != "Mafia" && itr->first != "Villager")
            total_num_of_players += itr-> second;
    }
    return total_num_of_players;
}


void Room::add_player_name(string line) {

    vector<string> parsed_line = split(line, ' ');
    if(player_names.size() + parsed_line.size()-1 > total_players()) {
        player_names.clear();
        throw runtime_error("many users");
    }
    else
        for(int itr = 0; itr < parsed_line.size() -1; itr ++)
        {
            string new_player_name = parsed_line[itr +1];
            if(find_player(new_player_name) != NULL)
                throw runtime_error("A player with this name already exists.");
            player_names.push_back(new_player_name);
        }
    if(player_names.size() == total_players())
        set_roles();

}

Player* Room::make_new_player(string role, string player_name) {

    if(role == "Detective"){
        Detective* new_Detective = new Detective(player_name, role);
        return new_Detective;
    }
    if(role == "Doctor"){
        Doctor* new_Doctor = new Doctor(player_name, role);
        return new_Doctor;
    }
    if(role == "Godfather"){
        Godfather* new_Godfather = new Godfather(player_name, role);
        return new_Godfather;
    }
    if(role == "Joker"){
        Joker* new_Joker = new Joker(player_name, role);
        return new_Joker;
    }
    if(role == "Silencer") {
        Silencer* new_Silencer = new Silencer(player_name, role);
        return new_Silencer;
    }
    if(role == "RouinTan") {
        RouinTan* new_RouinTan = new RouinTan(player_name, role);
        return new_RouinTan;
    }
    if(role == "Simple_villager") {
        Simple_villager* new_Simple_villager = new Simple_villager(player_name, role);
        return new_Simple_villager;
    }
    if(role == "Simple_mafia") {
        Simple_mafia* new_Simple_mafia = new Simple_mafia(player_name, role);
        return new_Simple_mafia;
    }
}

void Room::announce_roles() {

    for (int itr = 0; itr < players.size(); itr++)
    {
        if(players[itr] != NULL) {
            cout << players[itr]->get_name() << " is ";
            players[itr]->print_role();
        }
    }
}

void Room::clear() {

    vote.clear_votes();
    vote.clear_vote_counts();
    asked_detectives.clear();
    healed_doctors.clear();
    silenced_silencers.clear();
    to_be_killed_candidate.clear();
    killed_player_at_night.clear();
    night_votes_finished = false;
    new_silents.clear();
    for(int itr = 0; itr < players.size(); itr ++)
        players[itr]->be_unhealed();

}

void Room::print_night_events() {

    if(!killed_player_at_night.empty())
        cout<< "Killed : " << killed_player_at_night << endl;
    if(new_silents.size() > 0) {
        cout << "Silenced : ";
        sort(new_silents.begin(), new_silents.end());
        for (int itr = 0; itr < new_silents.size(); itr ++)
            cout << new_silents[itr] << endl;
    }
}

void Room::start_day() {
    check_victory();
    if(is_finished)
        return;
    time = "day";
    cout << "Day " << day_number << endl;
    if(day_number > 1)
        print_night_events();
    clear();
}

void Room::set_roles() {

    int player_number = 0;
    random_shuffle(player_names.begin(), player_names.end(), random_generator);
    map<string, int>::iterator itr;
    for (itr = role_numbers.begin(); itr != role_numbers.end(); itr ++) {
        if (itr->first != "Mafia" && itr->first != "Villager")
            for (int each_role_number = 0; each_role_number < (itr->second); each_role_number ++) {
                players.push_back(make_new_player(itr->first, player_names[player_number]));
                player_number ++;
            }
    }
    announce_roles();
    start_day();
}


bool Room::is_joined(string player_name) {

    for(int itr = 0; itr < player_names.size(); itr++) {
        if(players[itr]->get_name() == player_name)
            return true;
    }
    return false;
}

bool Room::is_alive(string player_name) {

    for(int itr = 0; itr < players.size(); itr++) {
        if(players[itr]->get_name() == player_name)
            if(players[itr]->is_alive())
                return true;
    }
    return false;
}


void Room::count_votes() {

    vote.count_votes();
}

int Room::mafia_counts() {
    int count = 0;
    for(int itr = 0; itr < players.size(); itr++) {
        if(is_mafia(players[itr]->get_name()))
            if(players[itr]-> is_alive())
                count ++;
    }
    return count;
}

int Room::villager_counts() {
    int count = 0;
    for(int itr = 0; itr < players.size(); itr++) {
        if(is_villager(players[itr]->get_name()))
            if(players[itr]-> is_alive())
                count ++;
    }
    return count;
}

void Room::check_vote_errors(string voter_name, string votee_name) {

    if (! is_joined(voter_name) || ! is_joined(votee_name))
        throw runtime_error("User not joined");

    else if (! is_alive(votee_name) || ! is_alive(voter_name))
        throw runtime_error("User already died");
    else if (time == "night") {
        if (! is_mafia(voter_name))
            throw runtime_error("This user can not vote");
    }
}

void Room::add_vote(string voter_name, string votee_name) {

    if (player_names.size() != total_players())
        throw runtime_error("Not enough players have joined yet!");

    check_vote_errors(voter_name, votee_name);

    if (find_player(voter_name)->get_is_silenced())
        throw runtime_error("This player is silent");

    vote.add_vote(voter_name, votee_name);

    if (time == "night" && vote.get_votes_size() == mafia_counts()) {
        night_votes_finished = true;
        kill_selected_player();
    }

}

string Room::max_voted() {
    return vote.max_voted();
}

void Room::reset_silents() {

    for(int itr = 0; itr < players.size(); itr ++)
        players[itr]->be_unsilent();
}

void Room::start_night() {
    reset_silents();
    time = "night";
    vote.clear_votes();
    vote.clear_vote_counts();
    cout << "Night " << day_number << endl;
    check_night_actions();
}

void Room::kill(string player_name) {

    for(int itr = 0; itr < players.size(); itr++) {
        if(players[itr]->get_name() == player_name) {
            if(time == "day") {
                if(find_player(player_name)->get_role() == "Joker") {
                    cout << "Do I like a guy with a plan?" << endl;
                    finish();
                    return;
                }
                players[itr]->die("day");
                cout << "Died " << player_name << endl;
                check_victory();
                if(is_finished)
                    return;
                start_night();
                break;
            }
            else if(time == "night") {
                cout << "Mafia try to kill " << player_name << endl;
                to_be_killed_candidate = player_name;
                check_night_actions();
                break;
            }
        }
    }
}

void Room::kill_selected_player() {
     count_votes();
     string selected_player = max_voted();
     kill(selected_player);
}

bool Room::is_mafia(string player_name) {
    for(int itr = 0; itr < players.size(); itr++) {
        if(players[itr]->get_name() == player_name) {
            if(players[itr]->get_role() == "Godfather" || players[itr]->get_role() == "Silencer" ||
            players[itr]->get_role() == "Simple_mafia")
              return true;
        }
    }
    return false;
}

bool Room::is_villager(string player_name) {
    for(int itr = 0; itr < players.size(); itr++) {
        if(players[itr]->get_name() == player_name) {
            if(players[itr]->get_role() == "Detective" || players[itr]->get_role() == "Doctor" ||
               players[itr]->get_role() == "Simple_villager" || players[itr]->get_role() == "RouinTan")
                return true;
        }
    }
    return false;
}

Player* Room::find_player(string name) {
    for(int itr = 0; itr < players.size(); itr++) {
        if(players[itr]->get_name() == name)
            return players[itr];
    }
    return NULL;
}


bool Room::has_already_asked(string detective_name) {

    for(int itr = 0; itr < asked_detectives.size(); itr++) {
        if(asked_detectives[itr] == detective_name)
            return true;
    }
    return false;
}

void Room::check_detect_errors(string detective_name, string suspect_name) {

    if(! is_joined(detective_name) ||
       ! is_joined(suspect_name))
        throw runtime_error("User not joined");
    else if(! is_alive(detective_name))
        throw runtime_error("User already died");
}

void Room::detect(string detective_name, string suspect_name) {

    check_detect_errors(detective_name, suspect_name);
    if(!night_votes_finished)
        throw runtime_error("Night votes have not finished yet.");
    if(! is_alive(suspect_name))
        throw runtime_error("Person is dead");
    if(has_already_asked(detective_name))
        throw runtime_error("Detective has already asked");
    Player* asker = find_player(detective_name);
    Player* suspect = find_player(suspect_name);
    if(asker->get_role() != "Detective")
        throw runtime_error("User can not ask");
    else {
        asker->action(suspect);
        asked_detectives.push_back(detective_name);
    }
    check_night_actions();
}

bool Room::has_already_healed(string doctor_name) {

    for(int itr = 0; itr < healed_doctors.size(); itr++)
    {
        if(healed_doctors[itr] == doctor_name)
            return true;
    }
    return false;
}

int Room::alive_role_number(string role) {
    int count = 0;
    for(int itr = 0; itr < players.size(); itr ++) {
        if(players[itr]-> is_alive() && players[itr]->get_role() == role)
            count++;
    }
    return count;
}

void Room::check_heal_errors(string doctor_name, string to_be_healed_name) {

    check_heal_errors(doctor_name, to_be_healed_name);
    if(! is_joined(doctor_name) ||
       ! is_joined(to_be_healed_name))
        throw runtime_error("User not joined");
    else if(! is_alive(doctor_name))
        throw runtime_error("User already died");
}

void Room::heal(string doctor_name, string to_be_healed_name) {

    check_heal_errors(doctor_name, to_be_healed_name);
    if(asked_detectives.size() < alive_role_number("Detective"))
        throw runtime_error("Not all Detectives have detected yet!");
    if(! is_alive(to_be_healed_name))
        throw runtime_error("Person is dead");
    if(has_already_healed(doctor_name))
        throw runtime_error("Doctor has already healed");
    Player* doctor = find_player(doctor_name);
    Player* to_be_healed = find_player(to_be_healed_name);
    if(doctor->get_role() != "Doctor")
        throw runtime_error("User can not heal");
    else {
        doctor->action(to_be_healed);
        healed_doctors.push_back(doctor_name);
    }
    check_night_actions();
}

bool Room::has_already_silenced(string silencer_name) {

    for(int itr = 0; itr < silenced_silencers.size(); itr++)
    {
        if(silenced_silencers[itr] == silencer_name)
            return true;
    }
    return false;
}


void Room::check_silence_errors(string silencer_name, string to_be_silenced_name) {

    if(! is_joined(silencer_name) ||
       ! is_joined(to_be_silenced_name))
        throw runtime_error("User not joined");
    else if(! is_alive(silencer_name))
        throw runtime_error("User already died");
}

void Room::silence(string silencer_name, string to_be_silenced_name) {

    check_silence_errors(silencer_name, to_be_silenced_name);
    if(healed_doctors.size() < alive_role_number("Doctor"))
        throw runtime_error("Not all Doctors have healed yet!");
    if(! is_alive(to_be_silenced_name))
        throw runtime_error("Person is dead");
    if(has_already_silenced(silencer_name))
        throw runtime_error("Silencer has already silenced");
    Player* silencer = find_player(silencer_name);
    Player* to_be_silenced = find_player(to_be_silenced_name);
    if(silencer->get_role() != "Silencer")
        throw runtime_error("User can not silence");
    else {
        silencer->action(to_be_silenced);
        silenced_silencers.push_back(silencer_name);
        new_silents.push_back(to_be_silenced_name);
    }
    check_night_actions();
}

void Room::check_night_actions() {
    if(night_votes_finished) {
        if (asked_detectives.size() == alive_role_number("Detective") &&
            healed_doctors.size() == alive_role_number("Doctor") &&
            silenced_silencers.size() == alive_role_number("Silencer")) {
            kill_at_night(to_be_killed_candidate);
            if (! find_player(to_be_killed_candidate)->is_alive())
                killed_player_at_night = to_be_killed_candidate;
            day_number ++;
            start_day();
        }
    }
}

void Room::kill_at_night(string player_name) {

    find_player(player_name)->die("night");
    check_victory();
}

void Room::get_state() {

    cout << "Mafia = " << mafia_counts() << endl;
    cout << "Villager = " << villager_counts() << endl;

}

void Room::check_victory() {
    if(villager_counts() <= mafia_counts()) {
        cout << "Loose!" << endl;
        finish();
    }
    else if(mafia_counts() == 0) {
        cout << "Victory!" << endl;
        finish();
    }
}