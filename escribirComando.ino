/*******FUNC ESCRIBIR COMANDOS AT Y RESPUESTA**********************************************************************/
int escribirComando(String ATcomandos, char*Respuesta,  const int timeout) {
  bool valido = 0;
  char valorCharResult = 0;
  String valorStrResult; // Almacena valores de "valorChar"
  char cadenaStrAchar[100];  // valorStrResult a trama1
  long int time = millis(); // Tiempo en a demorar
  do {
    proA7.println(ATcomandos); // Envia a proA7 el "ATcomandos"
    while (proA7.available() > 0 && valido == 0) {
      valorCharResult = proA7.read(); // valorChar
      valorStrResult += valorCharResult; //valorStr es un String
      if (valorCharResult == '\n') { // Detecta "\n" (salto de linea)
        Serial.print("ATresult:"); Serial.println(valorStrResult);
        valorStrResult.toCharArray(cadenaStrAchar, 100); // ValorStr a un arregloChar
        if (strstr(cadenaStrAchar, Respuesta) != NULL) {
          valido = 1;
          break;
        }
        else {
          valorStrResult = " "; // Limpia valorStr
          memset(cadenaStrAchar, '\0', 100); // Limpia Trama
        }
      }
    }
  }
  while ((time + timeout) > millis());
  Serial.print("ValorValido:"); Serial.println(valido);
  return valido;
}
