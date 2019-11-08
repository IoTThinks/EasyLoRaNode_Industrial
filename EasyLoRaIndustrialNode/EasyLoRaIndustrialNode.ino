#include "EasyLoRaIndustrialNode.h"

void setup() {  
  setupSerial();
  //setupWiFi();
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
  // Check heap mem
  // log("esp_free_heap: " + String(esp_get_free_heap_size()) + 
  //    ", free_min_heap: " + String(esp_get_minimum_free_heap_size()));
  
  // Blink LED 1 for another loop
  onLED1();
  delay(500);
  offLED1();
  delay(500);

  // Get sensor data
  String mb_temp = R"=====("mb_temp":)=====" + getModbusSensor();
  //String s_smk = R"=====("s_smk":)=====" + getSensor();
  delay(2000);
   
  // Send sensor data to gateway
  //sendLoRaMessage(mb_temp + String(",") + s_smk);
  sendLoRaMessage(mb_temp);
  delay(1000);

  //delay(500);
  //buttonPressed();
  //waitingForOTA();
}
