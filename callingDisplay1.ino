#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <Wire.h>
#include "RTClib.h"

#define CLK 11
#define OE  9
#define LAT 10

#define A   A0
#define B   A1
#define C   A2
#define D   A3
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
const char str[] PROGMEM = "Adafruit 16x32 RGB LED Matrix";
int    textX   = matrix.width(),
       textMin = sizeof(str) * -12,
       hue     = 0;

byte seconds, minutes, hours, dayOfWeek, dayOfMonth, months, years;
RTC_DS1307 rtc;
//String inputString = "";
//boolean stringComplete = false;

void setup() {
  delay(1000);
  Wire.begin();
  rtc.begin();
  matrix.begin();
  matrix.setTextSize(4);
  Serial3.begin(9600);
  Serial2.begin(9600);
  Serial.begin(9600);

}

void loop() {
  DateTime now = rtc.now();
  if (stringComplete) {
    if (inputString[0] == '1') {
      matrix.fillScreen(0);
      matrix.setCursor(1, 2);
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      if (now.hour() < 10) {
        matrix.print("0");
        matrix.print(String(now.hour(), DEC));
        matrix.setCursor(45, 2);
        matrix.setTextColor(matrix.Color333(7, 0, 0));
        matrix.print(':');
      }
      else {
        matrix.print(String(now.hour(), DEC));
        matrix.setCursor(45, 2);
        matrix.setTextColor(matrix.Color333(7, 0, 0));
        matrix.print(':');
      }
      if (now.minute() < 10) {
        Serial3.print("0");
        Serial3.println(String(now.minute(), DEC));
      } else {
        Serial3.println(String(now.minute(), DEC));
      }
      // clear the string:
      inputString = "";
      stringComplete = false;
      //delay(500);
      //matrix.fillScreen(0);
      //Serial3.println();
    } else {
      Serial.println(inputString[2]);
      matrix.fillScreen(0);
      matrix.setCursor(14, 2);
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.println(inputString);
      Serial3.print(inputString[2]);
      Serial3.println(inputString[3]);
      // clear the string:
      inputString = "";
      stringComplete = false;
      //delay(500);
      //matrix.fillScreen(0);
      //Serial3.println();
    }
  }
}


/*
  void loop() {
  DateTime now = rtc.now();
  if (stringComplete) {
    if (inputString[0] == '1') {
      matrix.fillScreen(0);
      matrix.setCursor(1, 2);
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.println(String(now.hour(), DEC));
      matrix.setCursor(45, 2);
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.print(':');

      Serial3.println(String(now.minute(), DEC));
      inputString = "";
      stringComplete = false;
    } else {
      Serial.println(inputString[2]);
      matrix.fillScreen(0);
      matrix.setCursor(14, 2);
      matrix.setTextColor(matrix.Color333(7, 0, 0));
      matrix.println(inputString);
      Serial3.print(inputString[2]);
      Serial3.println(inputString[3]);
      inputString = "";
      stringComplete = false;
      //delay(3000);
    }
  }
  }
******************************/
/******************************
  void loop() {
  if (stringComplete) {
    Serial2.println(inputString[2]);
    matrix.fillScreen(0);
    matrix.setCursor(14, 2);
    matrix.setTextColor(matrix.Color333(7,7,7));
    matrix.println(inputString);
    Serial3.print(inputString[2]);
    Serial3.println(inputString[3]);
    // clear the string:
    inputString = "";
    stringComplete = false;
    //delay(3000);
    //matrix.fillScreen(0);
    //Serial3.println();
  }
  }
*/

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


