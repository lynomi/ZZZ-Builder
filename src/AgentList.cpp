#include <QFile>
#include <QDebug>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "AgentList.h"
#include "Agent.h"
#include <iostream>
#include <vector>

AgentList::AgentList() {}

int AgentList::size() const {
    return list.size();
}

Agent AgentList::get(int i) const {
    return list[i];
}

std::vector<Agent>& AgentList::getList() {
    return list;
}

void AgentList::generateList() {
    qDebug() << "Loading agents";
    list.push_back(Agent('S',"Alice","Anomaly","Physical", 6));
    list.push_back(Agent('A',"Anby","Stun","Electric", 0));
    list.push_back(Agent('A',"Anton","Attack","Electric", 19));
    list.push_back(Agent('S',"Astra","Support","Ether", 0));
    list.push_back(Agent('A',"Ben","Defense","Fire", 0));
    list.push_back(Agent('A',"Billy","Attack","Physical", 15));
    list.push_back(Agent('S',"Burnice","Anomaly","Fire", 0));
    list.push_back(Agent('S',"Caesar","Defense","Physical", 0));
    list.push_back(Agent('A',"Corin","Attack","Physical", 16));
    list.push_back(Agent('S',"Ellen","Attack","Ice", 9));
    list.push_back(Agent('S',"Evelyn","Attack","Fire", 3));
    list.push_back(Agent('S',"Grace","Anomaly","Electric", 18));
    list.push_back(Agent('S',"Harumasa","Attack","Electric", 11));
    list.push_back(Agent('S',"Hugo","Attack","Ice", 8));
    list.push_back(Agent('S',"Jane Doe","Anomaly","Physical", 12));
    list.push_back(Agent('S',"Ju Fufu","Stun","Fire", 0));
    list.push_back(Agent('S',"Koleda","Stun","Fire", 0));
    list.push_back(Agent('S',"Lighter","Stun","Fire", 0));
    list.push_back(Agent('A',"Lucy","Support","Fire", 0));
    list.push_back(Agent('S',"Lycaon","Stun","Ice", 0));
    list.push_back(Agent('S',"Miyabi","Anomaly","Ice", 1));
    list.push_back(Agent('S',"Nekomata","Attack","Physical", 17));
    list.push_back(Agent('A',"Nicole","Support","Ether", 0));
    list.push_back(Agent('S',"Orphie", "Attack", "Fire", 0));
    list.push_back(Agent('A',"Pan Yinhu","Defense","Physical", 0));
    list.push_back(Agent('A',"Piper","Anomaly","Physical", 13));
    list.push_back(Agent('A',"Pulchra","Stun","Physical", 0));
    list.push_back(Agent('S',"Qingyi","Stun","Electric", 0));
    list.push_back(Agent('S',"Rina","Support","Electric", 0));
    list.push_back(Agent('S',"Seed","Attack","Electric", 5));
    list.push_back(Agent('A',"Seth","Defense","Physical", 0));
    list.push_back(Agent('S',"S0 Anby","Attack","Electric", 7));
    list.push_back(Agent('S',"Soldier 11","Attack","Fire", 14));
    list.push_back(Agent('A',"Soukaku","Support","Ice", 0));
    list.push_back(Agent('S',"Trigger","Stun","Electric", 0));
    list.push_back(Agent('S',"Vivian","Anomaly","Ether", 0));
    list.push_back(Agent('S',"Yanagi","Anomaly","Electric", 4));
    list.push_back(Agent('S',"Yixuan","Rupture","Ether", 2));
    list.push_back(Agent('S',"Yuzuha","Support","Physical", 0));
    list.push_back(Agent('S',"Zhu Yuan","Attack","Ether", 10));
}

std::vector<Agent> AgentList::generateTeams(int num_teams) const {
    std::vector<Agent> completed_teams;
    std::vector<Agent> selected_dps;

    // allows easy reference to Agent by their name
    std::unordered_map<std::string, Agent> name_to_agent;
    for (const Agent& ag : list) {
        name_to_agent[ag.getName()] = ag;
    }

    // adding all available dps agents to selected_dps
    for (const Agent& ag : list) {
        if (ag.getStatus() && ag.getID() > 0) {
            selected_dps.push_back(ag);
        }
    }

    // sort lowest to highest ID
    std::sort(selected_dps.begin(), selected_dps.end(), [](const Agent& a, const Agent& b) {
        return a.getID() < b.getID();
    });

    std::unordered_set<std::string> used_agents;
    int formed_teams = 0;

    // attempting to build team for each dps (starts from lower ID)
    for (const Agent& dps : selected_dps) {
        // stops when team requirement is met
        if (formed_teams >= num_teams) break;

        const std::string& dps_name = dps.getName();
        if (used_agents.count(dps_name)) continue;

        std::string file_path = "teams/" + dps_name;
        std::ifstream file(file_path);
        if (!file.is_open()) continue;

        std::string line;
        bool team_found = false;

        // searches through agent's team file
        while (std::getline(file, line) && !team_found) {
            std::stringstream ss(line);
            std::string name;
            std::vector<std::string> members;
            bool valid = true;

            while (std::getline(ss, name, ',')) {
                name.erase(0, name.find_first_not_of(" \t\r\n"));
                name.erase(name.find_last_not_of(" \t\r\n") + 1);

                auto it = name_to_agent.find(name);

                // checks availability of agents in team
                if (it == name_to_agent.end() || !it->second.getStatus() || used_agents.count(name)) {
                    valid = false;
                    break;
                }

                members.push_back(name);
            }

            if (valid && members.size() == 3) {
                for (const std::string& member_name : members) {
                    completed_teams.push_back(name_to_agent[member_name]);
                    used_agents.insert(member_name);
                }
                formed_teams++;
                team_found = true;
            }
        }

        file.close();
    }

    return completed_teams;
}

