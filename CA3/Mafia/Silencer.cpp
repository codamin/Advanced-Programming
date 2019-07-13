#include "Silencer.h"
#include "Player.h"

Silencer::Silencer(string _name, string _role) :Player(_name, _role) {
    silenced_person = "NoOne";
}

void Silencer::action(Player* target) {
    target->be_silent();
}

string Silencer::answer() {
    if(! get_is_silenced()) {
        string answer = "Yes";
        return answer;
    }
}