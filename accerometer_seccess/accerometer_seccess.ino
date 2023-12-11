#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#define STASSID "PALM"   //ชื่อไวไฟ
#define STAPSK  ""   // รหัสไวไฟ

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.4.1";  //server
const uint16_t port = 9001;  // port server

ESP8266WiFiMulti WiFiMulti;
 WiFiClient client;
 MMA8452Q accel;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // mode wifi esp 8266
  WiFiMulti.addAP(ssid, password);   //connect wifi

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {  // cheack wifi connect
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
  }
  
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  accel.scale = SCALE_8G;    // ตั้ง สเกล เป็น 8G +-
  accel.setScale(accel.scale);
}

void loop() {
  if (accel.available()) {      // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    client.print(accel.getCalculatedX(), 3);  // เเสดงค่าเเกน x
    client.print("\t");
    client.print(accel.getCalculatedY(), 3);   // เเสดงค่าเเกน y
    client.print("\t");
    client.print(accel.getCalculatedZ(), 3);   // เเสดงค่าเเกน z
    client.println();
 
    delay (10);
  }
}
