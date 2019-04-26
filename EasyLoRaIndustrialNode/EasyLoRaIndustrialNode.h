// ===================================================
// Put all pin mappings and library here
// ===================================================
// Serial
#define BAUD_RATE 9600

// LED
#define LED_STATUS1 14       
#define LED_STATUS2 13
#define LED_STATUS3 19
#define LED_STATUS4 21

// Button
#define BTN       34

// LoRa
#include <SPI.h>
#include <LoRa.h>

#define LORA_SS       23
#define LORA_SCK      18
#define LORA_MOSI      5
#define LORA_MISO     36
#define LORA_DIO012   39
#define LORA_RESET    25

#define LORA_SF 12 // 7 is the fastest. 12 is is farthest
#define LORA_CR 5
#define LORA_BW 125E3
#define LORA_PREAMBLE_LENGTH  8

// Free PIN
#define FREE_PIN1    2
#define FREE_PIN2    4
#define FREE_PIN3   26

// Modbus
#define MODBUS_TXD  17
#define MODBUS_RXD  16

// WiFi
#include <WiFi.h>
const char* ssid     = "Easy LoRa";
const char* password = "Password";

// OTA
#include <ArduinoOTA.h>
