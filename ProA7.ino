#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial proA7(10, 11); // pin RX y TX
TinyGPSPlus GPS; // Nombre GPS

////////VARIABLES PINES
byte p_mux = 3; // Pin para mux
byte p_PWRKEY = 2; // Pin para activar la red GSM
byte ledSend = 7, ledLlamada = 6, ledGPSon = 4; // Leds de activacion

////////DATOS GPS
float LAT = 0, LNG = 0; // Valores de lat y long

////////COMUNICACION_SERIAL
byte conteoRing = 0; // conteoRing
char valorChar = 0; //Recive los valores char de proA7
String valorStr; // Almacena valores de "valorChar"
char trama1[100]; // valorStr a trama1
char num_telefoYmas[100]; // valorStr a num_telefoYmas

//////////DETECTAR NUMERO TELEFONICO
char tramaPhone[50]; // Almacena Numero
String NumTelRec="1"; //Numero Telefonico Recibido
String NumTelSav="1"; //Numero Telefonico Guardado
//VARIABLES PARA SEPARAR TRAMA
char *strtok(char *str1, const char *str2); //Subfuncion separa la trama
char *numeroPhone = NULL; //No almacena en una memoria especifica

///////DATOS POR INTERNET
bool enviarDatos = false;

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
  if (NumTelRec != NumTelSav) { // Son diferentes, ninguna similitud NULL
    NumTelSav = NumTelRec;
    Serial.print("Numero Telefonico Guardado: ");Serial.println(NumTelSav);
  }
  //ACTIVAR DATOS
  else if ((conteoRing % 2) == 1 && NumTelSav == NumTelRec && conteoRing>0 && enviarDatos == false) { // Son iguales
   Serial.println("---------DATOS ENCENDIDO---------");
   delay(3000);   
    if (TCP_GPRS()) {
      ////////ACTIVA TCP_GPRS
      enviarDatos = true; //Activo el envio de datos por internet
      Serial.println("Activado TCP_GPRS!!!");
      
      ////////ACTIVA GPS
      digitalWrite(ledGPSon, HIGH); // Activar ledGPSon
      Serial.println("----GPS Activado----"); delay(100); // Mensaje
      proA7.println("AT+GPS=1"); 
    } 
    else {
      enviarDatos = false;
      Serial.println("Sin activar TCP_GPRS");
    }   
  }
   //APAGAR DATOS
  else if ((conteoRing % 2) == 0 && NumTelSav == NumTelRec && conteoRing > 0) { //SON iguales
    ////////DESACTIVAR GPS
    proA7.println("AT+GPS=0"); delay(1000); // Desactivar GPS
    Serial.println("----GPS Desactivado----"); delay(500);
    digitalWrite(ledGPSon, LOW); // Desactiva ledGPS
    
    Serial.println("---------DATOS APAGAR---------");
    escribirComando("AT+CIPCLOSE", 2000, true);
    escribirComando("AT+CIPSHUT", 2000, true);
    enviarDatos = false;
  
    Serial.println("Conexion cerrada---------");
    delay(3000);
    ComunicacionSerial();
  }
  else if (enviarDatos) {
    enviarDatosGPS();
    serialA7(); // Detectar si se recibe llamadas
  }
  else { // Se activo con valor de 0
    ComunicacionSerial(); // Modo serialComunicacionSerial
  }
}
