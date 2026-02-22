let colorInterval = null;

document.addEventListener('DOMContentLoaded', () => {
    // Avvia subito il monitoraggio
    startColorPolling();
});

function startColorPolling() {
    fetchColorData();
    // Aggiorna ogni 1000ms (1 secondo)
    if (!colorInterval) {
        colorInterval = setInterval(fetchColorData, 1000);
    }
}

function fetchColorData() {
    // Chiama la stessa API che usa l'altro sito
    fetch('/api/Esp32_GetColor')
        .then(res => res.json())
        .then(data => {
            updateColorUI(data.r, data.g, data.b, data.name);
        })
        .catch(err => console.error("Errore connessione ESP32:", err));
}

function updateColorUI(r, g, b, name) {
    document.getElementById('val-r').innerText = r;
    document.getElementById('val-g').innerText = g;
    document.getElementById('val-b').innerText = b;
    document.getElementById('color-name').innerText = name;
    
    const box = document.getElementById('color-box');
    box.style.backgroundColor = `rgb(${r}, ${g}, ${b})`;
}