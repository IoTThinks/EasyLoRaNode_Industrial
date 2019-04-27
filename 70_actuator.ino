void setupActuator() {
  Serial.println("[ACTUATOR] Setup Actuator");
  pinMode(FREE_PIN2, OUTPUT);
  digitalWrite(FREE_PIN2, LOW);
}

void onActuator(){
  // Already ON, to skip
  if(digitalRead(FREE_PIN2) == HIGH)
    return;
    
  Serial.println("[ACTUATOR] On actuator");
  digitalWrite(FREE_PIN2, HIGH);
}

void offActuator(){
  // Already ON, to skip
  if(digitalRead(FREE_PIN2) == LOW)
    return;
    
  Serial.println("[ACTUATOR] Off actuator");
  digitalWrite(FREE_PIN2, LOW);
}

