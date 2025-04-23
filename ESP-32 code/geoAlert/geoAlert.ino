#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SFE_BMP180.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Constants
#define ALTITUDE 1655.0 // Altitude for the location (e.g., Boulder, CO)
#define VIBRATION_PIN 18 // GPIO pin for the vibration sensor

// Wi-Fi & MQTT credentials
const char* ssid = "geoAlert";
const char* password = "geoalert";
const char* mqtt_server = "test.mosquitto.org"; // Public Mosquitto Broker
const char* clientId = "geo_alert_device_01";  // A unique identifier for your ESP32 device

// MQTT Topics
const char* topic_sensors = "geo_alert/sensors";

// Sensor objects
SFE_BMP180 barometer;
Adafruit_ADXL345_Unified accelerometer = Adafruit_ADXL345_Unified();

// Variables for sensor data
double temperature, pressure, relativePressure, altitude;
WiFiClient espClient;
PubSubClient client(espClient);

// Initialize sensors and WiFi
void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  connectWiFi();
  
  // Connect to MQTT broker
  client.setServer(mqtt_server, 1883); // Use Mosquitto's non-secure MQTT port
  
  // Initialize Sensors
  initSensors();
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop(); // Keeps MQTT client alive
  
  // Read and process sensor data
  double accelData[3]; // X, Y, Z
  bool isVibrationDetected = readVibrationSensor();
  readBarometerData();
  readAccelerometerData(accelData);

  // Display Data on Serial Monitor
  displaySensorData(accelData, isVibrationDetected);

  // Publish Data to MQTT broker
  publishData(accelData, isVibrationDetected);

  delay(2000); // Wait for 2 seconds before next iteration
}

void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void publishData(double* accelData, bool isVibrationDetected) {
  // Create JSON message for sensor data
  String message = "{\"accel_x\": " + String(accelData[0]) +
                   ", \"accel_y\": " + String(accelData[1]) +
                   ", \"accel_z\": " + String(accelData[2]) +
                   ", \"vibration\": \"" + (isVibrationDetected ? "YES" : "NO") + 
                   "\", \"temperature\": " + String(temperature) + 
                   ", \"pressure\": " + String(pressure) +
                   ", \"altitude\": " + String(altitude) + "}";
  
  // Publish sensor data to the unique topic
  client.publish(topic_sensors, message.c_str());
}

void initSensors() {
  // Initialize Barometer (BMP180)
  if (!barometer.begin()) {
    Serial.println("BMP180 not found");
    while (1); // Halt if sensor is not found
  }
  Serial.println("BMP180 Initialized");

  // Initialize Accelerometer (ADXL345)
  if (!accelerometer.begin()) {
    Serial.println("ADXL345 not found");
    while (1); // Halt if sensor is not found
  }
  Serial.println("ADXL345 Initialized");

  // Set vibration sensor pin as input
  pinMode(VIBRATION_PIN, INPUT);
}

bool readVibrationSensor() {
  return digitalRead(VIBRATION_PIN) == HIGH;
}

void readBarometerData() {
  // Start and read temperature and pressure from BMP180
  if (barometer.startTemperature() == 0) return;
  delay(barometer.startTemperature());

  if (barometer.getTemperature(temperature) == 0) return;

  if (barometer.startPressure(3) == 0) return;
  delay(barometer.startPressure(3));

  if (barometer.getPressure(pressure, temperature) == 0) return;

  // Calculate relative pressure and altitude
  relativePressure = barometer.sealevel(pressure, ALTITUDE);
  altitude = barometer.altitude(pressure, relativePressure);
}

void readAccelerometerData(double* accelData) {
  // Read Accelerometer (ADXL345) X, Y, Z data
  sensors_event_t event;
  accelerometer.getEvent(&event);

  accelData[0] = event.acceleration.x;
  accelData[1] = event.acceleration.y;
  accelData[2] = event.acceleration.z;
}

void displaySensorData(double* accelData, bool isVibrationDetected) {
  Serial.println("---------------------------------------------------------");
  Serial.println("Sensor Data:");
  
  // Display Accelerometer data (X, Y, Z)
  Serial.print("Accelerometer (X, Y, Z): ");
  Serial.print(accelData[0], 2);
  Serial.print(", ");
  Serial.print(accelData[1], 2);
  Serial.print(", ");
  Serial.println(accelData[2], 2);

  // Display Vibration status
  Serial.print("Vibration Detected: ");
  Serial.println(isVibrationDetected ? "Yes" : "No");

  // Display Barometer data
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" °C");
  
  Serial.print("Pressure: ");
  Serial.print(pressure, 2);
  Serial.println(" mb");
  
  Serial.print("Relative Pressure: ");
  Serial.print(relativePressure, 2);
  Serial.println(" mb");
  
  Serial.print("Computed Altitude: ");
  Serial.print(altitude, 0);
  Serial.println(" meters");
}
