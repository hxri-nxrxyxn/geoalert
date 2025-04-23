#include <Arduino.h>

// Uncomment one of these lines based on the board you're using
//#define USE_ESP32
#define USE_ESP8266
// #define USE_ARDUINO

#ifdef USE_ESP32
  #include <HardwareSerial.h>
  HardwareSerial LoRaSerial(2);
  #define LORA_RX 16  // ESP32 RX (Receives from LoRa TXD)
  #define LORA_TX 17  // ESP32 TX (Sends to LoRa RXD)
  #define LORA_RST 4  // Optional Reset Pin (ESP32)
#endif

#ifdef USE_ESP8266
  #include <SoftwareSerial.h>
  SoftwareSerial LoRaSerial(5, 4);  // RX = D1 (GPIO5), TX = D2 (GPIO4)
  #define LORA_RST 0  // Optional Reset Pin (ESP8266, GPIO0)
#endif

#ifdef USE_ARDUINO
  #include <SoftwareSerial.h>
  SoftwareSerial LoRaSerial(10, 11);  // RX = Pin 10, TX = Pin 11
  // Arduino does not always have an available GPIO for reset
#endif

void setup() {
  Serial.begin(74880);  // USB Serial Monitor

  #ifdef USE_ESP32
    LoRaSerial.begin(115200, SERIAL_8N1, LORA_RX, LORA_TX);
  #else
    LoRaSerial.begin(115200);
  #endif

  #ifdef LORA_RST
    pinMode(LORA_RST, OUTPUT);
    digitalWrite(LORA_RST, LOW);
    delay(100);
    digitalWrite(LORA_RST, HIGH);
    delay(500);
  #endif

  Serial.println("LoRa Configuration Bridge Active. Type AT commands:");

  // Ensure LoRa module is in AT mode
  LoRaSerial.print("AT+MODE=0\r\n");
  delay(500);
  LoRaSerial.print("AT\r\n");  // Check AT mode
}

void loop() {
  // Forward data from PC (USB) to LoRa module
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    LoRaSerial.print(cmd + "\r\n");  // Send with CRLF
  }

  // Forward any responses from LoRa module back to PC
  if (LoRaSerial.available()) {
    String response = LoRaSerial.readStringUntil('\n');
    Serial.println("LoRa: " + response);
  }
}
