#if defined(ESP32)

//Librerias para ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiMulti.h>
WiFiMulti WifiMulti;

#elif defined(ESP8266)

//Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WifiMulti;

#endif


//Código aplicado para generar sobrecarga de operadores
template<class T> inline Print &operator <<(Print &obj, T arg) { 
  obj.print(arg); 
  return obj; 
}

String macID, macID2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  Serial.println("SoftAP");
  Serial.println(macID);
  Serial.println("==================");
  delay(5000);

  String mac2 = WiFi.macAddress();

  String macID2 = String(mac2[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac2[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  Serial.println(macID2);
  delay(2000);

}
