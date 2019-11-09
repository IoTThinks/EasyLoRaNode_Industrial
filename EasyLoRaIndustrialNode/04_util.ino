// ====================================
// Util
// ====================================
// To get chip ID, ESP32 will return mac address
String getChipID()
{  
  // Get default mac address
  uint8_t chipid[6];
  esp_efuse_mac_get_default (chipid);

  // Format into uppercase mac address without :
  // Eg: BCDDC2C31684
  char returnStr[15];
  snprintf(returnStr, 15, "%02X%02X%02X%02X%02X%02X",chipid[0], chipid[1], chipid[2], 
            chipid[3], chipid[4], chipid[5]);
  return returnStr;
}

// To get chip ID, ESP32 will return last 3 octets of mac address
String getShortChipID()
{  
  // Get default mac address
  uint8_t chipid[6];
  esp_efuse_mac_get_default (chipid);

  // Format into uppercase mac address without :
  // Eg: BCDDC2C31684
  char returnStr[9];
  snprintf(returnStr, 9, "%02X%02X%02X", chipid[3], chipid[4], chipid[5]);
  return returnStr;
}

void printChipID()
{
  log("[UTIL] Chip ID: " + getChipID());
}

// Get random number from 0 to range
long getRandomNumber(int maxNum)
{
  randomSeed(analogRead(FREE_PIN3));
  return random(maxNum);  
}

// ====================================
// JSON
// ====================================
// Print json to string for printing
String jsonToString(StaticJsonDocument<200> doc)
{
  String output;
  serializeJson(doc, output);
  return output;
}

// Convert to Json Doc from string
StaticJsonDocument<200> toJsonDoc(const String& jsonStr)
{  
  //log("[UTIL] Parsing json string=" + jsonStr);
  
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, jsonStr);

  // Test if parsing succeeds.
  if (error) {
    log("[UTIL] Json parse failed.");
  }
    
  return doc;
}

// Get Json Attribute value
String getJsonAttValue(StaticJsonDocument<200> doc, const String& attNameLevel1, const String& attNameLevel2, 
                       const String& attNameLevel3)
{
  if(attNameLevel3 != "")
    doc[attNameLevel1][attNameLevel2][attNameLevel2];
  else if(attNameLevel2 != "")
    return doc[attNameLevel1][attNameLevel2];
  else
    return doc[attNameLevel1];
}

String removeJsonAtt(StaticJsonDocument<200> doc, const String& attName)
{
  doc.remove(attName);
  return jsonToString(doc);
}
