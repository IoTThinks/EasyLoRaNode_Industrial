void setupActuator() {
  log("[ACTUATOR] Setup Actuator");

  // Pin P2
  digitalWrite(FREE_PIN2, LOW);
  pinMode(FREE_PIN2, OUTPUT);  

  // Restore saved state
  String savedActuatorState = getPreference("PREFS_P2_STATE");

  if(savedActuatorState == "true")
  {
    log("[ACTUATOR] Restored actuator state to ON.");
    onActuator();
  }
  else
  {
    // State is false or not saved
    log("[ACTUATOR] Saved actuator state to OFF. Do nothing.");
  }
}

void onActuator(){
  // Save to FLASH
  setPreference("PREFS_P2_STATE", "true");
  
  // Already ON, to skip
  if(digitalRead(FREE_PIN2) == HIGH)
    return;
    
  log("[ACTUATOR] On actuator");
  digitalWrite(FREE_PIN2, HIGH);
}

void offActuator(){
  // Save to FLASH
  setPreference("PREFS_P2_STATE", "false");
  
  // Already ON, to skip
  if(digitalRead(FREE_PIN2) == LOW)
    return;
    
  log("[ACTUATOR] Off actuator");
  digitalWrite(FREE_PIN2, LOW);
}
