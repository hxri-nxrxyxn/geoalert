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
