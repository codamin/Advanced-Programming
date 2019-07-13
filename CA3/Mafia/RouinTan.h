#ifndef MAFIA_ROUINTAN_H
#define MAFIA_ROUINTAN_H

#include "Player.h"

class RouinTan  : public Player {

public:
    RouinTan(string _name, string _role) : Player(_name, _role) {
        is_survived_before = 0;
    };
    string answer();
    void action(Player* target);
    virtual void die(string time);


private:
    bool is_survived_before;
};


#endif //MAFIA_ROUINTAN_H
