//
// Created by amin on 12/20/18.
//

#include "Godfather.h"
#include "Player.h"

void Godfather::action(Player* target) {
}

string Godfather::answer() {
    if(! get_is_silenced()) {
        string answer = "NO";
        return answer;
    }
}