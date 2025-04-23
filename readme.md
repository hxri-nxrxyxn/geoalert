# GeoAlert 🌍⚡🚨
## **Real-time Location-Based Alert & Earthquake Monitoring System**

## **🚀 Overview**

GeoAlert is a comprehensive system that combines **IoT sensor data collection** with a user-friendly **mobile application** to provide real-time alerts and monitoring. The initial phase focuses on an **ESP32 & ESP8266 sensor network** utilizing **LoRa communication** and **Firebase** for remote sensing. The subsequent development introduces a **Svelte and Capacitor-powered mobile app** for earthquake alerts and visualizing sensor statistics. This project aims to keep users informed and prepared with timely notifications and comprehensive insights from both custom sensor deployments and established networks.


## **📌 Project Structure**

This project comprises two main parts: the IoT sensor network and the mobile application.

### **1️⃣ Svelte + Vite Frontend (Web)**

✅ Built using **Svelte & Vite** for a fast and reactive UI.
<br>
✅ Displays real-time sensor data from Firebase (relevant to the initial IoT setup).
<br>
✅ Provides a seamless experience for users to monitor alerts from the LoRa network.

### **2️⃣ ESP32 & ESP8266 Sensor Data with LoRa Communication**

✅ **ESP8266** collects **sensor data** (vibration, barometric pressure, acceleration) and transmits it via **LoRa**.
<br>
✅ **ESP32** acts as the **LoRa receiver** and sends data to **Firebase Realtime Database**.
<br>
✅ Uses **LoRa RYLR998 module** with **AT commands** for configuration.
<br>
✅ Supports **vibration sensors, barometric pressure sensors, and accelerometers**.
<br>
✅ Stores and updates data in **Firebase Realtime Database**.

### **3️⃣ Svelte + Capacitor Mobile Application**

✅ Built with **Svelte** for a reactive and performant user interface. 📱
<br>
✅ Uses **Capacitor** for cross-platform deployment to iOS and Android. 🌐
<br>
✅ Provides **⚡ Real-Time Earthquake Alerts** based on seismic activity. 🔔
<br>
✅ Features **🗺️ Interactive Maps** to visualize earthquake locations and sensor distribution. 📍
<br>
✅ Displays **📈 Sensor Statistics** from established sensor networks, including health, activity levels, and historical data. 📊
<br>
✅ Offers **⚙️ Customizable Settings** for alert thresholds and notification preferences. 🛠️
<br>
✅ Includes **🔒 User Authentication** via Firebase Authentication. 🔑

-----

## **🛠️ Installation & Setup**

The setup process varies for the IoT sensor network and the mobile application.

### **🔹 Setting Up the Svelte Web App**

1.  **Clone the repository:**
    ```sh
    git clone [https://github.com/](https://github.com/)<repo-owner>/GeoAlert.git
    cd GeoAlert
    ```
2.  **Install dependencies:**
    ```sh
    npm install
    ```
3.  **Start the development server:**
    ```sh
    npm run dev
    ```

### **🔹 Setting Up the ESP8266 (LoRa Sensor Node)**

1.  **Connect sensors** (BMP180, ADXL345, vibration sensor) to ESP8266.
2.  **Install required libraries** in the Arduino IDE:
      - `Adafruit_Sensor`
      - `Adafruit_ADXL345_U`
      - `SFE_BMP180`
      - `SoftwareSerial`
      - `FirebaseESP8266`
3.  **Flash ESP8266 with** `Main/LTESP8266`.
4.  **Ensure LoRa is configured** using AT commands (see LoRa Setup).
5.  **ESP8266 transmits sensor data via LoRa**.

### **🔹 Setting Up the ESP32 (LoRa Gateway & Firebase Uploader)**

1.  **Install required libraries** in the Arduino IDE:
      - `WiFi`
      - `FirebaseESP32`
      - `Adafruit_Sensor`
      - `Adafruit_ADXL345_U`
      - `SFE_BMP180`
2.  **Flash ESP32 with** `Main/LRESP32`.
3.  **Configure WiFi and Firebase credentials** in the ESP32 code.
4.  **ESP32 receives LoRa data and updates Firebase**.

### **🔹 Setting Up LoRa Modules**

1.  **Ensure proper connections**:
      - **ESP32 ↔ LoRa Module:** TX → RX, RX → TX
      - **ESP8266 ↔ LoRa Module:** TX → RX, RX → TX
2.  **Use AT Commands** (from `Main/LoraConfig` or a serial terminal) to configure LoRa (example configuration):
    ```sh
    AT+MODE=0       # Set AT Mode
    AT+ADDRESS=1    # Set Device Address (for ESP8266 sensor node)
    AT+NETWORKID=5  # Set Network ID
    AT+BAND=865000000  # Set Frequency Band (e.g., 865 MHz for India)
    AT+PARAMETER=9,7,1,12  # Set LoRa Parameters (Spreading Factor, Coding Rate, etc.)

    AT+ADDRESS=2    # Set Device Address (for ESP32 gateway)
    AT+NETWORKID=5  # Ensure Network ID matches
    AT+BAND=865000000  # Ensure Frequency Band matches
    AT+PARAMETER=9,7,1,12  # Ensure LoRa Parameters match
    ```

### **🔹 Setting Up the Svelte Mobile App**

1.  **Prerequisites:**

      * Node.js and npm installed.
      * Firebase account and project set up.
      * Capacitor CLI installed (`npm install -g @capacitor/cli`).
      * Android Studio or Xcode (for building native apps).

2.  **Clone the Repository:**

    ```bash
    git clone [https://github.com/hxri-nxrxyxn/geoalert](https://github.com/hxri-nxrxyxn/geoalert)
    cd GeoAlert
    ```

3.  **Firebase Setup:**

      * Create a Firebase project and enable Realtime Database and Authentication.
      * Obtain your Firebase configuration details.
      * Replace the placeholder Firebase configuration in the `src/script.js` file with your own.

4.  **Frontend Setup (Svelte):**

      * Navigate to the `frontend` directory.
      * Run `npm install` to install dependencies.
      * Run `npm run dev` to start the development server (for web development).
      * Run `npm run build` to build the Svelte app for mobile deployment.

5.  **Capacitor Setup:**

      * In the `frontend` directory, run `npx cap init`.
      * Add platforms: `npx cap add android` or `npx cap add ios`.
      * Copy the built files to the Capacitor web directory: `npx cap copy`.
      * Open the native IDE: `npx cap open android` or `npx cap open ios`.

-----

## **⚙️ Why This Approach?**

🚀 **Long-Range Communication** - LoRa enables ultra-long-range wireless transmission for sensor data.
📡 **Real-Time Monitoring** - Sensor data is continuously updated in Firebase, and earthquake alerts are delivered promptly.
🔧 **IoT Integration** - ESP32 & ESP8266 provide a scalable and efficient platform for sensor data collection.
💡 **Low Power Consumption** - LoRa allows extended battery life for remote sensor nodes.
📱 **Cross-Platform Accessibility** - The mobile app built with Capacitor can be deployed on both iOS and Android.
📊 **Comprehensive Data Insights** - The app provides both real-time alerts and statistical data from various sensor sources.

-----

## **👥 Contributors**

👨‍💻 **Shahazad Abdulla** - ESP32 & ESP8266 LoRa-Firebase Integration.
🎨 **Hari Narayanan** - Svelte + Vite Web App and Svelte + Capacitor Mobile App Development.

-----

### **📢 Future Improvements**

  - 🛰 **GPS Integration** for real-time geolocation of sensor nodes and earthquake events.
  - 🔔 **Push Notifications** for alerts directly within the mobile app.
  - 📊 **Enhanced Data Visualization** for better analytics on both web and mobile platforms.
  - 🌍 **Integration of more diverse sensor data** and established earthquake monitoring networks.

-----

### **✅ Ready to Contribute?**

Feel free to **fork, clone, and modify** the project\!

```sh
git clone https://github.com/hxri-nxrxyxn/geoalert.git
```
