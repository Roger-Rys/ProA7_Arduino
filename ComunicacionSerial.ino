/*******FUNC COMUNICACION_SERIAL*****************************************/
void ComunicacionSerial() {
  byte conteoRing = 0; // conteoRing
  byte contador = 0;
  
  digitalWrite(p_mux, LOW); // Cambia MUX al modo Seial
  ////////////////////////MODO SERIAL//////////////////////////////////
  while (proA7.available() > 0) {
    valorChar = proA7.read(); // valorChar
    valorStr += valorChar; //valorStr es un String
    if (valorChar == '\n') { // Detecta "\n" (salto de linea)
      Serial.print("STR:"); Serial.println(valorStr);
      valorStr.toCharArray(trama1, 100); // ValorStr a un arregloChar

      ///////DETECTA EL RING/////////
      if ((strstr(trama1, " RING") != NULL) && conteoRing < 1) { // Detecta si trama1 = RING
        valorStr = " "; // Limpia valorStr
        conteoRing++; // Aumenta conteoRing
        //datosGPS = 2; // Activa la funcion EnvioSMS
        //proA7.println("AT+CLCC"); // Que numero llamada
        //delay(100);
        Serial.print("c_r:");Serial.println(conteoRing);
        proA7.println("ATH"); // Cuelga la llamada
        delay(100);
      }

      ///////DETECTA EL +CLCC contiene el numero telefonico/////////       && strNumTelNew != strNumTel  ó strstr(cNumTelNew, cNumTel) == NULL; son diferentes
      else if ((strstr(trama1, "+CLCC: 1,1,4,0,0,") != NULL) && contador < 1) { // Detecta si trama1 = +CLCC:...
        valorStr.toCharArray(trama2, 100); // Trama2 contiene el numero telefonico y mas valores
        contador++; // Aumenta "contador"
        detectaNumTel = 1; //Valor 1 significa que detecto el numero telefonico 
        Serial.print("trama2:");Serial.println(trama2); //Contiene el numero telefonico
        Serial.print("detectaNumTel:");Serial.println(detectaNumTel); //Imprime detectaNumTel
        Serial.print("datosGPS:");Serial.println(datosGPS); //Imprime datosGPS
        Serial.print("conteoRing:");Serial.println(conteoRing); //Imprime contador
        valorStr = " "; // Limpia valorStr
        memset(trama1, '\0', 100); // Limpia Trama
      }

      ///////BORRA STRING Y TRAMA1/////////
      else {
        valorStr = " "; // Limpia valorStr
        memset(trama1, '\0', 100); // Limpia Trama
      }
    }
  }

  ///////SERIAL DE ARDUINO/////////
  while (Serial.available()) {
    proA7.write(Serial.read()); // Serial lee, Disp escribe
  } delay(50);
}
