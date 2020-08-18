/******ENVIA EL MENSAJE DE POSICION POR DATOS*************/
void enviarDatosGPS() {
  delay(10000); // Activar GPS
  Serial.println("----Recogiendo GPS----"); delay(100); // Mensaje
  //String posicion = SerialDatosGPS(); // Lee los datos GPS y guardar valores en variable
  SerialDatosGPS();
  digitalWrite(p_mux, LOW); // Cambia MUX al serial
  
  Serial.println("---VALORES ALMACENADOS---");  // Muesta los valores GPS almacenados
  Serial.print("Posicion=");Serial.println(posicion);  
  
  ////////ENVIAR DATOS THINKER
    String datos = "GET https://api.thingspeak.com/update?api_key=2CNOXEGVDQ3X35K7"+posicion;
    Serial.print("datosGET:");Serial.println(datos);
    /*
    proA7.println("AT+CIPSEND"); delay(100);
    proA7.println(datos);
    delay(100);
    proA7.println((char)26);
    */
  Serial.println("Mensaje enviado");
  digitalWrite(ledSend, LOW); // Desactiva ledSend (Envio el SMS)
}
