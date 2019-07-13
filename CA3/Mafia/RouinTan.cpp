#include "RouinTan.h"
#include "Player.h"
#include <iostream>

void RouinTan::action(Player* target) {}

string RouinTan::answer() {
    if(! get_is_silenced()) {
        string answer = "NO";
        return answer;
    }
}

void RouinTan::die(string time) {
    if(time == "night") {
        if (! is_survived_before) {
            is_survived_before = 1;
        } else if (! is_healed) {
            alive = 0;
        } else {
            is_healed = 0;
        }
    }

    else if(time == "day") {
        if (! is_healed) {
            alive = 0;
        } else
            is_healed = 0;
    }
}