void button_pressed_callback(int pressedPin) {
  checkWiFi();

  if (WiFi.status() != WL_CONNECTED) {

    switch (pressedPin) {
      case 13:
        Serial.println("Health Alert!");
        sendData("Health Alert");  //Sending Data to server using GPRS
        digitalWrite(LED, HIGH);
        break;
      case 12:
        Serial.println("Disaster Alert!");
        sendData("Disaster Alert");
        digitalWrite(LED, HIGH);
        break;
      case 14:
        Serial.println("Intruder Alert!");
        sendData("Intruder Alert");
        digitalWrite(LED, HIGH);
        break;
      case 27:
        Serial.println("Communicate Alert!");
        sendData("Communicate Alert");
        digitalWrite(LED, HIGH);
        break;
      default:
        digitalWrite(LED, LOW);
    }
    delay(2000);
  } else {
    switch (pressedPin) {
      case 13:
        Serial.println("Health Alert!");
        postData("Health Alert");  //Sending Data to server using GPRS
        digitalWrite(LED, HIGH);
        break;
      case 12:
        Serial.println("Disaster Alert!");
        postData("Disaster Alert");
        digitalWrite(LED, HIGH);
        break;
      case 14:
        Serial.println("Intruder Alert!");
        postData("Intruder Alert");
        digitalWrite(LED, HIGH);
        break;
      case 27:
        Serial.println("Communicate Alert!");
        postData("Communicate Alert");
        digitalWrite(LED, HIGH);
        break;
      default:
        digitalWrite(LED, LOW);
    }
    delay(2000);
  }
}
