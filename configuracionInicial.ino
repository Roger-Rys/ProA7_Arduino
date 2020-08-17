/*******FUNC CONFIGURACION_INIC*******************************************************/
void configuracionInicial() {
  digitalWrite(p_mux, LOW); // Cambia MUX al serial
  digitalWrite(p_PWRKEY, HIGH); delay(3000); // 2 seg para Activar la red GSM
  digitalWrite(p_PWRKEY, LOW); delay(10000);
  Serial.println("PWR_KEY Activado"); // Mensaje que la red esta activada

  while (escribirComando("AT", "OK", 1000) != 1) { // Envia AT y espera respuesta OK
    Serial.println("----No conectado con modulo A7----");
    digitalWrite(p_PWRKEY, HIGH); delay(3000); // 3 seg para Activar la red GSM
    digitalWrite(p_PWRKEY, LOW); 
  }
  Serial.println("----Conectado con modulo A7----");

  digitalWrite(ledGPSon, HIGH); // Activar ledGPS
  proA7.println("AT+GPS=1"); delay(20000); // Activar GPS
  SerialDatosGPS(); // Lee los datos GPS
  Serial.println("----GPS Activado----"); delay(500); // Mensaje
  DatosObtenidosGPS(); // Obtiene datos GPS correctos
  proA7.println("AT+GPS=0"); delay(500); // Desactivar GPS
  digitalWrite(p_mux, LOW); // Cambia MUX al serial
  Serial.println("----GPS Desactivado----"); delay(500);
  digitalWrite(ledGPSon, LOW); // Desactiva ledGPS

  Serial.println("-------SISTEMA FUNCIONANDO-------");
  delay(2000);
}
