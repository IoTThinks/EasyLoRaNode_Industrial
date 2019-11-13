void setupModbus() {
  // Modbus settings
  ModbusSerial.begin(MODBUS_BAUDRATE, SERIAL_8N1, MODBUS_RXD, MODBUS_TXD);
  
  // Modbus slave ID 1
  modbus.begin(MODBUS_SLAVEID, ModbusSerial);  
  modbus.idle(yield);
  
  log("[MODBUS_SENSOR] Setup Modbus sensor");
}

// Get Modbus message
bool getResultMsg(ModbusMaster *node, uint8_t result) 
{ 
  String tmpstr2 = "";
  switch (result) 
  {
    case node->ku8MBSuccess:
      return true;
      break;
    case node->ku8MBIllegalFunction:
      tmpstr2 += "Illegal Function";
      break;
    case node->ku8MBIllegalDataAddress:
      tmpstr2 += "Illegal Data Address";
      break;
    case node->ku8MBIllegalDataValue:
      tmpstr2 += "Illegal Data Value";
      break;
    case node->ku8MBSlaveDeviceFailure:
      tmpstr2 += "Slave Device Failure";
      break;
    case node->ku8MBInvalidSlaveID:
      tmpstr2 += "Invalid Slave ID";
      break;
    case node->ku8MBInvalidFunction:
      tmpstr2 += "Invalid Function";
      break;
    case node->ku8MBResponseTimedOut:
      tmpstr2 += "Response Timed Out";
      break;
    case node->ku8MBInvalidCRC:
      tmpstr2 += "Invalid CRC";
      break;
    default:
      tmpstr2 += "Unknown error: " + String(result);
      break;
  }

  // Print Modbus returned message
  log("[MODBUS_SENSOR] Error message: ", string2Char(tmpstr2));
  return false;
}

// Suport multile words
// Keep original value from Modbus and let the server handle the conversion
String getModbusSensor() {
  Serial.println("[MODBUS_SENSOR] Gettting Modbus sensor");
  
  // Getting result from register id with number of words
  uint8_t result = modbus.readHoldingRegisters(MODBUS_REGISTERID, MODBUS_REGISTERWORD);
  long finalResult = 0;
  
  if (getResultMsg(&modbus, result)) 
  {
    // Loop for multiple word
    for (int i=0; i < MODBUS_REGISTERWORD; i++)
    {
      int wordItem = modbus.getResponseBuffer(i);
      String resItem = "[MODBUS_SENSOR] Modbus response message: " + String(wordItem);
      Serial.println(resItem);

      // Shift value to left 16 bit
      finalResult = finalResult << 16 | wordItem ;
    }
    return (String) finalResult;
  }
  else 
  {
    return "\"error\"";
  }   
}
