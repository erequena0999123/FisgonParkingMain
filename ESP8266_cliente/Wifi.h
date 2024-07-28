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
#include <WiFiUdp.h>
WiFiUDP Udp;

#endif

#include <Ticker.h>
Ticker sending, receiving;


//Código aplicado para generar sobrecarga de operadores
template<class T> inline Print &operator <<(Print &obj, T arg) { 
  obj.print(arg); 
  return obj; 
}

void ArranqueWifi(){

//==================================================================================
//                                  Código para estación
//==================================================================================

  Serial.begin(115200);
  delay(2000);
  
  WiFi.mode(WIFI_STA);
  Serial.println("\nIniciando multi Wifi");

  if(!WiFi.config(IP_Local,gateway,subnet)){
    Serial.println("Error de configuracion estatica");
  }
  //Redes wifi configuradas
  WifiMulti.addAP(ESPSSID, PasswordSSID);
  //WifiMulti.addAP("", "");

  //Ejecucion del multi Wifi para conectarse a una red de las configuradas
  Serial.print("Conectando a Wifi...");
  if (WifiMulti.run() == WL_CONNECTED) {
    
    Serial << "\n" << "Conectado" << "\n";
    Serial << "SSID: " << WiFi.SSID() << "\n" << "IP: " << WiFi.localIP() << "\n";
    Serial << "ESP Mac: " << WiFi.macAddress() << "\n" << "Submascara de red: " << WiFi.subnetMask();
    Serial << "\n"<< "Gateway: " << WiFi.gatewayIP() << "\n" << "DNS: " << WiFi.dnsIP() << "\n";
    Serial << "De: " << Udp.remoteIP() << ", puerto: " << Udp.remotePort() << "\n";
  }
}


//Función para refrescar el Wifi en caso de desconexión
void ActualizarWifi(){
  byte cont = 0;
  while(WifiMulti.run()!= WL_CONNECTED && cont<=10){
    Serial.print(".");
    delay(5000);
  }
  yield();
  
  Serial << "\n" << "Conectado" << "\n";
  Serial << "SSID: " << WiFi.SSID() << "\n" << "IP: " << WiFi.localIP() << "\n";
  Serial << "ESP Mac: " << WiFi.macAddress() << "\n" << "Submascara de red: " << WiFi.subnetMask();
  Serial << "\n"<< "Gateway: " << WiFi.gatewayIP() << "\n" << "DNS: " << WiFi.dnsIP() << "\n";
  Serial << "De: " << Udp.remoteIP() << ", puerto: " << Udp.remotePort() << "\n";
}
