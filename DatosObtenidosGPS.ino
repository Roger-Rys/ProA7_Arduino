/*******ENCUENTRA DATOS DE LATITUD Y LONGITUD**************************************************/
void DatosObtenidosGPS() {
  for (byte i = 0; i <= esperaDatosGps; i++) {
    if (LAT != LAT_COMP && LNG != LNG_COMP) {
      LAT_COMP = LAT; LNG_COMP = LNG; // Se almacena los nuevos valores
      correccionLocacion++;
      if (correccionLocacion == 3) { //Se corrige los datos de locacion
        i = esperaDatosGps; // i va a valer "esperaDatosGps", para terminar secuencia
        Serial.println("----Valor GPS obtenidos----"); delay(3000);
      }
    }
    else if (i == 80) {
      proA7.println("AT+GPS=1"); delay(100);
    }
    else {
      SerialDatosGPS(); delay(500);
      Serial.println(i);
    }
  }
}
