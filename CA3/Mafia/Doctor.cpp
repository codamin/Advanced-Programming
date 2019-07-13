#include "Doctor.h"
#include "Player.h"


string Doctor::answer() {
    if(! get_is_silenced()) {
        string answer = "NO";
        return answer;
    }
}

void Doctor::action(Player *target) {

    target->be_healed();
}
