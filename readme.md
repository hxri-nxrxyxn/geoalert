# GeoAlert 🌍⚡

## **Real-time Location-Based Alert System Using ESP32, ESP8266, LoRa, Firebase, and a Svelte-Powered App**

---

## **🚀 Overview**
GeoAlert is a smart **IoT-based alert system** that combines **ESP32 & ESP8266 sensor data collection** with **LoRa communication** and **Firebase** for real-time monitoring. This project enables remote sensing and alert notifications using LoRa for long-range, low-power communication.

---

## **📌 Project Structure**

### **1️⃣ Svelte + Vite Frontend**
✅ Built using **Svelte & Vite** for a fast and reactive UI.
✅ Displays real-time sensor data from Firebase.
✅ Provides a seamless experience for users to monitor alerts.

### **2️⃣ ESP32 & ESP8266 Sensor Data with LoRa Communication**
✅ **ESP8266** collects **sensor data** and transmits it via **LoRa**.
✅ **ESP32** acts as the **LoRa receiver** and sends data to **Firebase**.
✅ Uses **LoRa RYLR998 module** with **AT commands** for configuration.
✅ Supports **vibration sensors, barometric pressure sensors, and accelerometers**.
✅ Stores and updates data in **Firebase Realtime Database**.

---

## **🛠️ Installation & Setup**

### **🔹 Setting Up the Svelte App**
1. **Clone the repository:**
   ```sh
   git clone https://github.com/<repo-owner>/GeoAlert.git
   cd GeoAlert
   ```
2. **Install dependencies:**
   ```sh
   npm install
   ```
3. **Start the development server:**
   ```sh
   npm run dev
   ```

### **🔹 Setting Up the ESP8266 (LoRa Sensor Node)**
1. **Connect sensors** (BMP180, ADXL345, vibration sensor) to ESP8266.
2. **Install required libraries:**
   - `Adafruit_Sensor`
   - `Adafruit_ADXL345_U`
   - `SFE_BMP180`
   - `SoftwareSerial`
   - `FirebaseESP8266`
3. **Flash ESP8266 with** `Main/LTESP8266`.
4. **Ensure LoRa is configured** using AT commands.
5. **ESP8266 transmits sensor data via LoRa**.

### **🔹 Setting Up the ESP32 (LoRa Gateway & Firebase Uploader)**
1. **Install required libraries:**
   - `WiFi`
   - `FirebaseESP32`
   - `Adafruit_Sensor`
   - `Adafruit_ADXL345_U`
   - `SFE_BMP180`
2. **Flash ESP32 with** `Main/LRESP32`.
3. **ESP32 receives LoRa data and updates Firebase**.

### **🔹 Setting Up LoRa Modules**
1. **Ensure proper connections**:
   - **ESP32 ↔ LoRa Module:** TX → RX, RX → TX
   - **ESP8266 ↔ LoRa Module:** TX → RX, RX → TX
2. **Use AT Commands** (from `Main/LoraConfig`) to configure LoRa:
   ```sh
   AT+MODE=0       # Set AT Mode
   AT+ADDRESS=1    # Set Device Address
   AT+NETWORKID=5  # Set Network ID
   AT+BAND=865000000  # Set Frequency Band
   AT+PARAMETER=9,7,1,12  # Set LoRa Parameters
   ```

---

## **⚙️ Why This Approach?**
🚀 **Long-Range Communication** - LoRa enables ultra-long-range wireless transmission.
📡 **Real-Time Monitoring** - Data is continuously updated in Firebase.
🔧 **IoT Integration** - ESP32 & ESP8266 make it scalable and efficient.
💡 **Low Power Consumption** - LoRa allows extended battery life.

---

## **👥 Contributors**
👨‍💻 **Shahazad Abdulla** - ESP32 & ESP8266 LoRa-Firebase Integration.  
🎨 **Hari Narayanan** - Svelte + Vite Web App Development.  

---

### **📢 Future Improvements**
- 🛰 **GPS Integration** for real-time geolocation.
- 🔔 **Push Notifications** for alerts in the web app.
- 📊 **Data Visualization** for better analytics.

---

### **✅ Ready to Contribute?**
Feel free to **fork, clone, and modify** the project!
```sh
git clone https://github.com/<repo-owner>/GeoAlert.git
```
🎯 **Pull requests are welcome!**

