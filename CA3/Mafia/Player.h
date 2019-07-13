#ifndef MAFIA_PLAYER_H
#define MAFIA_PLAYER_H

using namespace std;
#include <string>

class Player {

public:
    Player(string name, string role);
    void print_role();
    string get_name() { return name;}
    bool is_alive() { return alive;}
    virtual void die(string time);
    string get_role() { return role;}
    virtual string answer() = 0;
    virtual void action(Player* target) = 0;
    void be_healed();
    void be_unhealed();
    void be_silent();
    bool get_is_silenced() { return is_silenced;}
    void be_unsilent();

protected:
    bool alive;
    bool is_healed;

private:
    string name;
    string role;
    bool is_silenced;

};


#endif //MAFIA_PLAYER_H
