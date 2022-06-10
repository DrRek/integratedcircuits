#include "mygprs.h"

GPRS gprs;

void init_gprs(){
  pinMode (SWITCH_ON_GPRS, OUTPUT);
  digitalWrite(SWITCH_ON_GPRS, LOW);
}

void send_http_message(char* data){
  //accendo il GPS
  digitalWrite(SWITCH_ON_GPRS, HIGH);

  Serial.println("GPRS - HTTP Connection Test...");  
  //gprs.preInit();
  while(0 != gprs.init()) {
     delay(1000);
     Serial.println("init error");
  }  
  while(!gprs.join("TM")) {  //change "cmnet" to your own APN
      Serial.println("Error joining GPRS network");
      delay(2000);
  }
  // successful DHCP
  Serial.print("IP Address is ");
  Serial.println(gprs.getIPAddress());
  
  Serial.println("Init success, connecting to exploreembedded.com ...");
  
  if(0 == gprs.connectTCP("webhook.site", 80)) {
      Serial.println("Successfully connected to exploreembedded.com!");
  }else{
      Serial.println("connect error");
      while(1);
  }

  Serial.println("waiting to fetch...");
  if(0 == gprs.sendTCPData(data))
  {      
    gprs.serialDebug();
  }
  
  gprs.closeTCP();
  gprs.shutTCP();
  Serial.println("close");

  digitalWrite(SWITCH_ON_GPRS, LOW);
}
