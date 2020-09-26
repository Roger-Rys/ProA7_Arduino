////////////////////////MODO SERIAL//////////////////////////////////
void serialA7() {
  while (proA7.available() > 0) {
    valorChar = proA7.read(); // valorChar
    valorStr += valorChar; //valorStr es un String
    if (valorChar == '\n') { // Detecta "\n" (salto de linea)
      Serial.print("c_s:"); Serial.println(valorStr);
      valorStr.toCharArray(trama1, 100); // ValorStr a un arregloChar

      ///////DETECTA EL RING/////////
      if ((strstr(trama1, " RING") != NULL)) { // Detecta si trama1 = RING
        digitalWrite(ledLlamada, HIGH);  //Indicador de llamada entrante
        
        valorStr = ""; // Limpia valorStr
        memset(trama1, '\0', 100); // Limpia Trama

        conteoRing++; // Aumenta conteoRing
        //Detectar si conteoRing es igual a cero
        if(conteoRing==1){
          //Se ejecuta cada vez que inicializa el dispositivo
          proA7.println("AT+CLCC"); // Que numero llamada
          delay(100);  
        }        

        proA7.println("ATH"); // Cuelga la llamada
        delay(100);        
      }

      ///////DETECTA EL +CLCC contiene el numero telefonico/////////
      else if ((strstr(trama1, "+CLCC: 1,1,4,0,0,") != NULL) && NumTelSav.length() <= 11) { // Detecta si trama1 = +CLCC:...
        valorStr.toCharArray(num_telefoYmas, 100); // num_telefoYmas contiene el numero telefonico y mas valores
        NumTelRec = detectarNumTel(num_telefoYmas);

        valorStr = " "; // Limpia valorStr
        memset(trama1, '\0', 100); // Limpia Trama
        digitalWrite(ledLlamada, LOW); //Indicador de fin de llamada
      }
      ///////BORRA STRING Y TRAMA1/////////
      else {
        valorStr = " "; // Limpia valorStr
        memset(trama1, '\0', 100); // Limpia Trama
      }
    }
  }
}

