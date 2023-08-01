/*
   Nepatronix Engineering Solution
   Notification system
*/

#include <esp_sleep.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define BUTTON_PIN_BITMASK 0x8007000  // GPIOs 2,4,13 and 15

int contentLength;
String UID = "12345678";

// String State = "Fire";
// String Data = "{\"device_uid\":\"" + UID + "\",\"alert_type\":" + State + "}";

AsyncWebServer server(80);
IPAddress localIP;
IPAddress localGateWay(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
WiFiClient client;
HTTPClient http;

const char* ssid = "nepatronix_2.4";
const char* pass = "CLB269DA03";
const char* ServerURL = "";
const char* postServerURL = "http://webhook.site/e28ba9a4-c1ca-4c59-aa0c-4769e83e941d";


#define LED 14


void setup() {
  Serial.begin(115200);
  //Begin serial communication with Arduino and SIM900
  Serial2.begin(115200, SERIAL_8N1, 17, 16);

  pinMode(LED, OUTPUT);

  //Print the wakeup reason for ESP32
  print_wakeup_reason();
  //Print the GPIO used to wake up
  print_GPIO_wake_up();

  esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);

  //Go to sleep now
  Serial.println("Going to sleep now");
  delay(1000);
  esp_deep_sleep_start();
}

void loop() {
  //nothing
}
