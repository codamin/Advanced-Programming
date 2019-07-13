//
// Created by amin on 12/20/18.
//

#include "Joker.h"
#include "Player.h"

void Joker::action(Player* target) {
}

string Joker::answer() {
    if(! get_is_silenced()) {
        string answer = "NO";
        return answer;
    }
}