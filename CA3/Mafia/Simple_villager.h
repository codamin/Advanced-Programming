#ifndef MAFIA_SIMPLE_VILLAGER_H
#define MAFIA_SIMPLE_VILLAGER_H


#include "Player.h"

class Simple_villager  : public Player {

public:
    Simple_villager(string _name, string _role) : Player(_name, _role) {};
    string answer();
    void action(Player* target);

private:

};


#endif //MAFIA_SIMPLE_VILLAGER_H

