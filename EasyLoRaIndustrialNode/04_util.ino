// ====================================
// Chip ID
// ====================================
// To get chip ID, ESP32 will return mac address
void setChipID()
{
  // ========
  // Chip ID
  // ========
  // Get default mac address
  uint8_t chipid[6];
  esp_efuse_mac_get_default (chipid);

  // Format into uppercase mac address without :
  // Eg: BCDDC2C31684
  snprintf(SYS_ChipID, 15, "%02X%02X%02X%02X%02X%02X",chipid[0], chipid[1], chipid[2], 
            chipid[3], chipid[4], chipid[5]);

  log("[UTILS] ChipID: ", SYS_ChipID);

  // ========
  // Hostname
  // ========  
  strcpy(SYS_HostName, "ENI-");
  strcat(SYS_HostName, SYS_ChipID);
  log("[UTILS] Host Name: ", SYS_HostName);
}

// To get chip ID, ESP32 will return last 3 octets of mac address
void setNetworkID()
{  
  // Get default mac address
  uint8_t chipid[6];
  esp_efuse_mac_get_default (chipid);

  // Format into uppercase mac address without :
  // Eg: BCDDC2C31684
  SYS_NetworkID = chipid[5];
  log("[UTILS] Network ID: ", string2Char(String(SYS_NetworkID)));
}

void printChipID()
{
  log("[UTIL] Chip ID: ", SYS_ChipID);
}

// Get random number from 0 to range
long getRandomNumber(int maxNum)
{
  randomSeed(analogRead(FREE_PIN3));
  return random(maxNum);  
}

// ====================================
// Converter
// ====================================
char* string2Char(String str){
    if(str.length()!=0){
        char *p = const_cast<char*>(str.c_str());
        return p;
    }
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
//StaticJsonDocument<200> toJsonDoc(const String& jsonStr)
StaticJsonDocument<200> toJsonDoc(const char* jsonStr)
{  
  // log("[UTIL] Parsing json string=", jsonStr);  
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
    return doc[attNameLevel1][attNameLevel2][attNameLevel2];
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
