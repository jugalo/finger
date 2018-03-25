#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#include <ESP8266WiFi.h>

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include <Fonts/FreeSerifBold8pt7b.h>

#include "globals.h"

Adafruit_SSD1306 display(SSD1306_RESET);

SoftwareSerial mySerial(D6, D7);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup(){  
  //Serial.begin(9600);
  //while (!Serial);  
  //delay(100);              
  iniBuzzer();
  iniDisplay();
  iniFinger(); 
  if (!iniWifi()){
    ESP.restart();
  }
  PROGRAMA=potenciometro();
}

void loop() {
  PROGRAMA=potenciometro();
  if (PROGRAMA==1){
    finger.getTemplateCount();
    ID=finger.templateCount+1;
    enrollFinger();
  }else {
    getFinger();     
  }
}

