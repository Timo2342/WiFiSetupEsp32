#include <Arduino.h>
#include <WiFiSetup.h>

char*ssid = "your Wlan SSID";
char*password = "your wlan Password";

WlanSetup WiFi;
void setup(){
    WiFi.begin();
    WiFi.tryConnect(ssid,password);
}
void loop(){
}