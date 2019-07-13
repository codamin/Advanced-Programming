#ifndef MAFIA_GODFATHER_H
#define MAFIA_GODFATHER_H


#include "Player.h"

class Godfather  : public Player {

public:
    Godfather(string _name, string _role) : Player(_name, _role) {};
    string answer();
    void action(Player* target);

private:

};


#endif //MAFIA_GODFATHER_H
