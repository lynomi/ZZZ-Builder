function AgentPanel({ agents, onToggle, onEnableRank }) {
  return (
    <>
      <h2>Choose your agents:</h2>

      {/* toggle all A ranks */}
      <button
        onClick={() => onEnableRank("A")}
        style={{ margin: "10px", 
        backgroundColor: "#800f2faf"
        }}>
        Enable all A ranks
      </button>

      {/* toggle all S ranks */}
      <button onClick={() => onEnableRank("S")}
        style={{ margin: "10px",
        backgroundColor: "#800f2faf"
         }}>
        Enable all S ranks
      </button>

      {/* agent grid */}
      <div
        style={{
          flex: 1,
          padding: "10px",
          display: "grid",
          gridTemplateColumns: "repeat(6, 80px)",
          gridAutoRows: "95px",
          gap: "10px",
          justifyContent: "center",
        }}
      >
        {agents.map(({ agent, selected }) => {
          const imagePath = `agents/${agent.getName()}.jpg`;

          return (
            <button
              key={agent.getName()}
              onClick={() => onToggle(agent)}
              style={{
                display: "flex",
                flexDirection: "column",
                alignItems: "center",
                justifyContent: "center",
                padding: "5px",
                border: "1px solid #ccc",
                borderRadius: "8px",
                cursor: "pointer",
                background: selected ? "#800f2f97" : "#0000002b" // on : off
              }}
            >
              <img
                src={imagePath}
                alt={agent.getName()}
                style={{
                  width: "60px",
                  height: "60px",
                  objectFit: "cover",
                  borderRadius: "6px",
                }}
              />
              <span style={{ fontSize: "10pt", marginTop: "5px" }}>
                {agent.getName()}
              </span>
            </button>
          );
        })}
      </div>
    </>
  );
}

export default AgentPanel;