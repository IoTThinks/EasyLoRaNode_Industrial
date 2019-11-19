// ===================================================
// Put all pin mappings and library here
// ===================================================
// Serial
#define BAUD_RATE 115200 //9600

// LED
#define LED1 14       
#define LED2 13
#define LED3 19
#define LED4 21

// Button
#define BTN       34

// LoRa
#include <SPI.h>
#include <LoRa.h>

// LoRa pins
#define LORA_SS       23
#define LORA_SCK      18
#define LORA_MOSI      5
#define LORA_MISO     36
#define LORA_DIO012   39
#define LORA_RESET    25

// LoRa signal configuration
#define LORA_FREQ_BASE 433E6
#define LORA_FREQ_STEPS 200E3 // Steps must be larger than BW
#define LORA_FREQ_NUM_CHANNELS 19 // Max channels (not including base channel)
#define LORA_SF 7 // 7 is the fastest. 12 is is farthest
#define LORA_CR 5
#define LORA_BW 125E3 // 41.7E3, 125E3
#define LORA_PREAMBLE_LENGTH  8
long LORA_FREQ_RX = LORA_FREQ_BASE; // Default as base frequency

// Free PIN
#define FREE_PIN1    2
#define FREE_PIN2    4
#define FREE_PIN3   26

// Sensor
int _sensorValue;

// Modbus
// Serial 1 but GPIO16 and 17
#include "ModbusMaster.h"
#include <HardwareSerial.h>
#define MODBUS_BAUDRATE 9600
#define MODBUS_RXD  16
#define MODBUS_TXD  17
#define MODBUS_REGISTERID 0x2010
#define MODBUS_REGISTERWORD 1
#define MODBUS_SLAVEID 1

// instantiate ModbusMaster object
ModbusMaster modbus;

// Serial to connect to RS485 module
HardwareSerial ModbusSerial(1);

// WiFi
#include <WiFi.h>
const char* ssid     = "Easy LoRa";
const char* password = "EasyLoRa123";

// Bluetooth
#include "BluetoothSerial.h"
#include "esp_bt.h"
// Bluetooth Serial object
BluetoothSerial SerialBT;
bool isBTConnected = false;

// OTA
#include <ArduinoOTA.h>

// =====================
// Utils - System
// =====================
#include <ArduinoJson.h>
char SYS_ChipID[15];
char SYS_HostName[20];
byte SYS_NetworkID;

// =====================
// Cron jobs
// =====================
#define CRONJOB_PRIORITY_READLORA 0
#define CRONJOB_PRIORITY_UPDATESENSOR 0 // Idle
unsigned long CRONJOB_START_MILLIS = 0;
unsigned long CRONJOB_CURRENT_MILLIS;
const unsigned long CRONJOB_PERIOD = 5000; // miliseconds

// To store internal updated sensor data
String CRONJOB_SENSOR_DATA((char *)0);
