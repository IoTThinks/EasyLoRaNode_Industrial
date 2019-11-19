// ====================================
// Serial Bluetooth
// ====================================

// References
// https://github.com/espressif/arduino-esp32/blob/master/libraries/BluetoothSerial/examples/SerialToSerialBT/SerialToSerialBT.ino

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void serialBTCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    log("[SerialBT] BT client connected");
    isBTConnected = true;
  }
 
  if(event == ESP_SPP_CLOSE_EVT ){
    log("[SerialBT] BT client disconnected");
    isBTConnected = false;
  }
}

void setupSerialBT() {
  // Bluetooth device name
  SerialBT.register_callback(serialBTCallback);
  SerialBT.begin(SYS_HostName);
  esp_bt_mem_release(ESP_BT_MODE_BLE);
  log("[SerialBT] SerialBT starts OK. To pair with bluetooth for debug log.");  
}
