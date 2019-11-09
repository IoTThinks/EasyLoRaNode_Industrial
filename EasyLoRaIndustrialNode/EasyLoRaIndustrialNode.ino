#include "EasyLoRa.h"

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

  // Receive and process LoRa message
  // To send back LoRa message if required
  receiveAndProcessLoRaMessage();

  //buttonPressed();
  //waitingForOTA();
}

void receiveAndProcessLoRaMessage()
{
  // For LoRa 1
  String message = receiveLoRaMessage();
  if(message != ""){   
    log("[MAIN] => Received message: " + message);
    processDownlinkMessage(message);
  }
}
