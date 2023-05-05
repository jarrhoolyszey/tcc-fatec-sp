#include "WiFiUtils.h"

void setupWiFi(void) {


  WiFi.begin(SSID, PASSWORD);
  
  WiFi.mode(WIFI_STA);
  
  Serial.print("Connecting to ");
  Serial.println(SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n");
  Serial.println("Connection established!");
  Serial.print("IP Address:\t");
  Serial.println(WiFi.localIP());
}