#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    
#include <EasyScheduler.h>
// Update these with values suitable for your network.
const char* ssid = "demon";
const char* password = "12345678";
float a,b,c;
float tol = 0.0;
String ALL;
char AA[8],BB[8],CC[8],DD[32];
// Config MQTT Server
#define mqtt_server "tailor.cloudmqtt.com"
#define mqtt_port 16035
#define mqtt_user "zgvfulhf"
#define mqtt_password "cPzxPfHp5ytw"
WiFiServer server(9001); // ประกาศสร้าง TCP Server ที่พอร์ต 9001
WiFiClient  client1;

WiFiClient espClient;
PubSubClient client(espClient);
 MMA8452Q accel;
 
Schedular Task1; // สร้างงาน Task
Schedular Task2;
unsigned long time1,time2,time3;

void setup() {
  
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_AP_STA); // ใช้งาน WiFi ในโหมด AP
  WiFi.softAP("palmzaawow"); // ตั้งให้ชื่อ WiFi เป็น PALM

  server.begin(); // เริ่มต้นใช้ TCP Server
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  accel.scale = SCALE_8G;    // ตั้ง สเกล เป็น 8G +-
  accel.setScale(accel.scale);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  time1 = millis();
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("SOS/data/detect");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
      return;
    }
  }
  //Task1.check(, 1000); 
  Task2.check(chack, 1000);
  if (accel.available()) {      // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
   float a = (accel.getCalculatedX());
   float b = (accel.getCalculatedY());
   float c = (accel.getCalculatedZ());
   // b = (accel.getCalculatedY(), 3);
   // c = (accel.getCalculatedZ(), 3);
   float tol = 0.0;
    tol = float(sqrt(pow(a, 2)+pow(b, 2)+pow(c, 2)));
    //Serial.println(tol);
    delay (10);
    /*if (tol >= 3.2){
       client.publish("SOS/data/detect","CAMALL");
       delay(100);
       
    }*/
   
    dtostrf(a,1,3,AA);dtostrf(b,1,3,BB);dtostrf(c,1,3,CC);
    ALL = String(a)+"\t"+String(b)+"\t"+String(c);
    ALL.toCharArray(DD, 32);;
   /* Serial.println(DD);
    Serial.println(String(a));
    Serial.println(accel.getCalculatedX(), 3);
    Serial.println(String(c));*/
    client.publish("SOS/data",DD);
    delay (100);
    }
  client.loop();

time2 = millis();
time3 = (time2-time1);
Serial.println(time3);
}
void chack(){

    if (tol >= 3.2){
       client.publish("SOS/data/detect","CAMALL");
       delay(100);
      }
    delay (100);
    }
  

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  int i=0;
  while (i<length) msg += (char)payload[i++];
  if (msg == "GET") {
    client.publish("SOS/data/status", "LEDOFF");
    Serial.println("Send !");
    Serial.println(msg);
    return;
  }
  Serial.println(msg);
}
