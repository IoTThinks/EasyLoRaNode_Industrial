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
  // Set back to input mode
  pinMode(FREE_PIN1, INPUT);
  delay(100);

  // Get sensor value
  _sensorValue = analogRead(FREE_PIN1);   
  Serial.println("[SENSOR] Sensor value=" + (String)_sensorValue);
  
  // This is GPIO2
  // Set to low for easy flashing
  pinMode(FREE_PIN1, OUTPUT);
  digitalWrite(FREE_PIN1, LOW);

  // Value 4095 is normally an error
  if(_sensorValue == 4095)
  {
    return "\"error\""; 
  }
  else
  {
    return (String)_sensorValue;
  }
}
