function TopBar() {
    return (
        <div style={{
            position: 'fixed',
            top: 0,
            left: 0,
            width: '100%',
            height: '60px',
            backgroundColor: '#4a0c1ead',
            color: '#FFF0F3',
            display: 'flex',
            alignItems: 'center',
            padding: '0 170px',
            zIndex: 1000
        }}>

        <img
            src="app-icon.png"
            alt="App Icon"
            style={{
            height: "40px",
            width: "40px",
        }}
        />

        <h2 style={{ margin: 30 }}><strong>ZZZ Builder</strong></h2>

        <a 
            href="https://github.com/lynomi/ZZZ-Builder"
            target="_blank"
            rel="noopener noreferrer"
            style = {{
                position: "fixed",
                top: "10px",
                right: "20px"
            }}
        >
            <img 
                src="github-icon.svg" 
                alt="Description" 
                style={{ width: "40px", height: "40px", cursor: "pointer" }} 
            />
        </a>
        
        </div>

        
  );
}

export default TopBar;