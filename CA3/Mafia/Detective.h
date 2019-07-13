#ifndef MAFIA_DETECTIVE_H
#define MAFIA_DETECTIVE_H


#include "Player.h"

class Detective  : public Player {

public:
    Detective(string _name, string _role) : Player(_name, _role) {};
    string answer();
    void action(Player* target);
private:

};


#endif //MAFIA_DETECTIVE_H
