/**********DETECTAR NUMERO TELEFONICO*********************************/
String detectarNumTel(char *tramaPhone){
  String strNumTel = ""; // trama separadas almacenada en StrNu..1 y 6
  char *cadenaSeparar; // Cadena a separar
  char *token;  // token es SubStrings de un String almacena la separacion
  byte conteo = 0; // contador

  if (tramaPhone[0] != NULL ) { // Si tramaPhone no esta vacio
    cadenaSeparar = tramaPhone; // Almacena "tramaPhone" en "cadenaSeparar"
    while ((token = strtok_r(cadenaSeparar, ",", &cadenaSeparar)) != NULL) { // "," es el delimitador a separar
      conteo ++; // Aumenta "conteo"
      if (conteo == 6) { // Si "conteo"=6
        strNumTel = token; // Token se almacena en "strNumTel"
      }
    }
    if (strNumTel != NULL) { // Si son diferentes de NULL
      return strNumTel;
    }
    else{
      return "Numero no guardado";
    }
  }
}

