#include "EasyLoRa.h"

void setup() {  
  setupSerial();
  //setupWiFi();
  setChipID();
  setNetworkID();
  setupSerialBT();  
  setupLED();  
  //setupButton();  
      
  setupLoRa();
  setupSensor();  
  setupModbus();
  setupActuator();
  //setupOTA();
  
  // Blink all leds
  blinkAllLEDs();

  // Create background cron job task
  // Let it to run in core 0 for not realtime tasks
  xTaskCreatePinnedToCore(cronjobTask, "cronjobTask", 1024, NULL, CRONJOB_PRIORITY_UPDATESENSOR, NULL, 0);
}

void loop() { 
  // Check heap mem
  // logHeap();

  // Received LoRa message is processed in callback

  // Not in use
  // buttonPressed();
  // waitingForOTA();
  
  // Delay a bit for watch dog
  // vTaskDelay(1);
}

void cronjobTask(void* pvParameters) {
  while(true)
  {
    runCronJobs();
    vTaskDelay(100); // Can tolerate delay
  }
}

void runCronJobs()
{
  CRONJOB_CURRENT_MILLIS = millis();
  if (CRONJOB_CURRENT_MILLIS - CRONJOB_START_MILLIS >= CRONJOB_PERIOD)
  {
    log("[MAIN] Updating internal sensor data...");
    updateInternalSensorData();
    CRONJOB_START_MILLIS = CRONJOB_CURRENT_MILLIS;
  }
}
