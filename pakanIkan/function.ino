void NTP_Server() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  lcd.setCursor(0, 0);
  lcd.print(&timeinfo, "--- %H:%M:%S ---");

  //Control auto pompa active HIGH
  if ((timeinfo.tm_hour == 7) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 0)) {
    Serial.println("servo turun");
    myServo.write(180);

  } else if ((timeinfo.tm_hour == 7) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 10)) {
    Serial.println("servo naik");
    myServo.write(0);

  } else if ((timeinfo.tm_hour == 16) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 0)) {
    Serial.println("servo turun");
    myServo.write(180);

  } else if ((timeinfo.tm_hour == 16) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 10)) {
    Serial.println("servo naik");
    myServo.write(0);
  }
  Serial.println();
}

void ntpBegin() {
  Serial.printf("Connecting to %s ", ssid);
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  NTP_Server();

  //disconnect WiFi as it's no longer needed
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);
}

void ultrasonik(){
  digitalWrite(trig, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay
  digitalWrite(trig, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW);   // trigPin low
  duration = pulseIn(echo, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance
  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);

  tinggi =  24 - distance;
  nTinggiAir = tinggi;
  Blynk.virtualWrite(V0, tinggi);
}

void suhuTanah(){
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");

  nSuhuAir = temperatureC;
  Blynk.virtualWrite(V4, temperatureC); 

}

BLYNK_WRITE(V1) {
  int btn = param.asInt();
  Serial.print("Pompa In :");
  Serial.println(btn);
  if (btn == 1) digitalWrite(rPompaIn, LOW);
  if (btn == 0) digitalWrite(rPompaIn, HIGH);
}

BLYNK_WRITE(V2) {
  int btn = param.asInt();
  Serial.print("Pompa Out:");
  Serial.println(btn);
  if (btn == 1) digitalWrite(rPompaOut, LOW);
  if (btn == 0) digitalWrite(rPompaOut, HIGH);
}

BLYNK_WRITE(V3) {
  int btn = param.asInt();
  Serial.print("Buzzer:");
  Serial.println(btn);
  if (btn == 1) myServo.write(180);
  if (btn == 0) myServo.write(0);
}

void lcdDisplay(){
    lcd.setCursor(0,1);
    lcd.print("Tinggi : ");
    lcd.setCursor(9,1);
    lcd.print(nTinggiAir);
    delay(1000);

    lcd.setCursor(0,1);
    lcd.print("                         ");

    lcd.setCursor(0,1);
    lcd.print("Suhu : ");
    lcd.setCursor(7,1);
    lcd.print(nSuhuAir);
    delay(1000);

    lcd.setCursor(0,1);
    lcd.print("                         ");

}