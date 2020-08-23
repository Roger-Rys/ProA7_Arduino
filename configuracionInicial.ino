/*******FUNC CONFIGURACION_INIC*******************************************************/
void configuracionInicial() {
  digitalWrite(p_mux, LOW); // Cambia MUX al serial
  digitalWrite(p_PWRKEY, HIGH); delay(3000); // 2 seg para Activar la red GSM
  digitalWrite(p_PWRKEY, LOW); delay(2000); //10seg
  Serial.println("PWR_KEY Activado"); // Mensaje que la red esta activada
  
  while (escribirComando("AT", 3000, false) != true) { // Envia AT y espera respuesta OK
    Serial.println("--desconectado a A7--");
    digitalWrite(p_PWRKEY, HIGH); delay(3000); // 3 seg para Activar la red GSM
    digitalWrite(p_PWRKEY, LOW); 
  }
 
  Serial.println("---Conectado---");
  delay(2000);
}
