#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"
#include <PubSubClient.h>
#define LED_PIN D1
int speakerPin = 14;

class myMQTTBroker: public uMQTTBroker
{
public:
    virtual bool onConnect(IPAddress addr, uint16_t client_count) {
      Serial.println(addr.toString()+" connected");
      return true;
    }
    
    virtual bool onAuth(String username, String password) {
      Serial.println("Username/Password: "+username+"/"+password);
      return true;
    }
    
    virtual void onData(String topic, const char *data, uint32_t length) {

      
      char data_str[length+1];
      os_memcpy(data_str, data, length);
      data_str[length] = '\0';
      
        int p =(char)data[0]-'0';
  // if MQTT comes a 0 turn off LED on D1
  if(p==0) 
  {
     digitalWrite(LED_PIN, LOW); 
    Serial.println(" Turn Off LED! " );
    tone(speakerPin,100,1000);
  } 
  // if MQTT comes a 1, turn on LED on pin D1
  if(p==1)
  {
     digitalWrite(LED_PIN, HIGH); 
   Serial.println(" Turn On LED! " );
   tone(speakerPin,1000,500);
 }
      
      Serial.println("received topic '"+topic+"' with data '"+(String)data_str+"'");
    }
};

myMQTTBroker myBroker;


void startWiFiAP()
{
  //WiFi.mode(WIFI_AP);
  WiFi.softAP("TUAN-^^","88888888");
  Serial.println("AP started");
  Serial.println("IP address: " + WiFi.softAPIP().toString());
}

void setup()
{
  WiFi.mode(WIFI_AP);
  Serial.begin(115200);
  Serial.println();
//  Serial.println();
    startWiFiAP();

  // Start the broker
  Serial.println("Starting MQTT broker");
  myBroker.init();


  myBroker.subscribe("led");
//  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
 

}

int counter = 1;

  
void loop()
{

//   myBroker.publish("led", (String)counter++);
 Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum());
  // wait a second
delay(1000);
}
