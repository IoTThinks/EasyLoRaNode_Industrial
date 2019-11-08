// ====================================
// Lora
// https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md
// ====================================
// Status
String LORA_Status = "Not Initialized";
String LORA_Lastreceived_Msg ="--No data--";

// Setup Lora
void setupLoRa() {
  log("[LoRa] Setting up LoRa");
  
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RESET, LORA_DIO012);
  
  while (!LoRa.begin(LORA_FREQ)) {
    log("[LoRa] Starting LoRa failed!");    
    LORA_Status="FAILED";
    delay(1000);
  }

  LoRa.setSpreadingFactor(LORA_SF);
  LoRa.setCodingRate4(LORA_CR); //4/5
  LoRa.setSignalBandwidth(LORA_BW);
  LoRa.setPreambleLength(LORA_PREAMBLE_LENGTH);
  LoRa.enableCrc();
  
  LORA_Status = "OK";
}

String receiveLoRaMessage() {
  int packetSize = LoRa.parsePacket();
  if (packetSize == 0) return "";          // if there's no packet, return

  // read packet header bytes:
  /*
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
  */
  
  String incoming = "";                 // payload of packet

  while (LoRa.available()) {            // can't use readString() in callback, so
    incoming += (char)LoRa.read();      // add bytes one by one
  }

  /*
  if (incomingLength != incoming.length()) {   // check length for error
    log("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    log("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:   
  log("Received from: 0x" + String(sender, HEX));
  log("Sent to: 0x" + String(recipient, HEX));
  log("Message ID: " + String(incomingMsgId));
  log("Message length: " + String(incomingLength));
  log("Message: " + incoming);  
  log("RSSI: " + String(LoRa.packetRssi()));
  log("Snr: " + String(LoRa.packetSnr()));
  log();
  */

  LORA_Lastreceived_Msg = incoming;
  return incoming;
}

void sendLoRaMessage(String outgoing) {
  // If sending message from sensor is empty, ignore it.
  if(outgoing == "")
   return;

  // Adding DeviceID
  // Format: "src":"DeviceID","temp":30,"humid":80
  // Outgoing in format "temp":30,"humid":80
  // outgoing = "\"src\":\"" + getChipID() + "\"," + outgoing;
  outgoing = R"=====("src":")=====" +
             getChipID() +
             R"=====(",)=====" +
             outgoing;
    
  log("[LoRa]=> Sending packet: " + outgoing);

  // Start sending
  LoRa.beginPacket();                   // start packet
  /*
  msgCount++;                           // increment message ID
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  */
  
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it  
}
