/*******FUNC COMUNICACION_SERIAL*****************************************/
void ComunicacionSerial() {
  
  digitalWrite(p_mux, LOW); // Cambia MUX al modo Seial
  
  ////////////////////////MODO SERIAL//////////////////////////////////
  serialA7();

  ///////SERIAL DE ARDUINO/////////
  while (Serial.available()) {
    proA7.write(Serial.read()); // Serial lee, Disp escribe
  } delay(50);
}
