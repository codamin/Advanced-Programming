//
// Created by amin on 12/20/18.
//

#ifndef MAFIA_JOKER_H
#define MAFIA_JOKER_H

#include "Player.h"

class Joker  : public Player {

public:
    Joker(string _name, string _role) : Player(_name, _role) {};
    string answer();
    void action(Player* target);

private:

};


#endif //MAFIA_JOKER_H
