// ====================================
// Lora
// https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md
// ====================================
// Status
String LORA_Status = "Not Initialized";

// Setup Lora
void setupLoRa() {
  log("[LoRa] Setting up LoRa");
  
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RESET, LORA_DIO012);

  // Set customed RX Channel information
  setRXChannel();
  
  while (!LoRa.begin(LORA_FREQ_BASE)) {
    log("[LoRa] Starting LoRa failed!");    
    LORA_Status="FAILED";
    delay(1000);
  }

  LoRa.setSpreadingFactor(LORA_SF);
  LoRa.setCodingRate4(LORA_CR); //4/5
  LoRa.setSignalBandwidth(LORA_BW);
  LoRa.setPreambleLength(LORA_PREAMBLE_LENGTH);
  LoRa.enableCrc();

  // Set continuous receive  
  LoRa.onReceive(onLoRa1ReceiveCallback);  
  LoRa_rxMode();
  
  LORA_Status = "OK";
}

// Divide Network ID to max number of channels to find RX Channel
void setRXChannel()
{
  // Set the RX channel
  int currentRXChannel = SYS_NetworkID % LORA_FREQ_NUM_CHANNELS + 1;

  // Set RX frequency
  LORA_FREQ_RX = LORA_FREQ_BASE + currentRXChannel * LORA_FREQ_STEPS;

  log("[LoRa] Current RX Channel: ", string2Char(String(currentRXChannel)),
      ", LORA_FREQ_RX: ", string2Char(String(LORA_FREQ_RX)));
}

void LoRa_rxMode(){
  log("[LoRa] Set RX mode");
  LoRa.enableInvertIQ();                // active invert I and Q signals
  LoRa.setFrequency(LORA_FREQ_RX);      // receive at custom frequency
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode(){
  log("[LoRa] Set TX mode");
  LoRa.idle();                          // set standby mode
  LoRa.setFrequency(LORA_FREQ_BASE);    // send at base frequency
  LoRa.disableInvertIQ();               // normal mode
}

// To send a single LoRa message
void sendLoRaMessage(const char* outgoing) {
  // Check heap mem
  logHeap();
  
  // If sending message from sensor is empty, ignore it.
  if(strlen(outgoing) == 0)
   return;

  // Adding DeviceID
  // Format: "src":"DeviceID","temp":30,"humid":80
  // Outgoing in format "temp":30,"humid":80
  char loRaMessage[256];
  strcpy(loRaMessage, R"=====("src":")=====");
  strcat(loRaMessage, SYS_ChipID);
  strcat(loRaMessage, R"=====(",)=====");
  strcat(loRaMessage, outgoing);
    
  // Start sending
  log("[LoRa]=> Sending packet: ", loRaMessage);
  LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet  
  LoRa.print(loRaMessage);              // add payload
  LoRa.endPacket();                     // finish packet and send it

  // Set back to receive mode
  LoRa_rxMode();                        // set rx mode
}

// Continuous LoRa receive
// TO DO: To filter not matched dst here for faster speed
void loRa1ReadTask(void* pvParameters) {
  int packetSize = *((int*)pvParameters);
  
  // To receive message using char* to avoid heap fragmentation
  char incoming[256];
  
  for (int i = 0; i < packetSize; i++) {
    incoming[i] = (char)LoRa.read();
  }

  // To terminate the string
  incoming[packetSize] = '\0';
  
  log("[LoRa] Receive message: ", incoming);
  processDownlinkMessage(incoming);

  // Cleanup task before exiting
  vTaskDelay(1);
  vTaskDelete(NULL);
}

// Call back to receive LoRa messages
void onLoRa1ReceiveCallback(int packetSize) {
  // Create a background task to process receive LoRa message
  // Let it to run in core 0 for not realtime tasks
  xTaskCreatePinnedToCore(loRa1ReadTask, "loRa1ReadTask", 10240, (void*)&packetSize, 
    CRONJOB_PRIORITY_READLORA, NULL, 0);
}
