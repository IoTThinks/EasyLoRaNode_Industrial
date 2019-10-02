#include "EasyLoRaIndustrialNode.h"

void setup() {  
  setupSerial();
  setupWiFi();
  setupSerialBT();
  printChipID();
  setupLED();  
  //setupButton();  
      
  setupLoRa();
  setupSensor();  
  setupModbus();
  setupActuator();
  //setupOTA();
  
  // Blink all leds
  blinkAllLEDs();
}

void loop() { 
  // Blink LED 1 for another loop
  onLED1();
  delay(500);
  offLED1();
  delay(500);

  // Get sensor data
  String mb_temp = String("\"mb_temp\":") + getModbusSensor();
  String s_smk = String("\"s_smk\":") + getSensor();  
  delay(2000);
   
  // Send sensor data to gateway
  sendLoRaMessage(mb_temp + String(",") + s_smk);
  delay(1000);

  //delay(500);
  //buttonPressed();
  //waitingForOTA();
}
