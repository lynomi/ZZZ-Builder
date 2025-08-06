#ifndef AGENT_LIST_H_
#define AGENT_LIST_H_
#include <vector>
#include "Agent.h"

class AgentList {
    private:
        std::vector<Agent> list;

    public:
        AgentList();

        // returns size of list
        int size() const;

        // returns the agent at index i
        Agent get(int i) const;
        
        // returns reference to the list
        std::vector<Agent>& getList();

        // adds every agent from the game into the list
        void generateList();

        // creates a list of agents with the finished teams
        // they are separated by every 3 agents in the list
        // 1st, 4th, 7th, etc. are the first agents in a team
        std::vector<Agent> generateTeams (int num_teams) const;
};
#endif