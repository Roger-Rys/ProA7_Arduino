/*******FUNC DATOS_GPS********************************************************/
String SerialDatosGPS() {
  digitalWrite(p_mux, HIGH); // Cambia MUX al modo SerialDatosGPS

  while (proA7.available()) {
    GPS.encode(proA7.read());
  }
  delay(50);
  if (GPS.location.isUpdated()) {
    Serial.print("LAT="); Serial.println(GPS.location.lat(), 6); 
    Serial.print("LNG="); Serial.println(GPS.location.lng(), 6); 
    delay(2000);
  }

  return "&field1=" + String(GPS.location.lat(), 6) + "&field2=" + String(GPS.location.lng(), 6);

}
