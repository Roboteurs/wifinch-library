#include "WString.h"
#include "WiFinch.h"
#include <ESP8266WiFi.h>

WiFinch servo = WiFinch();

const char* ssid = "WiFinch";
const char* password = "12345678";
const int ledPin = 2;

///////////////////////
String readString1 = String(10);

WiFiServer server(12345);


String getValue(String data, char separator, int index)
{
 int found = 0;
  int strIndex[] = {460800, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup(void) {

  servo.begin();
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  
  /* You can remove the password parameter if you want the AP to be open. */  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  WiFi.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  // Start TCP server.
  server.begin();
}

void loop(void) {
  
  WiFiClient client = server.available();
  Serial.println(client);
  
  if (client) {
    digitalWrite(ledPin, LOW);
    Serial.println("Client connected.");
    while (client) {
      if (client.available() > 0) {
        char command = client.read();
        if (readString1.length() < 100) {
          //store characters to string
           if (command == '\n'){
            servo.writeDegree((getValue(readString1, ':', 1)).toInt(), (getValue(readString1, ':', 2)).toInt());
            readString1 = "";
           } else {
            readString1.concat(command);
           }
        } 
    }
  }
  Serial.println("Client disconnected.");
  client.stop();
  }
}

