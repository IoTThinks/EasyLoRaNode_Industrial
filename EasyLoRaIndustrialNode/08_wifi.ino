void WiFiEvent(WiFiEvent_t event)
{  
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      log("[WiFi] WiFi connected.");      
      log("[WiFi] IP address: ", WiFi.localIP().toString());
      log("[WiFi] MAC address: ", WiFi.macAddress());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      log("[WiFi] WiFi lost connection.  Attempting to reconnect...");
      WiFi.reconnect();
      break;
    case SYSTEM_EVENT_STA_START:
      log("[WiFi] WiFi station start");
      break;
    case SYSTEM_EVENT_STA_CONNECTED:
      log("[WiFi] WiFi station connected to AP");
      break;
    case SYSTEM_EVENT_AP_START:
      log("[WiFi] WiFi AP start");
      break;
    default:      
      //Serial.printf("[WiFi] Unhandled WiFi Event %d\n", event);
      log("[WiFi] Unhandled WiFi Event: ", String(event));
      break;
  }
}

void setupWiFi()
{
    // delete old config
    WiFi.disconnect(true);
    delay(1000);

    WiFi.onEvent(WiFiEvent);

    WiFi.begin(ssid, password);
    WiFi.setSleep(false); // Do not sleep
    log("[WiFi] Wait for WiFi...");
}
