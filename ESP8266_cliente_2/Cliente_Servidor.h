
void UDP_Enviado_Servidor(){

  paquete.id = NumStation;  
  paquete.distancia = (int)DISTANCIA;

  Udp.beginPacket(gateway, localPort);
  Udp.write((byte *)&paquete, sizeof(Paquete_UDP));
  Udp.endPacket();
  
  Serial << "ID: "<< paquete.id << "\n" << "Distancia: " << paquete.distancia << " cm" << "\n";
}

void UPD_Recibido_Servidor(){
  //Si hay información disponible leerá el paquete
  int tamanoPaquete = Udp.parsePacket();

  if (tamanoPaquete){
    Serial << "Paquete de tamaño " << tamanoPaquete << " recibido\n";
    Serial << "De: " << Udp.remoteIP() << ", puerto: " << Udp.remotePort() << "\n";

    int len = Udp.read((byte *)&paquete2, sizeof(Paquete_UDP2));
    if (len > 0) {
      //incomingPacket[len] = 0;
    }

    NumStation = paquete2.numEstaciones;
    Dist_max = paquete2.distanciaCambio;

    Serial.println("\nContenido: ");
    Serial << "Número de cliente: " << paquete2.numEstaciones << "\n";
    Serial << "Cambio de distancia: " << paquete2.distanciaCambio << "\n";
    Serial << "Estado: " << paquete.sended << "\n";
  }
}
