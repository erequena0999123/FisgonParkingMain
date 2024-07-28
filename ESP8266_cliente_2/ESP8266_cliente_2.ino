//Librerias internas del proyecto
#include "Datos.h"
#include "Wifi.h"
#include "Cliente_Servidor.h"


void setup() {

  ArranqueWifi();

  SetPins();

  Udp.begin(localPort);
  Udp.begin(ClientPort);

  //receiving.attach(1, UPD_Recibido_Servidor);
  sending.attach(4, UDP_Enviado_Servidor);

}

void loop() {
  
  //Condición que llama a la función de reconectar al wifi
  if (WifiMulti.run() != WL_CONNECTED){
    ActualizarWifi();
  }

  if (WiFi.status() == WL_CONNECTED){
    if (ECO == NULL){
    Serial.println("Fallo del sensor!!");
      return;
    }
  
    LecturaUltrasonica();
  }
  
}
