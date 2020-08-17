#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial proA7(10, 11); // pin RX y TX
TinyGPSPlus GPS; // Nombre GPS

////////VARIABLES DE SELECCION
byte datosGPS = 0; // Cambia de modo Serial al modo SerialGPS
byte detectaNumTel = 0; // Detecta si existe un numero telefonico

////////VARIABLES PINES
byte p_mux = 3; // Pin para mux
byte p_PWRKEY = 2; // Pin para activar la red GSM
byte ledSend = 7, ledLlamada = 6, ledGPSon = 4; // Leds de activacion

////////VARIABLE LLAMADAS
byte cuentaLlamada = 0;

//VARIABLES PARA SEPARAR TRAMA
char *strtok(char *str1, const char *str2); //Subfuncion separa la trama
char *numeroPhone = NULL; //No almacena en una memoria especifica
char numeroCellChar[100];

////////DATOS GPS
float LAT = 0, LNG = 0; // Valores de lat y long
float LAT_COMP = 0, LNG_COMP = 0; // Valores de lat y long nuevos a comparar
long TIME = 0;  // Almacena el tiempo recibido del moduloA7
byte SATELITES = 0; // Almacena el num Satelites del moduloA7
byte esperaDatosGps = 200; // Tiempo de espera
byte correccionLocacion = 0; // Numero de veces que se va a corregir

////////VARIABLES PARA DETECTAR LLAMADAS
char valorChar = 0; //Recive los valores char de proA7
String valorStr; // Almacena valores de "valorChar"
char trama1[100]; // valorStr a trama1
char trama2[100]; // valorStr a trama2
char tramaPhone[100]; // Almacena Numero
String strNumero1, strNumTel = ""; // trama separadas almacenada en StrNu..1 y 6
String strNumTelNew = "1"; //Almacenara el valor de strNumTel
char cNumero1[10], cNumTel[13]; // strNumero1 y 6 a arregloChar cNumero1 y 6
char cNumTelNew[13];
char datoNumero[35]; // Almacena numero Telefonico
String cellStr; // almacena numero sin comillas ""
char cellChar[15]; // almacen cellStr a char

////////VARIABLES PARA ENVIO MENSAJE SMS
char ATenvioSMS [20];

////////INICIO DE DISPOSITIVO
byte inicioDispositivo = 10;

/*******FUNC SETUP***************************************************************/
void setup() {
  ////////DECLARAR PINES
  pinMode(p_mux, OUTPUT);// Pin MUX como salida
  //PINES LEDS
  pinMode(ledLlamada, OUTPUT); pinMode(ledGPSon, OUTPUT); pinMode(ledSend, OUTPUT);
  //PIN PARA PWR KEY
  pinMode(p_PWRKEY, OUTPUT);

  delay(20000);  //Esperar a que modulo A7 inicialice
  Serial.begin(9600);
  while (!Serial) {
    ;// Espera al puerto serial se conecte
  }
  proA7.begin(9600); // Velocidad a transferir datos
  Serial.println("------------------------INICIO------------------------");
  configuracionInicial(); // Configuracion inicial
}

/*******FUNC LOOP**********************************************************************/
void loop() {
  ////////MODO NORMAL
  if (detectaNumTel == 1 && strstr(cNumTelNew, trama2) == NULL) { // Son diferentes, ninguna similitud NULL
    detectarNumTel(trama2); // Funcion para almacenar numero Telefonico
    byte i = 0;
    while (i < 11) {
      for (i = 1; i < 11; i++) {
        cellStr = cellStr + cNumTel[i];
      }
    }
    cellStr.toCharArray(cellChar, 15);
    detectaNumTel = 0;
  }
  else if (datosGPS == 1) {
    SerialDatosGPS(); // Activa el modo SerialDatosGPS
  }
  else if (datosGPS == 2 && strstr(cNumTelNew, cNumTel) != NULL && detectaNumTel == 0) { // Son iguales
    EnvioSMS(cellChar); // Funcion para enviar mensaje SMS
    datosGPS = 0; // Activa el modo ComunicacionSerial
  }
  else { // Se activo con valor de 0
    ComunicacionSerial(); // Modo serialComunicacionSerial
  }
}
