/*******FUNC DATOS_GPS********************************************************/
void SerialDatosGPS() {
  digitalWrite(p_mux, HIGH); // Cambia MUX al modo SerialDatosGPS
  while (proA7.available()) {
    GPS.encode(proA7.read());
  }
  delay(50);
  if (GPS.location.isUpdated()) {
    Serial.print("LAT="); Serial.println(GPS.location.lat(), 6); // Obtiene datos de latitud
    LAT = GPS.location.lat(), 6;   
    Serial.print("LNG="); Serial.println(GPS.location.lng(), 6); // Obtiene datos de longitud
    LNG = GPS.location.lng(), 6;
    delay(2000);
  }
}
