// Should be in a another thread
// Format from gateway to node: "dst":"BCDDC2C31684","id":307,"method":"setP1","params":"false"
// Only process those with dst = ChipID
void processDownlinkMessage(const char* message)
{
  // Added { } to be a json
  char parsingMessage[128];
  strcpy(parsingMessage, "{");
  strcat(parsingMessage, message);
  strcat(parsingMessage, "}");
  
  // Parse message  
  StaticJsonDocument<200> doc = toJsonDoc(parsingMessage);
  if(doc.isNull())
  {
    log("[PROCESSOR] Invalid MQTT Format. Skip processing message.");
    return;
  }

  // Parse json
  String dst = getJsonAttValue(doc, "dst", "", "");

  if(dst != SYS_ChipID)
  {
    // Ignore messages of other nodes
    log("[PROCESSOR] Ignore message with dst: ", string2Char(dst));
    return;
  }
  else
  {
    log("[PROCESSOR] Correct destination. To process packet with dst: ", string2Char(dst));
  }
  
  // Parse the rest  
  String request_id = getJsonAttValue(doc, "id", "", "");
  String methodName = getJsonAttValue(doc, "method", "", "");
  String params = getJsonAttValue(doc, "params", "", "");
  // log("[PROCESSOR] dst = ", string2Char(dst));
  // log("[PROCESSOR] request_id = ", string2Char(request_id));
  // log("[PROCESSOR] methodName = ", string2Char(methodName));
  // log("[PROCESSOR] params = ", string2Char(params));
  
  // TODO: To handle all cases
  // To process downlink messages
  if(methodName == "setP2")
  {
    // setP2 to turn on power in P2
    if(params == "true")
    {
      onActuator();
    }
    else
    {
      offActuator();
    }
    
    // To send response back
    // logHeap();
    char* responseMessage = createUplinkMessage(request_id, "att", "\"p2\":" + params);
    sendLoRaMessage(responseMessage);
    free(responseMessage);
    // logHeap();
  }
  else if(methodName == "poll")
  {
    // "dst":"BCDDC2C31684","id":27,"method":"poll","params":"tmt"
    if(params == "tmt")
    {
      // Send internal sensor data back as telemetry data
      // logHeap();
      char* responseMessage = createUplinkMessage(request_id, "tmt", CRONJOB_SENSOR_DATA);
      sendLoRaMessage(responseMessage);  
      free(responseMessage); 
      // logHeap();   
    }
    else
    {
      log("[Processor] Unhandled downlink message: poll");
    }
  }
  else
  {
    log("[Processor] Unhandled downlink message");
  }
}

// To create uplink message to gateway
// "src":"Device C" is automatically added by sendLoRaMessage
// RPC response: "src":"Device C","id":251, act:"rpc", "data":{"success": true}
// Attribute response: "src":"Device C","id":251, "act":"att", "data":{"p1":"true","p2":"false"}
// Telemetry response: "src":"Device C","id":251, "act":"tmt", "data":{"temp":301,"humid":90}
char* createUplinkMessage(const String& id, const String& act, const String& data)
{
  char *returnStr = (char *) malloc (128);
  strcpy(returnStr, R"=====("id":)=====");
  strcat(returnStr, string2Char(id));
  strcat(returnStr, R"=====(,"act":")=====");
  strcat(returnStr, string2Char(act));
  strcat(returnStr, R"=====(","data":{)=====");
  strcat(returnStr, string2Char(data));
  strcat(returnStr, "}");
  return returnStr;
}

// TODO: TO optimize to char*
// Get sensor data as telemetry data
void updateInternalSensorData()
{
  // Reserved global string is free from heap fragmentation
  CRONJOB_SENSOR_DATA.reserve(128);
  CRONJOB_SENSOR_DATA = "\"mb_temp\":";
  CRONJOB_SENSOR_DATA += getModbusSensor();

  log("[PROCESSOR] Sensor data: ", string2Char(CRONJOB_SENSOR_DATA));
}
