#include <Device.h>

Device::Device(uint8_t pin, uint8_t type, String token) : DHT(pin, type) {
  _token = token;
  _base_url = TAGO_URL;
};

void Device::sendData(void) {
  String payload = _generate_payload();

  if(payload.isEmpty()) {
    Serial.println("Payload is empty.");
    return;
  }

  WiFiClient client;
  HTTPClient http;

  http.begin(client, _base_url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("device-token", _token);

  int httpCode = http.POST(payload);

  Serial.println("httpCode: " + httpCode);

  if (httpCode < 0) {
    Serial.println("Request error - " + httpCode);
    return;
  }

  if (httpCode != HTTP_CODE_OK) {
    Serial.println("Request error - " + httpCode);
    return;
  }

  String response = http.getString();

  http.end();

  Serial.println(response);
}

String Device::_generate_payload(void) {
  delay(2000); // minimum delay time to read DHT sensors

  float t = readTemperature();
  float h = readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "";
  }
  
  String payload;
  
  DynamicJsonDocument doc(256);

  JsonObject doc_0 = doc.createNestedObject();
  doc_0["variable"] = "humidity";
  doc_0["value"] = h;
  doc_0["unit"] = "%";

  JsonObject doc_1 = doc.createNestedObject();
  doc_1["variable"] = "temperature";
  doc_1["value"] = t;
  doc_1["unit"] = "C";

  serializeJson(doc, payload);

  return payload;
}