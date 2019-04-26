#include "EasyLoRaIndustrialNode.h"

void setup() {  
  setupSerial();
  setupLED();  
  //setupButton();
  //setupWiFi();
  delay(1000);
  //setupOTA();
  setupLoRa();
}

void loop() { 
  sendLoRaMessage("Hello Easy LoRa Node");
  delay(1000);
  //String loraMsg = receiveLoRaMessage();
  //Serial.println("Received LoRa Message: " + loraMsg);
  
  //onLED_STATUS1();
  //onLED_STATUS2();
  //onLED_STATUS3();
  //onLED_STATUS4();
  //delay(500);
  //offLED_STATUS1();
  //offLED_STATUS2();
  //offLED_STATUS3();
  //offLED_STATUS4();
  //delay(500);
  //buttonPressed();
  //waitingForOTA();
}
