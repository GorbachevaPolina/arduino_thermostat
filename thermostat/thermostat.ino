#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// const char* ssid = "TP-Link_58B0";  // SSID
// const char* password = "31795777"; // пароль
const char* ssid = "Galaxy S10+c6d1";  // SSID
const char* password = "ojgq3484"; // пароль

const int relayPin = D0;
const int thermoPin = A0;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);     

  //server connection
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  server.on("/", handleOnConnect);
  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleOnConnect() {
  server.send(200, "text/html", "hi"); 
}