#include <Arduino.h>
#include <Device.cpp>
#include <WiFiUtils.h>

Device device(D1, DHT22, DEVICE_TOKEN);

int period = 10 * 60 * 1000; // 10 minutes
unsigned long time_now = 0;
unsigned long last_time = 0;

void setup() {
  Serial.begin(9600);
  
  setupWiFi();

  device.begin();
}

void loop() {
  
  time_now = millis();

  if (time_now - last_time >= (unsigned long) period) {
    last_time = millis();
    device.sendData();
  }
}