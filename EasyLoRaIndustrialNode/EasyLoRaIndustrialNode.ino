#include "EasyLoRa.h"

void setup() {  
  setupSerial();
  //setupWiFi();
  setupSerialBT();
  setChipID();
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
  // xTaskCreatePinnedToCore(cronjobTask, "cronjobTask", 1024, NULL, tskIDLE_PRIORITY, NULL, 1);
  xTaskCreate(cronjobTask, "cronjobTask", 10240, NULL, CRONJOB_PRIORITY_UPDATESENSOR, NULL);
}

void loop() { 
  // Check heap mem
  logHeap();

  // Received LoRa message is processed in callback

  // Not in use
  // buttonPressed();
  // waitingForOTA();
  
  // Delay a bit for watch dog
  vTaskDelay(1);
}

void cronjobTask(void* pvParameters) {
  while(true)
  {
    runCronJobs();
    vTaskDelay(100);
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
