//
// Created by amin on 12/20/18.
//

#ifndef MAFIA_DOCTOR_H
#define MAFIA_DOCTOR_H


#include "Player.h"

class Doctor  : public Player {

public:
    Doctor(string _name, string _role) : Player(_name, _role) {};
    string answer();
    void action(Player* target);

private:

};

#endif //MAFIA_DOCTOR_H
