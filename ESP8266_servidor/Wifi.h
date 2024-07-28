//===============================================================================================================================================
//Definición de Librerias para el proyecto
//===============================================================================================================================================

#if defined(ESP32)

//Librerias para ESP32
#include <WiFi.h>
#include <Update.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <WebServer.h>


WebServer server(80);

#elif defined(ESP8266)

//Librerias para ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
//#include <ESPAsyncWebServer.h>

//Establecer el módulo ESP8266 como servidor
//AsyncWebServer server(80); //Puerto 80 (http)
ESP8266WebServer server(80);
WiFiUDP Udp_sending, Udp_receiving;

#endif

#include <WiFiManager.h>

//WiFiManager, creación de un objeto
WiFiManager wm;

#include <Ticker.h>
Ticker tick, receiving;
#define Led_interno LED_BUILTIN
byte cont = 0;

//Código aplicado para generar sobrecarga de operadores
template<class T> inline Print &operator <<(Print &obj, T arg) { 
  obj.print(arg); 
  return obj; 
}

//===============================================================================================================================================
//Definición de funciones WIFI para el proyecto
//===============================================================================================================================================

void EstatusWifi(){
  Serial << "SSID: " << WiFi.SSID() << "\n" << "AP dirección IP: " << WiFi.softAPIP() << "\n" << "Intensidad de señal: " << WiFi.RSSI() << "dBm";
  Serial.println("");
}

void ParpadeoLedWifi(){
  //Cambia el estado del LED
  byte estado = digitalRead(Led_interno);
  digitalWrite(Led_interno, !estado);
}

//===============================================================================================================================================
//                                 Código para Access Point
//===============================================================================================================================================

void AccessPoint(){
      
  // Se obtiene la macID para nombrar nuestro dispositivo
  // Nuestra SSID sera ESP8266 Server + macID
  String mac = WiFi.macAddress();

  //Genera un identificador único basado en los últimos dos bytes de la 
  //dirección MAC del módulo WiFi
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NombreString = "ESP8266 Server " + macID;
  
  //longitud en función de los caracteres de AP_NombreString más el carácter
  //núlo
  char AP_NombreChar[AP_NombreString.length() + 1];
  //Inicializa con 0
  memset(AP_NombreChar, AP_NombreString.length() + 1, 0);
  

  for (int i = 0; i < AP_NombreString.length(); i++)
    AP_NombreChar[i] = AP_NombreString.charAt(i);


  // Se crea el punto de acceso con el nombre ESP8266 Server + macID con la contraseña maestra
  // ssid, contraseña, canal, oculta, máximo de dispositivos conectados
  Serial.println(WiFi.softAP(AP_NombreChar, Password_AP, CanalServer, false, 8) ? "Fallo AP" : "Listo AP");
  EstatusWifi();
  delay(1500);
  Serial.printf("Estaciones conectadas a soft-AP = %d\n", WiFi.softAPgetStationNum());
}

//===============================================================================================================================================
//                                  Código para estación
//===============================================================================================================================================

void WifiManager(){

  pinMode(Led_interno, OUTPUT);
  
  //Uso de la libreria ticker para hacer un temporizador 
  tick.attach_ms(500, ParpadeoLedWifi);

  //Función para borrar la información almacenada en la EEPROM de redes WiFi
  //Función propia de la libreria del ESP8266
  //wm.resetSettings();

  //Creamos el AP y comprobamos si se establece la conexión
  if (!wm.autoConnect("WManager_ESP8266SERVER", "password")){
    Serial.println("Fallo en la conexión, tiempo de espera agotado");
    ESP.restart();
    delay(1000);
  }

  Serial.println("Conexión exitosa!!");

  AccessPoint();

  //Eliminamos el temporizador
  tick.detach();
  //Apagar el LED
  digitalWrite(Led_interno, HIGH); 
}


void ArranqueWifi(){

  Serial.begin(115200);
  delay(2000);
  WiFi.mode(WIFI_AP_STA);
  
  Serial.print("Conectando a Wifi...");
  if (WiFi.status() == WL_CONNECTED) {
    
    Serial << "\n" << "Conectado" << "\n";
    Serial << "SSID: " << WiFi.SSID() << "\n" << "IP: " << WiFi.localIP() << "\n";

    AccessPoint();

  }
  else{
    Serial.println("Iniciando WiFi manager..");
    WifiManager();
  }
}


//Función para refrescar el Wifi en caso de desconexión
void ActualizarWifi(){

  while(WiFi.status()!= WL_CONNECTED){
    if(WiFi.status()!= WL_CONNECTED && cont == 5){
      cont = 0;
      break;
    }
    else{
      cont++;
      Serial.print(".");
      Serial.print(cont);
      delay(2000);
    }
  }

  WifiManager();
  
  Serial << "\n" << "Conectado" << "\n";
  Serial << "SSID: " << WiFi.SSID() << "\n" << "IP: " << WiFi.localIP() << "\n";
}


void mDNS(){

  //Configuración y uso de la libreria mDNS para asignar nombre 
  //para evitar usar la IP en el navegador
  if (!MDNS.begin("EspServer")) {
    Serial.println("Error configurando mDNS!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS configurado");

  //Servicios asignados al mDNS
  MDNS.addService("http", "tcp", 80);
}
