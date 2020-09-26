/******ENVIA EL MENSAJE DE POSICION POR DATOS*************/
void enviarDatosGPS() {
  String posicion = "";
  delay(500);
  
  ////////ACTIVA GPS
  while (escribirComando("AT+GPS=1", 3000, true) != true) { // Envia AT y espera respuesta OK
    escribirComando("AT+GPS=0", 6000, true);
    Serial.println("--GPS DESACTIVADO--");
  }
  delay(500);
  do {
    posicion = SerialDatosGPS(); // Lee los datos GPS y guardar valores en variable
    delay(1000);
  } while (posicion.length() <= 32);
  delay(250);//500
  
  ////////DESACTIVA GPS
  escribirComando("AT+GPS=0", 5000, true);//10000
  digitalWrite(p_mux, LOW); // Cambia MUX al serial
  delay(500);//1000

  //Comprobar si activa todo de TCP_GPRS
  while (TCP_GPRS(true,iniciado) != true) {
    ////////ACTIVA TCP_GPRS
    iniciado=false;
    escribirComando("AT+CIPCLOSE", 4000, true);
    delay(100); //1000
    escribirComando("AT+CIPSHUT", 4000, true);
    delay(100);
    Serial.println("Desactivado TCP_GPRS");
  }
  delay(500);
  Serial.println("Activado TCP_GPRS!!!");
  iniciado=true;

  if (posicion.length() > 32) {
   
    String dato = "GET https://api.thingspeak.com/update?api_key=2CNOXEGVDQ3X35K7";
    dato += String(posicion);
    Serial.println(dato);
    delay(200);
      proA7.println("AT+CIPSEND");
      delay(500);
      serialA7();
      proA7.println(dato);
      delay(500);
      serialA7();
      proA7.println((char)26);
      delay(5000);
      serialA7();    
    escribirComando("AT+CIPCLOSE", 4000, true);
    digitalWrite(ledSend, HIGH); //Indicador de envio de mensaje 
    delay(100);
      
    while (escribirComando("AT", 3000, true) != true) { // Envia AT y espera respuesta OK
      Serial.println("--desconectado a A7--");
      digitalWrite(p_PWRKEY, HIGH); delay(3000); // 3 seg para Activar la red GSM
      digitalWrite(p_PWRKEY, LOW);
    }
    Serial.println("Enviado");
    
    digitalWrite(ledSend, LOW);  //Apagar indicador de envio de mensaje
    delay(100);
    //escribirComando("AT+CIPSTART=TCP,api.thingspeak.com,80", 10000, true);
    //delay(100);
  }
}
