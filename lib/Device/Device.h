#ifndef TAGO_DEVICE
#define TAGO_DEVICE

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Parametros Tago.io
#define DEVICE_TOKEN  "9ddf5850-1efb-48a2-87a6-a9514ef84f63"
#define TAGO_URL      "http://api.tago.io/data"

// Class definition
class Device : public DHT {
  public:
    Device(uint8_t pin, uint8_t type, String token);
    void sendData(void);
  
  private:
    String _token;
    String _base_url;

    String _generate_payload(void);
};

#endif