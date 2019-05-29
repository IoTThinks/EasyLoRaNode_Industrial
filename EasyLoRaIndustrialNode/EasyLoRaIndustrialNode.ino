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
  setupModbus();
  setupActuator();
  
  // Blink all leds
  blinkAllLEDs();
}

void loop() { 
  // Blink LED 1 for another loop
  onLED1();
  delay(500);
  offLED1();
  delay(500);
  
  // Send message from commodity sensor
  sendLoRaMessage(getSensor());  
  delay(1000);

  // Send message from modbus sensor
  sendLoRaMessage(getModbusSensor());
  delay(2000);
  
  //String loraMsg = receiveLoRaMessage();
  //Serial.println("Received LoRa Message: " + loraMsg);

  //delay(500);
  //buttonPressed();
  //waitingForOTA();
}
