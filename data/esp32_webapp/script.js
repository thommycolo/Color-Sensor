let colorInterval = null;

document.addEventListener('DOMContentLoaded', () => {
    initWifiConfig();
});

// --- FUNZIONI TAB ---
function openTab(tabName) {
    // 1. Aggiorna lo stato del contenitore per l'animazione del glider
    const tabsContainer = document.querySelector('.tabs');
    tabsContainer.setAttribute('data-active', tabName);

    // 2. Aggiorna classi bottoni (per il colore del testo)
    const buttons = document.querySelectorAll('.tab-btn');
    buttons.forEach(btn => btn.classList.remove('active'));
    
    if(tabName === 'config') {
        buttons[0].classList.add('active');
    } else {
        buttons[1].classList.add('active');
    }

    // 3. Mostra/Nascondi Contenuti
    document.getElementById('tab-config').style.display = (tabName === 'config') ? 'flex' : 'none';
    document.getElementById('tab-color').style.display = (tabName === 'color') ? 'flex' : 'none';

    // 4. Gestione Polling
    if (tabName === 'color') {
        startColorPolling();
    } else {
        stopColorPolling();
    }
}

// --- LOGICA COLORE LIVE ---
function startColorPolling() {
    fetchColorData();
    if (!colorInterval) {
        colorInterval = setInterval(fetchColorData, 1000);
    }
}

function stopColorPolling() {
    if (colorInterval) {
        clearInterval(colorInterval);
        colorInterval = null;
    }
}

function fetchColorData() {
    fetch('/api/Esp32_GetColor')
        .then(res => res.json())
        .then(data => {
            updateColorUI(data.r, data.g, data.b, data.name);
        })
        .catch(err => console.error("Errore lettura colore:", err));
}

function updateColorUI(r, g, b, name) {
    document.getElementById('val-r').innerText = r;
    document.getElementById('val-g').innerText = g;
    document.getElementById('val-b').innerText = b;
    document.getElementById('color-name').innerText = name;
    
    const box = document.getElementById('color-box');
    box.style.backgroundColor = `rgb(${r}, ${g}, ${b})`;
}

// --- LOGICA WIFI ---
function initWifiConfig() {
    const ssidInput = document.getElementById('ssid');
    const pswInput = document.getElementById('psw');
    const saveBtn = document.getElementById('saveBtn');
    
    fetch('/api/Esp32_GetConfig')
        .then(res => res.json())
        .then(data => {
            if(data.ssid_ext) ssidInput.value = data.ssid_ext;
            if(data.psw_ext) pswInput.value = data.psw_ext;
        })
        .catch(console.error);

    saveBtn.addEventListener('click', () => {
        const ssid = ssidInput.value.trim();
        const psw = pswInput.value.trim();
        if (!ssid) { alert("Inserisci SSID"); return; }

        saveBtn.disabled = true;
        showStatus("Tentativo di connessione...", "loading", true);

        fetch('/api/Esp32_SaveConfig', {
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify({ ssid_ext: ssid, psw_ext: psw })
        }).then(async (res) => {
            const data = await res.json();
            if (res.ok && data.status === 'connected') {
                showStatus(`✅ Connesso: ${data.ssid_ext}`, "success");
            } else {
                throw new Error(data.message || "Errore");
            }
        }).catch(err => {
            showStatus("❌ Errore Connessione", "error");
        }).finally(() => {
            saveBtn.disabled = false;
            document.getElementById('loader').style.display = 'none';
        });
    });
}

function showStatus(msg, type, loader=false) {
    const box = document.getElementById('status-box');
    box.className = `status-${type}`;
    box.classList.remove('hidden');
    document.getElementById('status-text').innerHTML = msg;
    document.getElementById('loader').style.display = loader ? 'block' : 'none';
}

function togglePassword() {
    const p = document.getElementById('psw');
    p.type = p.type === "password" ? "text" : "password";
}

window.openTab = openTab;