/*******FUNC ESCRIBIR COMANDOS AT Y RESPUESTA**********************************************************************/
bool escribirComando(String comando, const int tiempo, boolean mostrar) {
  bool valido = false;
  String respuesta = "";
  String recoger = "";
  char char_array[100];
  char resultadoChar[50];

  proA7.println(comando);
  Serial.println(comando);
  
  long int time = millis();
  while ( (time + tiempo) > millis())
  {
    while (proA7.available())
    {
      char c = proA7.read();
      recoger += c;

      if (c == '\n') { // Detecta "\n" (salto de linea)
        recoger.toCharArray(char_array, 100); // ValorStr a un arregloChar

        if ((strstr(char_array, "OK") != NULL)) {
          recoger = "";
          respuesta = "OK";
          valido = true;
        } else {
          recoger = ""; // Limpia valorStr
          memset(char_array, '\0', 100); // Limpia Trama
        }
      }
    }
  }
  if (mostrar)
  {
    Serial.println(respuesta);
  }
  return valido;
}


