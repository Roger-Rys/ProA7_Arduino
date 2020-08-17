/******ENVIA EL MENSAJE SMS DE POSICION A NUMERO DETERMINADO*************/
void EnvioSMS(char *NumTel) {
  //digitalWrite(ledLlamada, HIGH); // Activa LedLlamada
  //digitalWrite(ledLlamada, LOW); // Desactiva LedLlamada

  ////////ACTIVA GPS
  digitalWrite(ledGPSon, HIGH); // Activar ledGPSon
  proA7.println("AT+GPS=1"); delay(1000); // Activar GPS
  SerialDatosGPS(); // Lee los datos GPS
  Serial.println("----GPS Activado----"); delay(500); // Mensaje
  DatosObtenidosGPS(); // Obtiene datos GPS correctos
  ////////DESACTIVAR GPS
  proA7.println("AT+GPS=0"); delay(1000); // Desactivar GPS
  digitalWrite(p_mux, LOW); // Cambia MUX al serial
  Serial.println("----GPS Desactivado----"); delay(500);
  digitalWrite(ledGPSon, LOW); // Desactiva ledGPS
  Serial.println("---VALORES ALMACENADOS---");  // Muesta los valores GPS almacenados
  Serial.print("LAT="); Serial.println(LAT);
  Serial.print("LNG="); Serial.println(LNG);
  
  ////////ENVIAR SMS
  digitalWrite(ledSend, HIGH); delay(2000); // Activa ledSend (Envia SMS)
  proA7.println("AT+CMGF=1"); delay(2000); // Configura el Formato a enviar 1 es TEXT

  strcat(ATenvioSMS, "AT+CMGS="); // Almacena strig y caracter strNumTelNew
  strcat(ATenvioSMS, NumTel); // La union se guarda en "ATenvioSMS"
  Serial.println(ATenvioSMS);
  
  proA7.println(datoNumero); delay(2000); // Determina el numero a enviar SMS
  proA7.print(GPS.location.lat(), 6); proA7.print(","); // SMS contiene datos de
  proA7.println(GPS.location.lng(), 6);     // latitud(,) longitud
  delay(2000);
  proA7.println((char)26); // char26 es "ESC", para finalizar mensaje SMS
  
  Serial.println("Mensaje enviado");
  digitalWrite(ledSend, LOW); // Desactiva ledSend (Envio el SMS)
}


