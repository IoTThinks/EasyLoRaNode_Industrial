// ====================================
// LED
// ====================================
// LEDs are connected anode to +5, cathode to i/o pin. Aka: Active LOW.
// So pin set to LOW will on the LED
String LED_Status = "Not initalized";

void setupLED() {
  pinMode(LED_STATUS1, OUTPUT);    
  digitalWrite(LED_STATUS1, LOW);  

  pinMode(LED_STATUS2, OUTPUT);    
  digitalWrite(LED_STATUS2, LOW);  

  pinMode(LED_STATUS3, OUTPUT);    
  digitalWrite(LED_STATUS3, LOW);  

  pinMode(LED_STATUS4, OUTPUT);    
  digitalWrite(LED_STATUS4, LOW);  
  
  LED_Status = "OK";
  Serial.println("[LED_STATUS1]==> Setup LED");
}

// LED 1
void onLED_STATUS1() {
  Serial.println("[LED]==> On LED_STATUS1");
  digitalWrite(LED_STATUS1, HIGH);
}

void offLED_STATUS1() {  
  Serial.println("[LED]==> Off LED_STATUS1");
  digitalWrite(LED_STATUS1, LOW);
}

// LED 2
void onLED_STATUS2() {
  Serial.println("[LED]==> On LED_STATUS2");
  digitalWrite(LED_STATUS2, HIGH);
}

void offLED_STATUS2() {  
  Serial.println("[LED]==> Off LED_STATUS2");
  digitalWrite(LED_STATUS2, LOW);
}

// LED 3
void onLED_STATUS3() {
  Serial.println("[LED]==> On LED_STATUS3");
  digitalWrite(LED_STATUS3, HIGH);
}

void offLED_STATUS3() {  
  Serial.println("[LED]==> Off LED_STATUS3");
  digitalWrite(LED_STATUS3, LOW);
}

// LED 4
void onLED_STATUS4() {
  Serial.println("[LED]==> On LED_STATUS4");
  digitalWrite(LED_STATUS4, HIGH);
}

void offLED_STATUS4() {  
  Serial.println("[LED]==> Off LED_STATUS4");
  digitalWrite(LED_STATUS4, LOW);
}
