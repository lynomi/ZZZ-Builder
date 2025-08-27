import { useState, useEffect } from "react";

function TeamsPanel({ agentList, selectedAgents }) {
  const [teamData, setTeamData] = useState(null);
  const [teams, setTeams] = useState([]);
  const [numTeams, setNumTeams] = useState(1);

  useEffect(() => {
    fetch("teamData.json")
      .then(res => res.json())
      .then(data => setTeamData(data))
      .catch(err => console.error("Failed to load teams:", err));
  }, []);

  const createTeams = () => {
    if (!agentList || !teamData) return;

    const selectedNames = selectedAgents.map(a => a.agent.getName());
    agentList.getList().forEach(agent => {
      agent.setStatus(selectedNames.includes(agent.getName()));
    });

    const generated = agentList.generateTeams(numTeams, teamData);
    setTeams(generated);
  };

  if (!teamData) return <div>Loading teams...</div>;

  const rows = [];
  for (let i = 0; i < numTeams; i++) {
    const slice = teams.slice(i * 3, i * 3 + 3);
    while (slice.length < 3) slice.push(null);
    rows.push(slice);
  }

  return (
    <div>
      <h2>Teams</h2>

      <div style={{ display: "flex", flexDirection: "column", alignItems: "center", gap: "10px", marginBottom: "20px" }}>
        <button
          onClick={createTeams}
          style={{
            backgroundColor: "#800f2faf",
            color: "#fff",
            padding: "8px 16px",
            borderRadius: "5px",
            cursor: "pointer",
            transition: "transform 0.1s",
          }}
          onMouseDown={e => e.currentTarget.style.transform = "scale(0.95)"}
          onMouseUp={e => e.currentTarget.style.transform = "scale(1)"}
          onMouseLeave={e => e.currentTarget.style.transform = "scale(1)"}
        >
          Create Teams
        </button>

        <div style={{ display: "flex", alignItems: "center", gap: "10px" }}>
          <input
            type="range"
            min="1"
            max="5"
            value={numTeams}
            onChange={e => setNumTeams(parseInt(e.target.value))}
          />
          <span>{numTeams} {numTeams === 1 ? "team" : "teams"}</span>
        </div>
      </div>

      <div style={{ display: "flex", flexDirection: "column", gap: "20px", alignItems: "center" }}>
        {rows.map((row, rowIndex) => (
          <div key={rowIndex} style={{ display: "flex", gap: "10px" }}>
            {row.map((agent, idx) => (
              <button
                key={idx}
                style={{
                  display: "flex",
                  flexDirection: "column",
                  alignItems: "center",
                  justifyContent: "center",
                  width: "80px",
                  height: "80px",
                  padding: "5px",
                  border: "1px solid #ccc",
                  borderRadius: "8px",
                  cursor: agent ? "pointer" : "default",
                  background: "#0000002b",
                  opacity: agent ? 1 : 0.3,
                  transition: "transform 0.1s",
                }}
              >
                {agent ? (
                  <img
                    src={`agents/${agent.getName()}.jpg`}
                    style={{
                      width: "60px",
                      height: "60px",
                      objectFit: "cover",
                      borderRadius: "6px",
                    }}
                  />
                ) : (
                  <div style={{ width: "60px", height: "60px" }}></div>
                )}
              </button>
            ))}
          </div>
        ))}
      </div>
    </div>
  );
}

export default TeamsPanel;