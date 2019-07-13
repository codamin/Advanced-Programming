#ifndef MAFIA_VOTE_H
#define MAFIA_VOTE_H
#include <map>
#include <string>
#include <map>

class Vote {
public:
    void add_vote(std::string voter_name, std::string votee_name);
    void count_votes();
    std::string max_voted();
    void clear_votes();
    void clear_vote_counts();
    int get_votes_size() { return votes.size();}
private:
    std::map<std::string, std::string> votes;
    std::map<std::string, int> vote_counts;
};

#endif //MAFIA_VOTE_H
