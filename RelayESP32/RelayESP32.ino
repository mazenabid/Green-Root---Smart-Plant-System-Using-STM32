// Please make sure these are defined above your main code

#define BLYNK_TEMPLATE_ID "Change it with what you recive from blynk"
#define BLYNK_TEMPLATE_NAME "Change it with what you recive from blynk"
#define BLYNK_AUTH_TOKEN "Change it with what you recive from blynk"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <BlynkSimpleEsp32.h>

const char* ssid = "YOU RNETWORK NAME"; //Please make sure you change what's inside these " " To your actuall SSID
const char* password = "YOUR NETWORK PASSWORD"; //Please make sure you change what's inside these " " To your actuall PASSWORD

#define relay1 5 //We set the relay to be at pin 5 of the ESP32

WebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW); // Ensure the relay is off initially

  // This next part is a template that can be adjusted to use DHT11 or other sensors and display it on your local host... 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.begin();
  Serial.println("HTTP server started");
}

// Necessary Functionality for BLYNK
BLYNK_WRITE(V1) {
  int relayState = param.asInt();
  digitalWrite(relay1, relayState);
}

void loop() {
  Blynk.run();
  server.handleClient();
}
