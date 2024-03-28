#define BLYNK_TEMPLATE_ID "TMPL27mVKUCvC"
#define BLYNK_TEMPLATE_NAME "RelayControl"
#define BLYNK_AUTH_TOKEN "R0MGJrTSRRcvzzsYPWWNtoDZycmbrR4M"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <BlynkSimpleEsp32.h>

const char* ssid = "SASKTEL02DU";
const char* password = "Mero1106Zoom";

#define relay1 5

WebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW); // Ensure the relay is off initially

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

BLYNK_WRITE(V1) {
  int relayState = param.asInt();
  digitalWrite(relay1, relayState);
}

void loop() {
  Blynk.run();
  server.handleClient();
}
