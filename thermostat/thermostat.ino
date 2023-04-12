#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "page.h"

const char* ssid = "TP-Link_58B0";  // SSID
const char* password = "31795777"; // пароль
// const char* ssid = "Galaxy S10+c6d1";  // SSID
// const char* password = "ojgq3484"; // пароль

const int relayPin = D0;
const int thermoPin = A0;
const int btnPin = D1;

double thermoValue = 0;
bool isOn = true;
int prevBtnState;
String inputValue = "554";

ESP8266WebServer server(80);

void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void handleValue() {
  thermoValue = analogRead(thermoPin);
  String value = String(thermoValue);

  server.send(200, "text/plane", value);
}

void handleThreshold() {
  if (server.arg("threshold_input") != ""){     
    inputValue = server.arg("threshold_input");    
  }
  server.send(200, "text/html", "<meta charset='UTF-8'>" "Запрос отправлен на ESP.<br><a href=\"/\">Назад </a>"); 
}

void setup() {
  Serial.begin(115200);
  // delay(100);
  pinMode(relayPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  digitalWrite(relayPin, LOW);     
  prevBtnState = digitalRead(btnPin);

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

  // server.on("/", handleOnConnect);
  server.on("/", handleRoot);
  server.on("/readValue", handleValue);
  server.on("/getThreshold", handleThreshold);
  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if(isOn) {
    if(thermoValue <= inputValue.toFloat()) {
      digitalWrite(relayPin, HIGH);
    } else if(thermoValue > inputValue.toFloat()) {
      digitalWrite(relayPin, LOW);
    }
  }

  int buttonState = digitalRead(btnPin);
  if(buttonState == LOW && prevBtnState == HIGH) {
    isOn = !isOn;
    digitalWrite(relayPin, isOn);
  }
  prevBtnState = buttonState;
}