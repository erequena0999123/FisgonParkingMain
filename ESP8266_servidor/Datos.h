#include <ESP8266WiFi.h>

const char* Password_AP       = "M_2R9'5#V+w8";
const int ServerPort          = 9995; //Puerto de conexión UDP con el servidor
const int CanalServer         = 4; //Canal de conexión UDP
const int ClientPort         = 9996;


//Se define la estructura del paquete UDP
typedef struct udp{
  int id;
  float distancia;
  char sended[32];
} Paquete_UDP;
Paquete_UDP paquete;

typedef struct udpdos{
  int distanciaCambio;
  char sended[32];
} Paquete_UDP2;

Paquete_UDP2 paquete2 = {200, "Recibido"};

String Valor1                 = ""; //variables sacadas de la comunicacion
String Valor2                 = ""; //con el servidor
int Nivel1                    = 200; //variables que configuraran el nuevo
int Nivel2                    = 200; //cambio de nivel
int dist_sen1, dist_sen2;
