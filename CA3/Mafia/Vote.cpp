
#include "Vote.h"
using namespace std;

void Vote::add_vote(std::string voter_name, std::string votee_name) {
    votes[voter_name] = votee_name;
}

string Vote::max_voted() {

    map<string, int>::iterator itr;
    map<string, int>::iterator max = vote_counts.begin();
    for(itr = vote_counts.begin(); itr != vote_counts.end(); itr++ ) {
        if (itr->second > max->second)
            max = itr;
    }

    return max->first;
}

void Vote::clear_votes() {

    votes.clear();
}

void Vote::clear_vote_counts() {

    vote_counts.clear();
}

void Vote::count_votes() {

    map<string, string>::iterator itr;
    for(itr = votes.begin(); itr != votes.end(); itr++ )
        vote_counts[itr ->second] ++;
}