#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "HLs5_GEeKccRcZTqaJHESqHF2xtjRlrc";//Enter your Auth token
char ssid[] = "POCO M2";//Enter your WIFI name
char pass[] = "avila2003";//Enter your WIFI password

BlynkTimer timer;
bool pinValue = 0;
long cm;

#define trig D3
#define echo D4
#define relay D0

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  Wire.begin(D2, D1);

  //lcd.backlight();
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, Wlevel);
  digitalWrite(relay, HIGH);
}

BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}

void loop() {
  Blynk.run();
  timer.run();
}

void Wlevel() {
  if (pinValue == 1) {
    Serial.println("Motor is ON ");
    if (cm <= 30) {
      Serial.println("Water level is low");
      digitalWrite(relay, LOW);
    }
    else if (cm >= 40) {
      Serial.println("Water level is high");
      digitalWrite(relay, HIGH);
      Serial.println("Motor is being switched off");
    }
    else
    {
      Serial.println("Water level is medium");
    }
  }

  //lcd.setCursor(0, 1);

else if (pinValue == 0) {
  digitalWrite(relay, HIGH);
  //lcd.setCursor(0, 1);
  Serial.println("Motor is OFF");
}

digitalWrite(trig, LOW);
delayMicroseconds(20);
//Serial.println("Motor is ON");
digitalWrite(trig, HIGH);
delayMicroseconds(10);
//Serial.println("Motor is OFF");
digitalWrite(trig, LOW);
long t = pulseIn(echo, HIGH);
long cm = t / 29 / 2;


Blynk.virtualWrite(V1, cm);
Serial.println("Water Level: ");
Serial.println(cm);
//lcd.setCursor(0, 0);

//lcd.print(cm);
//lcd.print("   ");
delay(1000);
}
