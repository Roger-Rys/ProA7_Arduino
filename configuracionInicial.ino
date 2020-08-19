/*******FUNC CONFIGURACION_INIC*******************************************************/
void configuracionInicial() {
  digitalWrite(p_mux, LOW); // Cambia MUX al serial
  digitalWrite(p_PWRKEY, HIGH); delay(3000); // 2 seg para Activar la red GSM
  digitalWrite(p_PWRKEY, LOW); delay(2000); //10seg
  Serial.println("PWR_KEY Activado"); // Mensaje que la red esta activada
  
  while (escribirComando("AT", 5000, false) != true) { // Envia AT y espera respuesta OK
    Serial.println("----No conectado con modulo A7----");
    digitalWrite(p_PWRKEY, HIGH); delay(3000); // 3 seg para Activar la red GSM
    digitalWrite(p_PWRKEY, LOW); 
  }
  
  Serial.println("----Conectado con modulo A7----");
  Serial.println("-------FUNCIONANDO-------");
  delay(2000);
}
