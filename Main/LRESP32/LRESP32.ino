#include <Arduino.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// LoRa Module Configuration
#define LORA_RX 16  // GPIO16 (RX2) - LoRa RX
#define LORA_TX 17  // GPIO17 (TX2) - LoRa TX
#define LORA_RST 4  // Optional Reset Pin (ESP32)

HardwareSerial LoRaSerial(2);
String vibrationData, temperatureData, pressureData, altitudeData, accelXData, accelYData, accelZData;

// **WiFi & Firebase Credentials**
#define WIFI_SSID "geoAlert"  // Replace with your WiFi SSID
#define WIFI_PASSWORD "geoalert" // Replace with your WiFi password
#define FIREBASE_HOST "https://loraalert-72e69-default-rtdb.asia-southeast1.firebasedatabase.app"  // Firebase database URL
#define FIREBASE_SECRET "Mhj7vc6NtayZ5YVmZvlSFu59TYpCVB6D8YrQyN0n"  // Replace with your Firebase secret key

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// **Function to Send AT Commands**
void sendATCommand(String command) {
  Serial.print("Sending AT Command: [");
  Serial.print(command);
  Serial.println("]");

  LoRaSerial.print(command + "\r\n");  // Send command
  delay(500);

  while (LoRaSerial.available()) {
    String response = LoRaSerial.readStringUntil('\n');
    response.trim();
    Serial.println("LoRa Response: " + response);
  }
}

// **Connect to WiFi**
void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\n✅ Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// **Initialize Firebase**
void initFirebase() {
  Serial.println("Initializing Firebase...");
  
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_SECRET;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("✅ Firebase Initialized");
}

// **Send Data to Firebase**
void sendDataToFirebase(float accelX, float accelY, float accelZ, float temperature, float pressure, float altitude, String vibration) {
  Serial.println("Uploading data to Firebase...");

  Firebase.setFloat(fbdo, "/geo_alert/sensors/accel_x", accelX);
  Firebase.setFloat(fbdo, "/geo_alert/sensors/accel_y", accelY);
  Firebase.setFloat(fbdo, "/geo_alert/sensors/accel_z", accelZ);
  Firebase.setFloat(fbdo, "/geo_alert/sensors/temperature", temperature);
  Firebase.setFloat(fbdo, "/geo_alert/sensors/pressure", pressure);
  Firebase.setFloat(fbdo, "/geo_alert/sensors/altitude", altitude);
  Firebase.setString(fbdo, "/geo_alert/sensors/vibration", vibration);

  Serial.println("✅ Data uploaded successfully!");
}

void setup() {
  Serial.begin(115200);
  LoRaSerial.begin(115200, SERIAL_8N1, LORA_RX, LORA_TX);

  Serial.println("ESP32 LoRa Receiver Initializing...");

  // **Connect to WiFi**
  connectWiFi();
  initFirebase();

  // **Reset LoRa Module**
  pinMode(LORA_RST, OUTPUT);
  digitalWrite(LORA_RST, LOW);
  delay(100);
  digitalWrite(LORA_RST, HIGH);
  delay(500);

  // **Configure LoRa Module**
  sendATCommand("AT+MODE=0");          // Set to AT command mode
  sendATCommand("AT+ADDRESS=2");       // Set LoRa address for receiver
  sendATCommand("AT+NETWORKID=5");     // Set network ID
  sendATCommand("AT+BAND=865000000");  // Set frequency band
  sendATCommand("AT+PARAMETER=9,7,1,12"); // Set LoRa parameters

  Serial.println("ESP32 LoRa Receiver Ready. Listening for data...");
}

void loop() {
  if (LoRaSerial.available()) {
    String receivedData = LoRaSerial.readStringUntil('\n');
    receivedData.trim();

    Serial.print("Raw Received from LoRa: ");
    Serial.println(receivedData);

    // **Extract Data**
    int firstComma = receivedData.indexOf(',');
    int secondComma = receivedData.indexOf(',', firstComma + 1);
    int thirdComma = receivedData.indexOf(',', secondComma + 1);
    int fourthComma = receivedData.indexOf(',', thirdComma + 1);
    int fifthComma = receivedData.indexOf(',', fourthComma + 1);
    int sixthComma = receivedData.indexOf(',', fifthComma + 1);
    int seventhComma = receivedData.indexOf(',', sixthComma + 1);
    int eighthComma = receivedData.indexOf(',', seventhComma + 1);

    if (secondComma > 0 && thirdComma > 0 && fourthComma > 0 && fifthComma > 0 && sixthComma > 0 && seventhComma > 0 && eighthComma > 0) {
      vibrationData = receivedData.substring(secondComma + 1, thirdComma); // Vibration YES/NO
      temperatureData = receivedData.substring(thirdComma + 1, fourthComma);
      pressureData = receivedData.substring(fourthComma + 1, fifthComma);
      altitudeData = receivedData.substring(fifthComma + 1, sixthComma);
      accelXData = receivedData.substring(sixthComma + 1, seventhComma);
      accelYData = receivedData.substring(seventhComma + 1, eighthComma);
      accelZData = receivedData.substring(eighthComma + 1);

      // Convert values
      float accelX = accelXData.toFloat();
      float accelY = accelYData.toFloat();
      float accelZ = accelZData.toFloat();
      float temperature = temperatureData.toFloat();
      float pressure = pressureData.toFloat();
      float altitude = altitudeData.toFloat();

      // **Noise filtering: Remove values between 0 and -1 in X & Y**
      if (accelX > -1.0 && accelX < 0.0) accelX = 0.0;
      if (accelY > -1.0 && accelY < 0.0) accelY = 0.0;

      Serial.println("✅ Extracted Sensor Data:");
      Serial.println("Vibration: " + vibrationData);
      Serial.println("Temperature: " + temperatureData + " °C");
      Serial.println("Pressure: " + pressureData + " hPa");
      Serial.println("Altitude: " + altitudeData + " meters");
      Serial.print("Accelerometer X: "); Serial.println(accelX);
      Serial.print("Accelerometer Y: "); Serial.println(accelY);
      Serial.print("Accelerometer Z: "); Serial.println(accelZ);
      Serial.println("------------------------------------");

      // **Send data to Firebase**
      sendDataToFirebase(accelX, accelY, accelZ, temperature, pressure, altitude, vibrationData);
    } else {
      Serial.println("⚠️ Error: Incorrect LoRa data format!");
    }
  }
}
