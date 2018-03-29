/*
 *****************************************************
   Sensor CO2 DHT22 CO/MQ7 PM1003
 *****************************************************
   https://www.arduinothai.com/article/46/%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B9%83%E0%B8%8A%E0%B9%89-
   arduino-%E0%B8%A3%E0%B9%88%E0%B8%A7%E0%B8%A1%E0%B8%81%E0%B8%B1%E0%B8%9A-nodemcu-esp8266
 *****************************************************
  Arduino Nodemcu Esp8266
  Pin 10  Pin D6
  Pin 11  Pin D5
*/
#include <PID_v1.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "MQ135.h"
#include "DHT.h"

int PM01Value  = 0;       //define PM1.0 value of the air detector module
int PM2_5Value = 0;       //define PM2.5 value of the air detector module
int PM10Value  = 0;       //define PM10 value of the air detector module

SoftwareSerial PMSerial(3, 4); // RX, TX
SoftwareSerial chat(10, 11);   // RX, TX

#define DHTPIN 5      // what digital pin we're connected to
#define LENG 31       //0x42 + 31 bytes equal to 32 bytes
unsigned char buf[LENG];

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11    // DHT 11
#define DHTTYPE DHT22      // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21    // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

void temp();
void co();
void co2();
void SnO2();
void PM();
void updateValue();
void setText(String tmp);

const int CoSensor   = A0;
const int Co2Sensor  = A1;
const int SnO2Sensor = A2;

MQ135 gasSensor = MQ135(SnO2Sensor);

const int DOUTpin  = 8;
const int ledPin   = 13;

String a;
String b;

int valueCo;
int valueCo2;
int valueSnO2;

float localHum  = 0.0;
float localTemp = 0.0;
float localCo   = 0.0;
float localCo2  = 0.0;
float localSnO2 = 0.0;
float PM2_5     = 0.0;

float t;
float h;

float CalibateHumidity =  6.43;
float CalibateTemperature = - 2.41;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

void setup()  {

  Serial.begin(9600);
  chat.begin(9600);
  PMSerial.begin(9600);
  PMSerial.setTimeout(1500);
  dht.begin();
  // Set the default voltage of the reference voltage
  analogReference(DEFAULT);

  pinMode(DOUTpin, INPUT);    //sets the pin as an input to the arduino
  pinMode(ledPin, OUTPUT);    //sets the pin as an output of the arduino

  //initialize the variables we're linked to
  Setpoint = 100;

}

void loop() {

  output();
  updateValue();
}

void temp() {

  delay(2000);

  float h = dht.readHumidity();     //+ CalibateHumidity;
  float t = dht.readTemperature();  //+ CalibateTemperature;

  if (isnan(h) || isnan(t)) {
    return;
  }
  //  Calibrate
  t = t + CalibateTemperature;
  h = h + CalibateHumidity;
  localTemp = t, 1;
  localHum  = h, 1;
  delay(100);
}

void co() {
  valueCo = analogRead(CoSensor); //reads the analaog value from the CO sensor's AOUT pin
  myPID.Compute();
  float CO = valueCo * (5000 / 1024.0);
  localCo = CO / 12000;
  delay(100);
}

void co2() {
  valueCo2 = analogRead(Co2Sensor);
  //myPID.Compute();
  float Co2 = valueCo2 * (5000 / 1024.0);
  int voltage_diference = Co2 - 400;
  localCo2 = voltage_diference * 50.0 / 16.0;
  localCo2 = localCo2 - 831;
  delay(100);
}

void SnO2() {

  float ppm = gasSensor.getPPM();
  localSnO2 = ppm;
  delay(100);
}

void PM() {

  if (PMSerial.find(0x42)) {
    PMSerial.readBytes(buf, LENG);

    if (buf[0] == 0x4d) {
      if (checkValue(buf, LENG)) {
        PM01Value = transmitPM01(buf); //count PM1.0 value of the air detector module
        PM2_5Value = transmitPM2_5(buf); //count PM2.5 value of the air detector module
        PM10Value = transmitPM10(buf); //count PM10 value of the air detector module
      }
    }
  }

  static unsigned long OledTimer = millis();
  if (millis() - OledTimer >= 1000)
  {
    OledTimer = millis();
    /*
      Serial.print("PM1.0: ");
      Serial.print(PM01Value);
      Serial.println("  ug/m3");

      Serial.print("PM2.5: ");
      Serial.print(PM2_5Value);
      Serial.println("  ug/m3");

      Serial.print("PM1 0: ");
      Serial.print(PM10Value);
      Serial.println("  ug/m3");
      Serial.println();
    */
  }

}
char checkValue(unsigned char *thebuf, char leng)
{
  char receiveflag = 0;
  int receiveSum = 0;

  for (int i = 0; i < (leng - 2); i++) {
    receiveSum = receiveSum + thebuf[i];
  }
  receiveSum = receiveSum + 0x42;

  if (receiveSum == ((thebuf[leng - 2] << 8) + thebuf[leng - 1])) //check the serial data
  {
    receiveSum = 0;
    receiveflag = 1;
  }
  return receiveflag;
}

int transmitPM01(unsigned char *thebuf)
{
  int PM01Val;
  PM01Val = ((thebuf[3] << 8) + thebuf[4]); //count PM1.0 value of the air detector module
  return PM01Val;
}

//transmit PM Value to PC
int transmitPM2_5(unsigned char *thebuf)
{
  int PM2_5Val;
  PM2_5Val = ((thebuf[5] << 8) + thebuf[6]); //count PM2.5 value of the air detector module
  return PM2_5Val;
}

//transmit PM Value to PC
int transmitPM10(unsigned char *thebuf)
{
  int PM10Val;
  PM10Val = ((thebuf[7] << 8) + thebuf[8]); //count PM10 value of the air detector module
  return PM10Val;
}

void output () {

  temp();
  co();
  co2();
  SnO2();
  PM();
/*
  Serial.print("Temperature  ");
  Serial.print(localTemp);
  Serial.println(" .C");

  Serial.print("Humidity  ");
  Serial.print(localHum);
  Serial.println(" RH");

  Serial.print("CO  ");
  Serial.print(localCo);
  Serial.println(" PPM");

  Serial.print("CO2  ");
  Serial.print(localCo2, 3);
  Serial.println(" PPM");

  Serial.print("SnO2  ");
  Serial.print(localSnO2);
  Serial.println(" PPM");

  Serial.print("PM1.0: ");
  Serial.print(PM01Value);
  Serial.println(" ug/m3");

  Serial.print("PM2.5: ");
  Serial.print(PM2_5Value);
  Serial.println(" ug/m3");

  Serial.print("PM1 0: ");
  Serial.print(PM10Value);
  Serial.print(" ug/m3");
  Serial.println();
*/
  a = localTemp;
  a += ",";
  a += localHum;
  a += ",";
  a += localCo;
  a += ",";
  a += localCo2;
  a += ",";
  a += localSnO2;
  a += ",";
  a += PM01Value;
  a += ",";
  a += PM2_5Value;
  a += ",";
  a += PM10Value;
  a += "\n";
  //Serial.println(a);
  chat.print(a);
}

void updateValue() {  
  
  float PM2_5 = PM2_5Value;
  
  String strMas = "t10.txt=\"" + String(localTemp, 1)  + "\"";
  String strHui = "t11.txt=\"" + String(localHum, 1)   + "\"";
  String strCO  = "t12.txt=\"" + String(localCo, 3)    + "\"";
  String strCO2 = "t13.txt=\"" + String(localCo2, 1)   + "\"";
  String strPM  = "t14.txt=\"" + String(PM2_5, 1) + "\"";
  
  setText(strMas);
  setText(strHui);
  setText(strCO);
  setText(strCO2);
  setText(strPM);
  //Serial.print("\n");
  delay(3000);
}

void setText(String tmp) {
  Serial.print(tmp);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

/*
 * 
ตัวแปรรับค่า
temp    Temperature celsius
humi  Humidity
co  Carbon monoxide
co2 Carbon dioxide
pm  Particulate matter 

*/





//................................................





