import { useState, useEffect } from "react";
import AgentPanel from "./AgentPanel";
import TeamsPanel from "./TeamsPanel";
import TopBar from "./TopBar";
import AgentList from "./AgentList";
import "./App.css";

function App() {
  const [agents, setAgents] = useState([]);
  const [agentList, setAgentList] = useState(null);

  useEffect(() => {
    const list = new AgentList();
    list.generateList();
    setAgentList(list);

    setAgents(
      list.getList().map(agent => ({
        agent,
        selected: false
      }))
    );
  }, []);

  // toggle 1 agent
  const toggleAgent = (agentObj) => {
    setAgents(prev =>
      prev.map(a =>
        a.agent === agentObj ? { ...a, selected: !a.selected } : a
      )
    );
  };

  // enable agents of a given rank
  const enableRank = (rank) => {
    setAgents(prev =>
      prev.map(a =>
        a.agent.getRank() === rank ? { ...a, selected: true } : a
      )
    );
  };

  return (
    <>
      <TopBar />
      <div className="team-creation">
        <div className="agent-panel">
          <AgentPanel
            agents={agents}
            onToggle={toggleAgent}
            onEnableRank={enableRank}
          />
        </div>
        <div className="teams-panel">
          <TeamsPanel
            agentList={agentList}
            selectedAgents={agents.filter(a => a.selected)}
          />
        </div>
      </div>
    </>
  );
}

export default App;
