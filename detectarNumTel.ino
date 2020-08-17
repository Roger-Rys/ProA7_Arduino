/**********DETECTAR NUMERO TELEFONICO*********************************/
void detectarNumTel(char *tramaPhone){
  //memset(tramaPhone, '\0', 100); // Limpia trama2
  memset(cNumero1, '\0', 100);

  char *cadenaSeparar; // Cadena a separar
  char *token;  // token es SubStrings de un String almacena la separacion
  byte conteo = 0; // contador
  cNumero1[0] = NULL;

  if (tramaPhone[0] != NULL ) { // Si tramaPhone no esta vacio
    Serial.print("numeroCelular: "); Serial.println(tramaPhone);
    cadenaSeparar = tramaPhone; // Almacena "tramaPhone" en "cadenaSeparar"
    while ((token = strtok_r(cadenaSeparar, ",", &cadenaSeparar)) != NULL) { // "," es el delimitador a separar
      conteo ++; // Aumenta "conteo"
      if (conteo == 1) { // Si "conteo"=1
        strNumero1 = token; // Token se almacena en "strNumero1"
      }
      if (conteo == 6) { // Si "conteo"=6
        strNumTel = token; // Token se almacena en "strNumTel"
        strNumTelNew = strNumTel;
      }
      strNumero1.toCharArray(cNumero1, 10); // "strNumero1" a arregloChar en cNumero1
      strNumTel.toCharArray(cNumTel, 13); // "strNumTel" a arregloChar en cNumTel
      strNumTelNew.toCharArray(cNumTelNew, 13); //
    }
    if (cNumero1[0] != NULL && cNumTel[0] != NULL) { // Si son diferentes de NULL
      strcat(datoNumero, "NumeroTelef: "); // Almacena strig y caracter
      strcat(datoNumero, cNumTel); // La union se guarda en "datoNumero"
      Serial.println(datoNumero);
    }
  }
}

