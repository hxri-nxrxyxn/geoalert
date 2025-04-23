
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

=======
# 🚨 GeoAlert - Earthquake Alert & Sensor Monitoring App 🌐

## 🚀 Overview

GeoAlert is a mobile application built with Svelte, Capacitor, and Firebase, designed to provide real-time earthquake alerts and display statistical data from established sensor networks. 📊 Stay informed and prepared with timely notifications and comprehensive sensor insights. 📱

## 🛠️ Tech Stack

* **Frontend:** Svelte (for a reactive and performant user interface) 💻
* **Mobile Framework:** Capacitor (for cross-platform deployment to iOS and Android) 📱
* **Backend & Data:** Firebase (for real-time database, authentication, and cloud functions) 🔥

## ✨ Features

* **⚡ Real-Time Earthquake Alerts:** Receive instant notifications of seismic activity in your area. 🔔
* **🗺️ Interactive Maps:** Visualize earthquake locations and sensor distribution on an interactive map. 📍
* **📈 Sensor Statistics:** View detailed statistical data from established sensor networks, including sensor health, activity levels, and historical data. 📊
* **⚙️ Customizable Settings:** Configure alert thresholds and notification preferences to suit your needs. 🛠️
* **🔒 User Authentication:** Securely log in and manage your alert settings with Firebase Authentication. 🔑
* **📱 Cross-Platform Compatibility:** Deployable to both iOS and Android devices using Capacitor. 🌐

## ⚙️ Setup Instructions

1.  **Prerequisites:**
    * Node.js and npm installed.
    * Firebase account and project set up.
    * Capacitor CLI installed (`npm install -g @capacitor/cli`).
    * Android Studio or Xcode (for building native apps).
      
2.  **Clone the Repository:**
    ```bash
    git clone https://github.com/hxri-nxrxyxn/geoalert
    cd GeoAlert
    ```
  
3.  **Firebase Setup:**
    * Create a Firebase project and enable Realtime Database and Authentication.
    * Obtain your Firebase configuration details.
    * Replace the placeholder Firebase configuration in the `src/script.js` file with your own.
      
4.  **Frontend Setup (Svelte):**
    * Navigate to the `src` directory.
    * Run `npm install` to install dependencies.
    * Run `npm run dev` to start the development server.
      
5.  **Capacitor Setup:**
    * In the `frontend` directory, run `npx cap init`.
    * Add platforms: `npx cap add android` or `npx cap add ios`.
    * Build the Svelte app: `npm run build`.
    * Copy the built files to the Capacitor web directory: `npx cap copy`.
    * Open the native IDE: `npx cap open android` or `npx cap open ios`.
      

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues to suggest improvements or report bugs. 🐛

## 📜 License

This project is licensed under the MIT License. 📝

## 📧 Contact

For any questions or inquiries, please contact [me](hari@laddu.cc). 📬

