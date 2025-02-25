#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <SFE_BMP180.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define LORA_RX 5   // D1 (GPIO5) - LoRa RX
#define LORA_TX 4   // D2 (GPIO4) - LoRa TX
#define LORA_RST 0  // Optional Reset Pin (GPIO0)

#define I2C_SDA 12  // D6 (GPIO12) - I2C SDA
#define I2C_SCL 13  // D7 (GPIO13) - I2C SCL

#define VIBRATION_PIN 14 // GPIO14 (D5) - Vibration sensor
#define ALTITUDE 1655.0  // Altitude for location

SoftwareSerial LoRaSerial(LORA_RX, LORA_TX);
SFE_BMP180 barometer;
Adafruit_ADXL345_Unified accelerometer = Adafruit_ADXL345_Unified();
bool vibrationDetected;
double temperature, pressure, relativePressure, altitude;
float accelX, accelY, accelZ;

void sendATCommand(String command) {
  Serial.print("Sending AT Command: [");
  Serial.print(command);
  Serial.println("]");

  LoRaSerial.print(command + "\r\n");  // Send command
  delay(500);

  while (LoRaSerial.available()) {
    String response = LoRaSerial.readStringUntil('\n');
    response.trim();

    Serial.print("LoRa Response: ");
    Serial.println(response);

    if (response.startsWith("+ERR")) {
      Serial.println("⚠️ ERROR: LoRa command failed! Check format.");
    }
  }
}

void setup() {
  Serial.begin(74880);
  LoRaSerial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);  // Use GPIO12 & GPIO13 for I2C

  Serial.println("ESP8266 LoRa Sensor Node Initializing...");

  pinMode(VIBRATION_PIN, INPUT);

  // Initialize Barometer
  if (!barometer.begin()) {
    Serial.println("ERROR: BMP180 sensor not found!");
    while (true) { delay(1000); }
  }

  // Initialize Accelerometer
  if (!accelerometer.begin()) {
    Serial.println("ERROR: ADXL345 sensor not found!");
    while (true) { delay(1000); }
  }

  // Reset LoRa module
  #ifdef LORA_RST
    pinMode(LORA_RST, OUTPUT);
    digitalWrite(LORA_RST, LOW);
    delay(100);
    digitalWrite(LORA_RST, HIGH);
    delay(500);
  #endif

  // Configure LoRa Module
  sendATCommand("AT+MODE=0");
  sendATCommand("AT+ADDRESS=1");
  sendATCommand("AT+NETWORKID=5");
  sendATCommand("AT+BAND=865000000");
  sendATCommand("AT+PARAMETER=9,7,1,12");

  Serial.println("ESP8266 Sensor Node Ready. Sending data...");
}

void loop() {
  vibrationDetected = digitalRead(VIBRATION_PIN) == HIGH;
  readBarometerData();
  readAccelerometerData();

  // Create CSV-style message
  String message = String(vibrationDetected ? "YES" : "NO") + "," +
                   String(temperature, 2) + "," +
                   String(pressure, 2) + "," +
                   String(altitude, 2) + "," +
                   String(accelX, 2) + "," +
                   String(accelY, 2) + "," +
                   String(accelZ, 2);

  int msgLength = message.length();

  Serial.println("Sending Data: " + message);
  sendATCommand("AT+SEND=2," + String(msgLength) + "," + message);
  
  delay(2000);
}

void readBarometerData() {
  if (barometer.startTemperature() == 0) return;
  delay(barometer.startTemperature());
  if (barometer.getTemperature(temperature) == 0) return;
  if (barometer.startPressure(3) == 0) return;
  delay(barometer.startPressure(3));
  if (barometer.getPressure(pressure, temperature) == 0) return;
  relativePressure = barometer.sealevel(pressure, ALTITUDE);
  altitude = barometer.altitude(pressure, relativePressure);
}

void readAccelerometerData() {
  sensors_event_t event;
  accelerometer.getEvent(&event);
  accelX = event.acceleration.x;
  accelY = event.acceleration.y;
  accelZ = event.acceleration.z;
}
