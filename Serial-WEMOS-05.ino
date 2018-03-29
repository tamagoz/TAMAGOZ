
/*
  Arduino Nodemcu Esp8266
  Pin 10  Pin D6
  Pin 11  Pin D5
*/

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial chat(D5, D6); // RX, TX

#define SERVER_PORT 80
const char* ssid     = "Happy4.0";           //== 1 == ใส่ชื่อเครือข่าย WiFi ที่จะให้ Device เชื่อมต่อ
const char* password = "Thailand4.0";

//const char* ssid     = "GreatODev";              //== 1 == ใส่ชื่อเครือข่าย WiFi ที่จะให้ NodeMCU V2 เชื่อมต่อ
//const char* password = "1683vios";

//BOX-001
//const char* KeyCode     = "y1snUSTAUdFnbuHZdgcO";             //== 2 == ใส่ KeyCode  ของ Device
//const char* SecretKey = "qvjVNInlymUGeHBgbJSkJ7hIVTWNwc";     //== 3 == ใส่ SecretKey ของ Device

//BOX-002
//const char* KeyCode     = "Sm6y1HlqLV6hU5xvNdl0";             //== 2 == ใส่ KeyCode  ของ Device
//const char* SecretKey = "kAKFgbd3gDAOsE5LTJXEONWqtPMxmp";     //== 3 == ใส่ SecretKey ของ Device

//BOX-003
const char* KeyCode     = "fwxo8sOA4KFPPoo0xy6P";             //== 2 == ใส่ KeyCode  ของ Device
const char* SecretKey = "l1eF7cnndJfirXy148AYdX3ZxAV5Io";     //== 3 == ใส่ SecretKey ของ Device

const char* host = "piwatair.net";        //กำหนดชื่อ Server ที่ต้องการเชื่อมต่อ
WiFiServer server(SERVER_PORT);           //เปิดใช้งาน TCP Port 80
WiFiClient client;                        //ประกาศใช้  client

void sentDATA();

String a = "";

int counter = 0;
int lastIndex = 0;

float data[9];
float sensorValue = 0.0;                   // value read from the pot

void setup() {

  Serial.begin(9600);
  chat.begin(9600);
  delay(10);

  WiFi.begin(ssid, password);             //เชื่อมต่อกับ AP
  while (WiFi.status() != WL_CONNECTED)   //ตรวจเช็ค และ รอจนเชื่อมต่อ AP สำเร็จ
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());         //แสดง IP Address ที่ได้
}

void loop() {

  chat.print("Question1"); // ส่งหัวข้อคำถาม ว่า Question1 ไปยัง Arduino
  delay(10);
  a = chat.readString();   // อ่าน Serial และนำไปเก็บในตัวแปร a

  Serial.print(a);

  for (int i = 0; i < a.length(); i++) {
    if (a.substring(i, i + 1) == ",") {
      data[counter] = a.substring(lastIndex, i).toFloat();
      lastIndex = i + 1;
      counter++;
    }
    if (i == a.length() - 1) {
      data[counter] = a.substring(lastIndex, i).toFloat();
    }
  }

  if (!client.connect(host, SERVER_PORT)) {
    Serial.println("connection failed");
    return;
  }
  sentDATA();
  a = "";
  counter = 0;
  lastIndex = 0;
  delay(1000);
}

/***************************************************
  Send data
****************************************************/
void sentDATA() {

  String url = "/SensorRead.php?";
  url += "KeyCode=";
  url += KeyCode;
  url += "&SecretKey=";
  url += SecretKey;
  url += "&temp=";
  url += data[0];
  url += "&humi=";
  url += data[1];
  url += "&CO=";
  url += data[2];
  url += "&CO2=";
  url += data[3];
  //url += "&SnO2=";
  //url += data[4];
  //url += "&Pm1=";
  //url += data[5];
  url += "&pm=";
  url += data[6];
  //url += "&Pm10=";
  //url += data[7];

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println("send data");
  Serial.println(url);
  delay (1000);
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





