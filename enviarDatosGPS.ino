/******ENVIA EL MENSAJE DE POSICION POR DATOS*************/
void enviarDatosGPS() {
  String posicion = "";
  String datos = "";
  posicion = SerialDatosGPS(); // Lee los datos GPS y guardar valores en variable
  Serial.print("Posicion:"); Serial.println(posicion);

  digitalWrite(p_mux, LOW); // Cambia MUX al serial
  delay(50);
  if (posicion.length() > 32) {
    ////////ENVIAR DATOS THINKER
    datos = "GET https://api.thingspeak.com/update?api_key=2CNOXEGVDQ3X35K7" + posicion;
    Serial.print("datosGET:"); Serial.println(datos);
    Serial.print("datosGET2:"); Serial.println("GET https://api.thingspeak.com/update?api_key=2CNOXEGVDQ3X35K7" + posicion);
    /*
      proA7.println("AT+CIPSEND"); delay(100);
      proA7.println(datos);
      delay(100);
      proA7.println((char)26);

      Serial.println("Mensaje enviado");
      digitalWrite(ledSend, LOW); // Desactiva ledSend (Envio el SMS)
    */
  }
}
