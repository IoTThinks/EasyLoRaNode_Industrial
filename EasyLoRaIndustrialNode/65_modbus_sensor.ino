void setupModbus() {
  // Modbus communication runs at 9600 baud
  ModbusSerial.begin(9600, SERIAL_8N1, MODBUS_RXD, MODBUS_TXD);
  
  // Modbus slave ID 1
  modbus.begin(Slave_ID, ModbusSerial);  
  modbus.idle(yield);
  
  Serial.println("[MODBUS_SENSOR] Setup Modbus sensor");
}

// Get Modbus message
bool getResultMsg(ModbusMaster *node, uint8_t result) 
{ 
  String tmpstr2 = "\r\n";
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
  Serial.println("[MODBUS_SENSOR] Error message:" + tmpstr2);
  return false;
}

String getModbusSensor() {
  Serial.println("[MODBUS_SENSOR] Gettting Modbus sensor");
  
  // Getting result from register id with number of words
  uint8_t result = modbus.readHoldingRegisters(MODBUS_REGISTERID, MODBUS_REGISTERWORD);
  if (getResultMsg(&modbus, result)) 
  {
    double res_dbl = modbus.getResponseBuffer(0) / 10.0;
    String res = "[MODBUS_SENSOR] Modbus message: " + String(res_dbl);
    Serial.println("[MODBUS_SENSOR] Modbus response message: " + String(res_dbl));
    //res_dbl = modbus1.getResponseBuffer(1) / 10;
    //res += "Humidity2: " + String(res_dbl) + " %";
    
    return "mbs:" + (String) res_dbl;
  }
  else 
  {
    return "mbs:error";
  }   
}

