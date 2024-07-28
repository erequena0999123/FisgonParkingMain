//Librerias para ESP8266
#include <ESP8266WiFi.h>
//#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
//ESP8266WiFiMulti WifiMulti;

//#include <strings_en.h>
#include <WiFiManager.h>
//#include <wm_consts_en.h>
//#include <wm_strings_en.h>
//#include <wm_strings_es.h>

int Led_interno = 2;

//Código aplicado para generar sobrecarga de operadores
template<class T> inline Print &operator <<(Print &obj, T arg) { 
  obj.print(arg); 
  return obj; 
}

void AccessPoint(){

//==================================================================================
//                                 Código para Access Point
//==================================================================================
    
  // Se obtiene la macID para nombrar nuestro dispositivo
  // Nuestra SSID sera ESP8266 Server + macID
  String mac = WiFi.macAddress();

  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NombreString = "ESP8266 Server " + macID;
  

  char AP_NombreChar[AP_NombreString.length() + 1];
  memset(AP_NombreChar, AP_NombreString.length() + 1, 0);
  

  for (int i = 0; i < AP_NombreString.length(); i++)
    AP_NombreChar[i] = AP_NombreString.charAt(i);


  // Se crea el punto de acceso con el nombre ESP8266 Thing + macID 
  // con la contraseña maestra
  Serial.println(WiFi.softAP(AP_NombreChar, "Password_AP")? "Listo AP" : "Fallo AP");
}


void ParpadeoLedWifi(){
  //Cambia el estado del LED
  byte estado = digitalRead(Led_interno);
  digitalWrite(Led_interno, !estado);
}

void WifiManager(){

  //pinMode(Led_interno, OUTPUT);
  WiFiManager wm;

  //Uso de la libreria ticker para hacer un temporizador 
  //tick.attach_ms(500, ParpadeoLedWifi);

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
  //tick.detach();
  //Apagar el LED
  //digitalWrite(Led_interno, HIGH); 
}


void ArranqueWifi(){

//==================================================================================
//                                  Código para estación
//==================================================================================
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
    WifiManager();
    Serial.println("Wifi manager ejecutandose");
  }
}

void OTA(){

  // Puerto por defecto en 8266
  ArduinoOTA.setPort(8266);

  // Nombre por defecto esp8266-[ChipID]
  String mac = WiFi.macAddress();
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String OTA_Nombre = "ESP8266 Server " + macID;
  ArduinoOTA.setHostname(OTA_Nombre.c_str());

  // Sin autenticación por defecto
  ArduinoOTA.setPassword("admin");

  // La contraseña puede ser colocada con un valor MD5 (hash)
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    Serial.println("Iniciando Programación " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nTerminando");
    Serial.printf("Memoria Libre %u bytes\n", ESP.getFreeSketchSpace());
    delay(5000);
    ESP.restart();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progreso: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Falló");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Fallo de inicio");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Fallo de conexión");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Fallo de recibo");
    } else if (error == OTA_END_ERROR) {
      Serial.println("Fallo de finalización");
    }
  });

  ArduinoOTA.begin();

  //Serial.println("Listo");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Dirección IP Soft-AP = ");
  Serial.println(WiFi.softAPIP());
}
