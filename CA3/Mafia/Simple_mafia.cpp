#include "Simple_mafia.h"
#include "Player.h"

void Simple_mafia::action(Player* target) {
}

string Simple_mafia::answer() {
    if(! get_is_silenced()) {
        string answer = "Yes";
        return answer;
    }
}