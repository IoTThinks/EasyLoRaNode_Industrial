// Should be in a another thread
// Format from gateway to node: "dst":"BCDDC2C31684","id":307,"method":"setP1","params":"false"
// Only process those with dst = ChipID
void processDownlinkMessage(String message)
{
  // Parse message
  // Added { } to be a json 
  StaticJsonDocument<200> doc = toJsonDoc("{" + message + "}");
  if(doc.isNull())
  {
    log("[PROCESSOR] Invalid MQTT Format. Skip processing message.");
    return;
  }

  // Parse json
  String dst = getJsonAttValue(doc, "dst", "", "");
  if(dst != getChipID())
  {
    // Ignore messages of other nodes
    log("[PROCESSOR] Ignore message with dst = " + dst);
    return;
  }
  else
  {
    log("[PROCESSOR] Correct destination. To process packet with dst = " + dst);
  }
    
  // Parse the rest  
  String request_id = getJsonAttValue(doc, "id", "", "");
  String methodName = getJsonAttValue(doc, "method", "", "");
  String params = getJsonAttValue(doc, "params", "", "");

  log("[PROCESSOR] dst = " + dst);
  log("[PROCESSOR] request_id = " + request_id);
  log("[PROCESSOR] methodName = " + methodName);
  log("[PROCESSOR] params = " + params);
  
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
    String responseMessage = createUplinkMessage(request_id, "att", "\"p2\":" + params);
    sendLoRaMessage(responseMessage);
  }
  else if(methodName == "poll")
  {
    // "dst":"BCDDC2C31684","id":27,"method":"poll","params":"tmt"
    if(params == "tmt")
    {
      // Send sensor data back as telemetry data
     String responseMessage = createUplinkMessage(request_id, "tmt", getNodeTelemetryData());
     sendLoRaMessage(responseMessage);      
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
String createUplinkMessage(String id, String act, String data)
{
  String returnStr((char *)0);
  returnStr.reserve(128);
  returnStr += R"=====("id":)=====";
  returnStr += id;
  returnStr += R"=====(,"act":")=====";
  returnStr += act;
  returnStr += R"=====(","data":{)=====";
  returnStr += data;
  returnStr += "}";
  return returnStr;
}

// Get sensor data as telemetry data
String getNodeTelemetryData()
{
  String mb_temp = String("\"mb_temp\":") + getModbusSensor();
  return mb_temp;
}
