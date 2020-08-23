bool TCP_GPRS() { //voil TCP_GPRS()
  escribirComando("AT+CREG?", 2000, true); //Query network registration
  delay(100);
  escribirComando("AT+CGATT=1", 6000, true);
  delay(100);
  escribirComando("AT+CGDCONT=1,\"IP\",\"CMNET\"", 2000, true); //setting PDP parameter //PDP - The process on the Security Gateway responsible for collecting and sharing identities.(URL= https://sc1.checkpoint.com/documents/R76/CP_R76_CLI_WebAdmin/66477.htm)
  delay(100);
  escribirComando("AT+CGACT=1,1", 10000, true); //Activate PDP, open Internet service
  delay(100);
  bool confirmar = escribirComando("AT+CIPSTART=TCP,api.thingspeak.com,80", 11000, true);
  if(confirmar){
    return true; 
  }
  return false;   
}
