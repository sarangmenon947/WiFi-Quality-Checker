#include <ESP8266WiFi.h>

#define led1 D0
#define led2 D1
#define led3 D2

const char* ssid = "Tanest";
const char* password = "Tanest#sa23";

WiFiServer server(80);

String wifiQualityMessage;

void setup() {
  Serial.begin(115200);

  unsigned long startAttemptTime = millis();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - startAttemptTime > 20000) {
      Serial.println("\nFailed to connect.");
      return;
    }
  }

  unsigned long connectionTime = millis() - startAttemptTime;

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("Time taken: ");
  Serial.print(connectionTime);
  Serial.println(" ms");

  if (connectionTime <= 5000) {
    wifiQualityMessage = "Excellent signal";
    digitalWrite(led1, HIGH);
  } else if (connectionTime <= 10000) {
    wifiQualityMessage = "Good signal";
    digitalWrite(led2, HIGH);
  } else {
    wifiQualityMessage = "Poor signal";
    digitalWrite(led3, HIGH);
  }

  server.begin();
  Serial.println("Server started");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    response += "<!DOCTYPE HTML><html><body>";
    response += "<h1>ESP8266 Wi-Fi Connection Quality</h1>";
    response += "<p>Connection Status: ";
    response += wifiQualityMessage;
    response += "</p>";
    response += "</body></html>";

    client.print(response);
    delay(1);
    client.stop();
  }
}