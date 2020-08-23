
bool escribirComando(String comando, const int timeout, bool mostrar)
{
  bool valido = false;
  char char_array[75];
  String recoger = "";
  String respuesta = "";
  
  Serial.println(comando);
  proA7.println(comando);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (proA7.available())
    {
      char c = proA7.read();
      recoger += c;
      if (c == '\n') { // Detecta "\n" (salto de linea)
        recoger.toCharArray(char_array, 70); // ValorStr a un arregloChar

        if ((strstr(char_array, "OK") != NULL)) {
          respuesta = "OK";
          recoger = "";
          valido = true;
        } 
        else {
          recoger = ""; // Limpia valorStr
          memset(char_array, '\0', 70); // Limpia Trama
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


