/**********************************************************************************
  * Code for controlling multiple devices connected to one NodeMCU using Amazon Echo
  * 
  * Written by Sid for Sid's E Classroom
  * 
  * https://www.youtube.com/c/SidsEClassroom
  *********************************************************************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define WIFI_SSID "Free_WiFi"//change your Wifi name
#define WIFI_PASS "letsthrill"//Change your Wifi Password
#define SERIAL_BAUDRATE                 115200

fauxmoESP fauxmo;
//declare switching pins
//Change pins according to your NodeMCU pinouts
#define Kitchen D1
#define Bedroom D2
//#define Living D5
//#define Bathroom D6

// -----------------------------------------------------------------------------
// Wifi Setup
// -----------------------------------------------------------------------------

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
// -----------------------------------------------------------------------------
// Device Callback
// -----------------------------------------------------------------------------
void callback(uint8_t device_id, const char * device_name, bool state) {
  Serial.print("Device "); Serial.print(device_name); 
  Serial.print(" state: ");
  if (state) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
  //Switching action on detection of device name
 
  if ( (strcmp(device_name, "Bedroom Light") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(Kitchen, LOW);
    } else {
      digitalWrite(Kitchen, HIGH);
    }
  }
  if ( (strcmp(device_name, "Fan") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(Bedroom, LOW);
    } else {
      digitalWrite(Bedroom, HIGH);
    }
  }
  /*
  if ( (strcmp(device_name, "Study Lamp") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(Living, LOW);
    } else {
      digitalWrite(Living, HIGH);
    }
  }
  if ( (strcmp(device_name, "Night Lamp") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(Bathroom, LOW);
    } else {
      digitalWrite(Bathroom, HIGH);
    }
  }*/
  
}

void setup() {
    //Initialize pins to Low on device start
    pinMode(Kitchen, OUTPUT);
    digitalWrite(Kitchen, HIGH);
    pinMode(Bedroom, OUTPUT);
    digitalWrite(Bedroom, HIGH);
//    pinMode(Living, OUTPUT);
//    digitalWrite(Living, HIGH);
//    pinMode(Bathroom, OUTPUT);
//    digitalWrite(Bathroom, HIGH);
   
    
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");

    // Wifi
    wifiSetup();

    // Device Names for Simulated Wemo switches
    fauxmo.addDevice("Bedroom Light");
    fauxmo.addDevice("Fan");
//    fauxmo.addDevice("Study Lamp");
//    fauxmo.addDevice("Night Lamp");
    fauxmo.onMessage(callback);
}

void loop() {
  fauxmo.handle();
}
