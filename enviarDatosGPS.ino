/******ENVIA EL MENSAJE DE POSICION POR DATOS*************/
void enviarDatosGPS() {
  String posicion = "";

  ////////ACTIVA GPS
  while (escribirComando("AT+GPS=1", 3000, true) != true) { // Envia AT y espera respuesta OK
    escribirComando("AT+GPS=0", 6000, true);
    Serial.println("--GPS DESACTIVADO--");
  }
  do {
    posicion = SerialDatosGPS(); // Lee los datos GPS y guardar valores en variable
    delay(900);
  } while (posicion.length() <= 32);

  if (posicion.length() > 32) {
    escribirComando("AT+GPS=0", 10000, true);
    digitalWrite(p_mux, LOW); // Cambia MUX al serial
    delay(1000);
    while (escribirComando("AT", 3000, false) != true) { // Envia AT y espera respuesta OK
      Serial.println("--desconectado a A7--");
      digitalWrite(p_PWRKEY, HIGH); delay(3000); // 3 seg para Activar la red GSM
      digitalWrite(p_PWRKEY, LOW);
    }
    String dato = "GET https://api.thingspeak.com/update?api_key=2CNOXEGVDQ3X35K7";
    dato += posicion;
    Serial.println(dato);

    proA7.println("AT+CIPSEND");
    delay(4000);
    serialA7();
    proA7.println(dato);
    delay(4000);
    serialA7();
    proA7.println((char)26);
    delay(5000);
    serialA7();
    Serial.println("Enviado");
    escribirComando("AT+CIPCLOSE", 2000, true);
    delay(100);
    escribirComando("AT+CIPSTART=TCP,api.thingspeak.com,80", 10000, true);
    delay(100);

  }
}
