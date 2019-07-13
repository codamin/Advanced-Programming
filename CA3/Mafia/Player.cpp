#include <iostream>
#include "Player.h"
using namespace std;

Player::Player(string _name, string _role) {
    name = _name;
    role = _role;
    alive = 1;
    is_healed = 0;
    is_silenced = 0;
}


void Player::print_role() {

    cout<< role << endl;
}

void Player::be_healed() {

    is_healed = 1;
}

void Player::be_unhealed() {

    is_healed = 0;
}

void Player::be_silent() {

    is_silenced = 1;
}

void Player::be_unsilent() {
    is_silenced = 0;
}

void Player::die(string time) {

    if (! is_healed) {
        alive = false;
    }
    else
        is_healed = 0;
}
