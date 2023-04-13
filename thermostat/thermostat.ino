#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <math.h>
#include "page.h"
#include "response.h"

OneWire ds(D3);
DallasTemperature sensors(&ds);

DeviceAddress sensor1 = { 0x28, 0xFF, 0xC3, 0xF5, 0x67, 0x18, 0x03, 0x73 };
float readSensor1 = 0;
String readSensor1String = "";

const char* ssid = "TP-Link_58B0";  // SSID
const char* password = "31795777"; // пароль
// const char* ssid = "Galaxy S10+c6d1";  // SSID
// const char* password = "ojgq3484"; // пароль

const int relayPin = D0;
const int thermoPin = A0;
const int btnPin = D1;

int thermoValue = 0;
bool isOn = true;
int prevBtnState = 1;
String inputValue = "554";
bool isManuel = false;

ESP8266WebServer server(80);

float readDs18b20() {
  sensors.requestTemperatures();
  readSensor1 = sensors.getTempC(sensor1);
  //Serial.println(readSensor1);
  return readSensor1;
}

void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void handleValue() {
  thermoValue = floor(readDs18b20());
  String value = String(thermoValue);

  server.send(200, "text/plane", value);
}

void handleThreshold() {
  if (server.arg("threshold_input") != ""){     
    inputValue = server.arg("threshold_input");    
  }
  String resPage = RESPONSE_page;
  server.send(200, "text/html", resPage); 
}

void handleReadThreshold() {
  server.send(200, "text/plane", inputValue);
}

void handleToggleMode() {
  isManuel = !isManuel;
  if(isManuel) {
    server.send(200, "text/plane", "1");
  } else {
    server.send(200, "text/plane", "0");
  }
}

void setup() {
  Serial.begin(115200);
  sensors.begin();
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
  server.on("/readThreshold", handleReadThreshold);
  server.on("/toggleMode", handleToggleMode);
  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  // if(isOn) {
  //   if(thermoValue <= inputValue.toFloat()) {
  //     digitalWrite(relayPin, HIGH);
  //   } else if(thermoValue > inputValue.toFloat()) {
  //     digitalWrite(relayPin, LOW);
  //   }
  // }

  // int buttonState = digitalRead(btnPin);
  // if(buttonState == LOW && prevBtnState == HIGH) {
  //   isOn = !isOn;
  //   digitalWrite(relayPin, isOn);
  // }
  // prevBtnState = buttonState;
  if(isManuel) {
    int buttonState = digitalRead(btnPin);
    if(buttonState == LOW && prevBtnState == HIGH) {
      isOn = !isOn;
      digitalWrite(relayPin, isOn);
    }
    prevBtnState = buttonState;
  } else {
    if(thermoValue <= inputValue.toFloat()) {
      digitalWrite(relayPin, HIGH);
      isOn = true;
    } else if(thermoValue > inputValue.toFloat()) {
      digitalWrite(relayPin, LOW);
      isOn = false;
    }
  }
}