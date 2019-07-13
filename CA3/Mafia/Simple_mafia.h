#ifndef MAFIA_SIMPLE_MAFIA_H
#define MAFIA_SIMPLE_MAFIA_H

#include "Player.h"

class Simple_mafia : public Player {

public:
    Simple_mafia(string _name, string _role) : Player(_name, _role) {};
    string answer();
    void action(Player* target);
private:

};


#endif //MAFIA_SIMPLE_MAFIA_H

