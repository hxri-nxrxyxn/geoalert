GeoAlert 🌍⚡
Real-time location-based alert system using ESP32, MQTT, and a Svelte-powered app.

Overview
GeoAlert is a smart alert system that combines ESP32 sensor data collection with an MQTT-based communication network. The project consists of:

A Svelte + Vite frontend for the user interface.
An ESP32 module for collecting sensor data.
MQTT communication to relay sensor data to the app in real time.
Project Structure
1. Svelte + Vite App
The front-end interface is built using Svelte with Vite, providing a fast and reactive user experience.

2. ESP32 Sensor Data & MQTT Communication
The ESP32 module:
✅ Collects sensor data (e.g., temperature, motion, GPS, etc.).
✅ Uses MQTT protocol to publish data to the cloud/server.
✅ Integrates with the Svelte frontend to display real-time updates.

Recommended IDE Setup
Arduino IDE and VS Code + Svelte.

Installation & Setup
For the Svelte App
Clone the repository:

git clone https://github.com/<repo-owner>/GeoAlert.git
cd GeoAlert
Install dependencies:
npm install

Start the development server:
npm run dev

For the ESP32 Module
Install the required Arduino libraries:
PubSubClient (for MQTT)
WiFiClient (for internet connectivity)
Flash the ESP32 with the provided firmware (esp32/geoalert.ino).
Configure your MQTT broker (e.g., Mosquitto or AWS IoT).
Why This Approach?
🚀 Fast & Reactive UI - Thanks to Svelte and Vite.
📡 Real-time Communication - Using MQTT for instant data transfer.
🔧 ESP32 Integration - Making it IoT-ready.

Contributors
ShahazadAbdulla - ESP32 & MQTT integration.
HariNarayanan - Svelte + Vite app development.
