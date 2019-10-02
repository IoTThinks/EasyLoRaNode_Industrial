// ====================================
// Serial
// ====================================
void setupSerial() {
  Serial.begin(BAUD_RATE);
}

void log(String message)
{
  Serial.println(message);
  if(isBTConnected)
  {
    SerialBT.println(message);
  }
}
