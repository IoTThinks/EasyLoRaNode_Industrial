// ====================================
// COMMONDITY SENSOR
// ====================================
/*
MQ-135 normal air output 130
      Isopropile alcohol 700
      Lighter Gas        760
      Benzine            450
      Breath1            150
      Breath2            140
*/

void setupSensor() {
  pinMode(FREE_PIN1, INPUT);
  Serial.println("[SENSOR] Setup sensor");
}

String getSensor() {  
  _sensorValue = analogRead(FREE_PIN1);
  Serial.println("[SENSOR] Sensor value=" + (String)_sensorValue);

  String returnValue = "s:" + (String)_sensorValue;
  // Set alarm
  if(_sensorValue > 1000) {
    Serial.println("[SENSOR] Sensor may be not attached. Skip sending message.");
    return "";
  } 
  else if(_sensorValue > 500) {
    onLED1();
    onActuator();
    returnValue = "[Gas detected]"+returnValue;
  }
  else {
    offLED1();
    offActuator();
  }   

  return returnValue;
}

