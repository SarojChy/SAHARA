

void postData(String alert_type) {

  String Data = "{\"device_uid\":\"" + UID + "\",\"alert_type\":" + alert_type + "}";
  String get_UID_Payload = " ";
  http.begin(client, postServerURL);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(Data);
  if (httpResponseCode == 200) {
    Serial.println(httpResponseCode);
    Serial.println("Post Successfull");
  } else {
    Serial.println(httpResponseCode);
    Serial.println("Error wile connecting to server");
  }
  http.end();
}