void setupActuator() {
  log("[ACTUATOR] Setup Actuator");
  digitalWrite(FREE_PIN2, LOW);
  pinMode(FREE_PIN2, OUTPUT);  
}

void onActuator(){
  // Already ON, to skip
  if(digitalRead(FREE_PIN2) == HIGH)
    return;
    
  log("[ACTUATOR] On actuator");
  digitalWrite(FREE_PIN2, HIGH);
}

void offActuator(){
  // Already ON, to skip
  if(digitalRead(FREE_PIN2) == LOW)
    return;
    
  log("[ACTUATOR] Off actuator");
  digitalWrite(FREE_PIN2, LOW);
}
