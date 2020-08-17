void TCP_GPRS() {
  escribirComando("AT+CREG?", "OK", 5000); //Query network registration
  delay(100);
  escribirComando("AT+CGATT=1", "OK", 5000);
  delay(100);
  escribirComando("AT+CGDCONT=1,\"IP\",\"CMNET\"", "OK", 2000); //setting PDP parameter //PDP - The process on the Security Gateway responsible for collecting and sharing identities.(URL= https://sc1.checkpoint.com/documents/R76/CP_R76_CLI_WebAdmin/66477.htm)
  delay(100);
  escribirComando("AT+CGACT=1,1", "OK", 10000); //Activate PDP, open Internet service
  delay(100);
  escribirComando("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80", "OK", 10000);
  delay(100);
  escribirComando("AT+CIPSEND=5,\"12345\"", "OK", 2000); //Send string "12345"
  delay(100);
  escribirComando("AT+CIPCLOSE","OK", 2000);   //Close TCP
  delay(100);
  /*
    sendData("AT+CREG?",3000,DEBUG);
    sendData("AT+CGATT=1",1000,DEBUG);
    sendData("AT+CGDCONT=1,\"IP\",\"CMNET\"",1000,DEBUG);
    sendData("AT+CGACT=1,1",1000,DEBUG);
    sendData("AT+CIPSTART=\"TCP\",\"google.com\",80",3000,DEBUG);
    sendData("AT+CIPSEND=80",1000,DEBUG);
    sendData("GET http://www.google.com HTTP/1.0\r\n",100,DEBUG);
  */
}
