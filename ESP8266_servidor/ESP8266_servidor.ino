//Librerias internas del proyecto
#include "Datos.h"
#include "Wifi.h"
#include "Servidor_Cliente.h"


void setup() {
  
  ArranqueWifi();
  
  mDNS();

  
  server.on("/", paginaInicio);
  
  server.on("/Sensor1", HTTP_GET, Dispositivo1);
  server.on("/nivel1", funcionNivel1);
  
  server.on("/Sensor2", HTTP_GET, Dispositivo2);
  server.on("/nivel2", funcionNivel2);

  server.on("/actualizacion", PaginaActu);
  server.on("/actualizar", HTTP_POST, ActualizarPaso1, ActualizarPaso2);
  
  server.onNotFound(mensajeError);
  
  //Inicialización del servidor
  server.begin();
  Serial.println("Servidor HTTP iniciado");
  Udp_receiving.begin(ServerPort);
  Udp_sending.begin(ClientPort);

  receiving.attach_ms(1910, LectorUDP);  

  Pagina.replace("%ip", WiFi.localIP().toString());
}

void loop() {

  //Condición que llama a la función de reconectar al wifi
  if (WiFi.status() != WL_CONNECTED){
    ActualizarWifi();
  }

  server.handleClient();

  #if defined(ESP8266)
    MDNS.update();
  #endif
  delay(2);
}
