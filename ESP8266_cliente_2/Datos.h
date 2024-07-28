#include <ESP8266WiFi.h>

//Declaración e inicialización de las variables utilizadas
//para la conexión WIFI local http://EspServer/
const char* ESPSSID         = "ESP8266 Server 393A"; //423A
const char* PasswordSSID    = "M_2R9'5#V+w8";


//Información del servidor
//const int ServerPort        = 9995; //Puerto de conexión UDP con el servidor
unsigned int localPort        = 9995;

//Cambiar para que cada cliente se comunique sin problemas
const int ClientPort        = 9996;

//Configuración de IP estática
IPAddress IP_Local(192, 168, 4, 3);
IPAddress gateway(192, 168, 4, 1); //Dirección IP del servidor
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(0, 0, 0, 0);



//Se define una estructura para enviar la distancia al servidor por paquetes UDP
typedef struct udp{
  int id;
  float distancia;
  char sended[10];
} Paquete_UDP;

Paquete_UDP paquete = {1,0,"Enviado"};

typedef struct udpdos{
  int numEstaciones;
  int distanciaCambio;
  char sended[10];
} Paquete_UDP2;
Paquete_UDP2 paquete2;

String macID; //Variable para almacenar la macID
int NumStation = 2;

//==================================================================================
//Definición de pines para el ESP8266 nodeMCU V3 1.0 Módulo ESP - 12E
//==================================================================================

#define D0    16   //GPIO16  - WAKE UP
#define D1    5    //GPIO5
#define D2    4    //GPIO4
#define D3    0    //GPIO0
#define D4    2    //GPIO2   - TXD1

#define D5    14   //GPIO14  - HSCLK
#define D6    12   //GPIO12  - HMISO
#define D7    13   //GPIO13  - HMOSI  - RXD2
#define D8    15   //GPIO15  - HCS    - TXD2
#define RX    3    //GPIO3   - RXD0
#define TX    1    //GPIO1   - TXD0

#define S2 9       //GPIO9
#define S3 10      //GPIO10


//==================================================================================
//Inicialización de pines para el funcionamiento del sensor
//==================================================================================
 
const uint8_t TRIG = D7;      // Señal de transmisión
const uint8_t ECO = D5;       // Señal de recepción
const uint8_t LED_ROJO = D0;  // Led rojo
const uint8_t LED_VERDE = D2; // Led verde
int           DURACION;       // Variable para almacenar la información recibida del sensor
int           DISTANCIA;      // Variable utilizada para transformar a distancia según la información
                              // dada por el fabricante del sensor ultrasónico
uint8_t       Dist_max = 200;
const uint8_t Dist_min = 2;

//==================================================================================
//Setting y funcionamiento del sensor
//==================================================================================

void SetPins(){
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);
}

void LecturaUltrasonica(){
  digitalWrite(TRIG, HIGH);      // Estas tres líneas sirven para medir el tiempo que toma
  delayMicroseconds(10);          // el sensor para enviar y recibir una respuesta  
  digitalWrite(TRIG, LOW);
  
  DURACION = pulseIn(ECO, HIGH); // Devuelve un valor de tiempo equivalente en microsegundos
  DISTANCIA = DURACION / 58.3;   // 58.3 es un valor especificado por el fabricante
                                 // y el resultado es dado en centímentros

// El if evaluará la distancia captada por el sensor y apagará y encenderá los leds
  if (DISTANCIA >= Dist_min && DISTANCIA <= Dist_max){
    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  }
  else if (DISTANCIA >= Dist_max){
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }
  else{
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_VERDE, LOW);
  }
}
