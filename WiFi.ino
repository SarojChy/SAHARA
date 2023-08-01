void checkWiFi() {
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  delay(2000);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi couldn't connect..");
  } else {
    Serial.println("WiFi Connected");
  }
}
