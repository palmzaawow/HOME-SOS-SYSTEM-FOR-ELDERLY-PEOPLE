#include "ESPino32CAM.h"
#include "ESPino32CAM_LineNotify.h"
#include <PubSubClient.h>
const char* ssid     = "demon"; 
const char* password = "12345678";
String token = "lj6xRwdFhOEQFXOeQWFk74AUvIrxTosYYfms71U0ENF";
ESPino32CAM cam;
LineNotify line;
#define Button 0
#define mqtt_server "tailor.cloudmqtt.com"
#define mqtt_port 16035
#define mqtt_user "zgvfulhf"
#define mqtt_password "cPzxPfHp5ytw"
int inputPin= MOSI;
int inu= SS;
WiFiClient esp1Client;
PubSubClient client(esp1Client);
void setup() {
  Serial.begin(115200);
  Serial.println("\r\nESPino32CAM");
  pinMode(inputPin, INPUT);
  pinMode(inu, OUTPUT);
  digitalWrite(inu, HIGH);
  if (cam.init() != ESP_OK)
  {
    cam.printDebug(F("Init Fail"));
    while (1);
  }
  sensor_t *s = cam.sensor();
  s->set_framesize(s, FRAMESIZE_VGA);
  s->set_whitebal(s,true);
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\r\nConnected");
  line.authenKey(token);
  line.setUTC(7);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}
void loop()
{
    
    //Serial.println(digitalRead(inputPin));
    delay (1000);
    if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
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

  
  /*camera_fb_t *fb;
  String msg;
  if(!digitalRead(Button))
  {
    lineResp ret;
    msg = "HELP ! :";
    Serial.println("Send Message,Sticker and Image: "+msg);
    Serial.println("Capture");
    fb = cam.capture();
    ret = line.image(msg,fb->buf, fb->len);
	cam.clearMemory(fb);
    if(ret.status)
    {
      Serial.printf("API Called %d/%d per hour\r\n",ret.remaining,ret.limit);
      Serial.printf("Send Image %d/%d per hour\r\n",ret.imageremaining,ret.imagelimit);
      Serial.printf("The time when the limit is reset %d(UTC epoch seconds) , ",ret.reset);
      Serial.println(ret.reset_time);
    }
    else
      Serial.println(ret.response);
   Serial.println();
  }*/
  client.loop(); 
}


void callback(char* topic, byte* payload, unsigned int length) {
  camera_fb_t *fb;
  String msgline;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  int i=0;
  while (i<length) msg += (char)payload[i++];
  if (msg == "CAM2") {
    client.publish("SOS/data/status", "Capture");

    
    lineResp ret;
    msgline = "HELP ! ";
    Serial.println("Send Message,Sticker and Image: "+msgline);
    Serial.println("Capture");
    fb = cam.capture();
    ret = line.image(msgline,fb->buf, fb->len);
  cam.clearMemory(fb);
    if(ret.status)
    {
      Serial.printf("API Called %d/%d per hour\r\n",ret.remaining,ret.limit);
      Serial.printf("Send Image %d/%d per hour\r\n",ret.imageremaining,ret.imagelimit);
      Serial.printf("The time when the limit is reset %d(UTC epoch seconds) , ",ret.reset);
      Serial.println(ret.reset_time);
    }
    else
      Serial.println(ret.response);
   Serial.println();

   
    
    Serial.println("Send !");
    Serial.println(msg);
    return;
  }
    else if (msg == "CAMALL") {
    client.publish("SOS/data/status", "Capture");

    
    lineResp ret;
    msgline = "HELP ! ";
    Serial.println("Send Message,Sticker and Image: "+msgline);
    Serial.println("Capture");
    fb = cam.capture();
    ret = line.image(msgline,fb->buf, fb->len);
  cam.clearMemory(fb);
    if(ret.status)
    {
      Serial.printf("API Called %d/%d per hour\r\n",ret.remaining,ret.limit);
      Serial.printf("Send Image %d/%d per hour\r\n",ret.imageremaining,ret.imagelimit);
      Serial.printf("The time when the limit is reset %d(UTC epoch seconds) , ",ret.reset);
      Serial.println(ret.reset_time);
    }
    else
      Serial.println(ret.response);
   Serial.println();

   
    
    Serial.println("Send !");
    Serial.println(msg);
    return;
  }
  Serial.println(msg);
}
