void checkWiFi() {
  // firstFlag = true;
  WiFi.begin(ssid, pass);
  delay(1000);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting WiFi");
  } else {
    Serial.println("WiFi Connected");
  }
}
