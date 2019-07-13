#include "Simple_villager.h"
#include "Player.h"

void Simple_villager::action(Player* target) {
}

string Simple_villager::answer() {
    if(! get_is_silenced()) {
        string answer = "NO";
        return answer;
    }
}