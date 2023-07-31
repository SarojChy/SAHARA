/*
   Nepatronix Engineering Solution
   Notification system
*/

#include <esp_sleep.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const int sleepPin = 12;  // Change this to the GPIO pin where your button is connected.

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

#define Ambulance 2
#define Police 0
#define Flood 4
#define Fire 5
#define LED 14



void button_pressed_callback() {

  if (WiFi.status() != WL_CONNECTED) {
    if (digitalRead(Ambulance) == 0) {
      Serial.println("Emergency, We need Ambulance!");
      sendData("Ambulance");  //Sending Data to server using GPRS

      digitalWrite(LED, HIGH);
    } else if (digitalRead(Fire) == 0) {
      Serial.println("Emergency, Fire Alert!");
      digitalWrite(LED, HIGH);
    } else if (digitalRead(Flood) == 0) {
      sendData("Flood");
      Serial.println("Emergency, There is flood!");
      digitalWrite(LED, HIGH);
    } else if (digitalRead(Police) == 0) {
      Serial.println("Emergency, We need Police!");
      digitalWrite(LED, HIGH);
    } else {
      digitalWrite(LED, LOW);
    }
    delay(2000);
  } else {
    if (digitalRead(Ambulance) == 0) {
      Serial.println("Emergency, We need Ambulance!");
      postData("Ambulance");  // send alert through WiFi
      digitalWrite(LED, HIGH);
    } else if (digitalRead(Fire) == 0) {
      Serial.println("Emergency, Fire Alert!");
      digitalWrite(LED, HIGH);
    } else if (digitalRead(Flood) == 0) {
      Serial.println("Emergency, There is flood!");
      postData("Flood");
      digitalWrite(LED, HIGH);
    } else if (digitalRead(Police) == 0) {
      Serial.println("Emergency, We need Police!");
      digitalWrite(LED, HIGH);
    } else {
      digitalWrite(LED, LOW);
    }
    delay(2000);
  }
}



void setup() {
  Serial.begin(115200);
  //Begin serial communication with Arduino and SIM900
  Serial2.begin(115200, SERIAL_8N1, 17, 16);
  pinMode(sleepPin, INPUT_PULLUP);

  pinMode(Ambulance, INPUT_PULLUP);
  pinMode(Police, INPUT_PULLUP);
  pinMode(Flood, INPUT_PULLUP);
  pinMode(Fire, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  WiFi.mode(WIFI_STA);
  // checkWiFi();


  int sleepState = digitalRead(sleepPin);
  if (sleepState == LOW) {
    Serial.println("EPS awake...");
    checkWiFi();
    button_pressed_callback();
  }
  delay(1000);
  Serial.println("Going to sleep...");
  esp_sleep_enable_ext0_wakeup((gpio_num_t)sleepPin, LOW);  // Set up the button as the wakeup source.
  esp_deep_sleep_start();
}

void loop() {
}
