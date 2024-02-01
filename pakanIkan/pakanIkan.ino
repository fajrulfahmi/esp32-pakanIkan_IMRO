#include "Variable.h"
#include "time.h"
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;
Servo myServo;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, "admin2", "12345678", "blynk.cloud", 80);
  ntpBegin();
  sensors.begin();

  myServo.attach(servo);

  lcd.init();
  lcd.backlight();

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(rPompaIn, OUTPUT);
  pinMode(rPompaOut, OUTPUT);

  timer.setInterval(1000L, ultrasonik);
  timer.setInterval(1000L, suhuTanah);
}

void loop() {
  Blynk.run();
  timer.run();
  NTP_Server();
  lcdDisplay();
}
