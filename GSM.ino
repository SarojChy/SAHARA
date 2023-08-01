void updateSerial() {

  while (Serial.available()) {
    Serial2.write(Serial.read());  //Forward what Serial received to Software Serial Port
  }
  while (Serial2.available()) {
    Serial.write(Serial2.read());  //Forward what Software Serial received to Serial Port
  }
  delay(1000);
}

void gprsInit(String Data) {
  Serial2.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  updateSerial();
  Serial2.println("AT+SAPBR=3,1,\"APN\",\"web\"");
  updateSerial();
  Serial2.println("AT+SAPBR=1,1");
  updateSerial();
  Serial2.println("AT+SAPBR=2,1");
  updateSerial();
  Serial2.println("AT+HTTPINIT");
  updateSerial();
  Serial2.println("AT+HTTPPARA=\"URL\",\""+ String(postServerURL)+"\"");
  updateSerial();
  contentLength = Data.length();
  Serial2.print("AT+HTTPPARA=\"CONTENT\",\"Content-Length:");
  Serial2.print(contentLength);
  Serial2.println("\"");
  // Serial2.println("AT+HTTPPARA=\"CONTENT\",\"Content-Length:400\"");
  updateSerial();
  Serial2.println("AT+HTTPPARA=\"CONTENT\",\"Content-Type:application/json\"");
  updateSerial();
}

void sendData(String alert_type) {
  wakeupGSM();
  String Data = "{\"device_uid\":\"" + UID + "\",\"alert_type\":" + alert_type + "}";
  gprsInit(Data);  // Initialization of GPRS with Data length size
  int contentLength = Data.length();

  // Send the AT+HTTPDATA command with content length and timeout (5000 milliseconds)
  Serial2.print("AT+HTTPDATA=");
  Serial2.print(contentLength);
  Serial2.print(",2000\r");
  // Serial2.println("AT+HTTPDATA=ContentLength,100");
  updateSerial();
  Serial2.println(Data);
  updateSerial();
  Serial2.print((char)26);  // ASCII code for Ctrl+Z
  delay(2000);
  Serial2.println("AT+HTTPACTION=1");
  updateSerial();
  connTerminate();
  delay(500);
  sleeGSM();
}

void sleeGSM() {
  Serial.println("Sleeping.....");
  Serial2.println("AT+CSCLK=2");
  updateSerial();
}
void wakeupGSM() {
  Serial.println("Awake.....");
  Serial2.println("AT");
  updateSerial();
  Serial2.println("AT+CSCLK=0");
  updateSerial();
}

void connTerminate() {
  Serial2.println("AT+HTTPTERM");
  updateSerial();
  Serial2.println("AT+SAPBR=0,1");
  updateSerial();
}
