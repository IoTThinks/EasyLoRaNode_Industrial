// ====================================
// LED
// ====================================

String LED_Status = "Not initalized";

void setupLED() {
  digitalWrite(LED1, LOW);
  pinMode(LED1, OUTPUT);    

  digitalWrite(LED2, LOW);
  pinMode(LED2, OUTPUT);    

  digitalWrite(LED3, LOW);
  pinMode(LED3, OUTPUT);    

  digitalWrite(LED4, LOW);
  pinMode(LED4, OUTPUT);        
  
  LED_Status = "OK";
  log("[LED] Setup LED");
}

// LED 1
void onLED1() {
  // Already ON, to skip
  if(digitalRead(LED1) == HIGH)
    return;
  
  log("[LED] On LED1");
  digitalWrite(LED1, HIGH);
}

void offLED1() {  
  // Already OFF, to skip
  if(digitalRead(LED1) == LOW)
    return;
  
  log("[LED] Off LED1");
  digitalWrite(LED1, LOW);
}

// LED 2
void onLED2() {
  log("[LED] On LED2");
  digitalWrite(LED2, HIGH);
}

void offLED2() {  
  log("[LED] Off LED2");
  digitalWrite(LED2, LOW);
}

// LED 3
void onLED3() {
  log("[LED] On LED3");
  digitalWrite(LED3, HIGH);
}

void offLED3() {  
  log("[LED] Off LED3");
  digitalWrite(LED3, LOW);
}

// LED 4
void onLED4() {
  log("[LED] On LED4");
  digitalWrite(LED4, HIGH);
}

void offLED4() {  
  log("[LED] Off LED4");
  digitalWrite(LED4, LOW);
}

void blinkAllLEDs() {
  onLED1();
  delay(500);
  onLED2();
  delay(500);
  onLED3();
  delay(500);
  onLED4();
  delay(500);
  offLED1();
  delay(500);
  offLED2();
  delay(500);
  offLED3();
  delay(500);
  offLED4();
}
