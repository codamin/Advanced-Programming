#ifndef MAFIA_SILENCER_H
#define MAFIA_SILENCER_H

#include "Player.h"

class Silencer  : public Player {

public:
    Silencer(string _name, string _role);
    string answer();
    void action(Player* target);


private:
    string silenced_person;

};


#endif //MAFIA_SILENCER_H
