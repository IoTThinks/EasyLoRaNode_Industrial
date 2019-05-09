#include "EasyLoRaIndustrialNode.h"

void setup() {  
  setupSerial();
  setupLED();  
  //setupButton();
  //setupWiFi();
  delay(1000);
  //setupOTA();
  setupLoRa();
  setupSensor();  
  setupActuator();
}

void loop() { 
  sendLoRaMessage(getSensor());  
  delay(2000);
  //String loraMsg = receiveLoRaMessage();
  //Serial.println("Received LoRa Message: " + loraMsg);

  //delay(500);
  //buttonPressed();
  //waitingForOTA();
}
