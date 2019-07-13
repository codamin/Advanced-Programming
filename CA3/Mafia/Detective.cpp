#include <iostream>
#include "Detective.h"
#include "Room.h"
#include "Player.h"

using namespace std;

void Detective::action(Player* target) {
    cout << target->answer() << endl;
}

string Detective::answer() {
    if(! get_is_silenced()) {
        string answer = "NO";
        return answer;
    }
}
