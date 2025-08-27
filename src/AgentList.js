import Agent from "./Agent";

class AgentList {
  constructor() {
    this.list = [];
  }

  size() {
    return this.list.length;
  }

  get(i) {
    return this.list[i];
  }

  getList() {
    return this.list;
  }

  generateList() {
    console.log("Loading agents");
    this.list.push(new Agent('S', "Alice", "Anomaly", "Physical", 6));
    this.list.push(new Agent('A', "Anby", "Stun", "Electric", 0));
    this.list.push(new Agent('A', "Anton", "Attack", "Electric", 21));
    this.list.push(new Agent('S', "Astra", "Support", "Ether", 0));
    this.list.push(new Agent('A', "Ben", "Defense", "Fire", 0));
    this.list.push(new Agent('A', "Billy", "Attack", "Physical", 17));
    this.list.push(new Agent('S', "Burnice", "Anomaly", "Fire", 0));
    this.list.push(new Agent('S',"Caesar","Defense","Physical", 0));
    this.list.push(new Agent('A',"Corin","Attack","Physical", 18));
    this.list.push(new Agent('S',"Ellen","Attack","Ice", 10));
    this.list.push(new Agent('S',"Evelyn","Attack","Fire", 3));
    this.list.push(new Agent('S',"Grace","Anomaly","Electric", 20));
    this.list.push(new Agent('S',"Harumasa","Attack","Electric", 12));
    this.list.push(new Agent('S',"Hugo","Attack","Ice", 9));
    this.list.push(new Agent('S',"Jane Doe","Anomaly","Physical", 13));
    this.list.push(new Agent('S',"Ju Fufu","Stun","Fire", 0));
    this.list.push(new Agent('S',"Koleda","Stun","Fire", 0));
    this.list.push(new Agent('S',"Lighter","Stun","Fire", 0));
    this.list.push(new Agent('S',"Lucia","Support","Ether", 0));
    this.list.push(new Agent('A',"Lucy","Support","Fire", 0));
    this.list.push(new Agent('S',"Lycaon","Stun","Ice", 0));
    this.list.push(new Agent('A',"Manato","Rupture","Fire", 0));
    this.list.push(new Agent('S',"Miyabi","Anomaly","Ice", 1));
    this.list.push(new Agent('S',"Nekomata","Attack","Physical", 19));
    this.list.push(new Agent('A',"Nicole","Support","Ether", 0));
    this.list.push(new Agent('S',"Orphie", "Attack", "Fire", 0));
    this.list.push(new Agent('A',"Pan Yinhu","Defense","Physical", 0));
    this.list.push(new Agent('A',"Piper","Anomaly","Physical", 15));
    this.list.push(new Agent('A',"Pulchra","Stun","Physical", 0));
    this.list.push(new Agent('S',"Qingyi","Stun","Electric", 0));
    this.list.push(new Agent('S',"Rina","Support","Electric", 0));
    this.list.push(new Agent('S',"Seed","Attack","Electric", 5));
    this.list.push(new Agent('A',"Seth","Defense","Physical", 0));
    this.list.push(new Agent('S',"S0 Anby","Attack","Electric", 8));
    this.list.push(new Agent('S',"Soldier 11","Attack","Fire", 16));
    this.list.push(new Agent('A',"Soukaku","Support","Ice", 0));
    this.list.push(new Agent('S',"Trigger","Stun","Electric", 0));
    this.list.push(new Agent('S',"Vivian","Anomaly","Ether", 0));
    this.list.push(new Agent('S',"Yanagi","Anomaly","Electric", 4));
    this.list.push(new Agent('S',"Yidhari","Rupture","Ice", 7));
    this.list.push(new Agent('S',"Yixuan","Rupture","Ether", 2));
    this.list.push(new Agent('S',"Yuzuha","Support","Physical", 0));
    this.list.push(new Agent('S',"Zhu Yuan","Attack","Ether", 11));
    console.log("Finished loading agents");
  }

  generateTeams(numTeams, teamData) {
    const completedTeams = [];
    const nameToAgent = {};
    this.list.forEach(a => nameToAgent[a.getName()] = a);

    // gets top numTeams dps agents
    let selectedDPS = this.list.filter(ag => ag.getStatus() && ag.getID() > 0);
    selectedDPS.sort((a, b) => a.getID() - b.getID());
    selectedDPS = selectedDPS.slice(0, numTeams);
    
    const usedAgents = new Set();

    for (const dps of selectedDPS) {
      const lines = teamData[dps.getName()] || [];
      let teamFormed = false;

      for (const line of lines) {
        if (teamFormed) break;

        const members = Array.isArray(line) ? line : line.split(",").map(n => n.trim());
        const valid = members.every(name => nameToAgent[name] && nameToAgent[name].getStatus() && !usedAgents.has(name));

        if (valid && members.length === 3) {
          members.forEach(name => {
            completedTeams.push(nameToAgent[name]);
            usedAgents.add(name);
          });
          teamFormed = true;
        }
      }

      // adds the agent if team cant be formed
      if (!teamFormed && !usedAgents.has(dps.getName())) {
        completedTeams.push(dps);
        usedAgents.add(dps.getName());
      }
    }

    return completedTeams;
  }
}

export default AgentList;