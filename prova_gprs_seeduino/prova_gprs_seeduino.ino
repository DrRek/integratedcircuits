/*
Sketch: GPRS HTTP Test
*/
#include <gprs.h>
#include <SoftwareSerial.h>

#define PIN_TX    7  // Has already exchanged TX and RX pins
#define PIN_RX    8

char http_cmd[] = "GET /55c8ef2a-2642-4068-aba0-50e34aa27559?test=seeduino HTTP/1.0\r\n\r\n";
char buffer[512];

GPRS gprs;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("GPRS - HTTP Connection Test...");  
  gprs.preInit();
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
  if(0 == gprs.sendTCPData(http_cmd))
  {      
    gprs.serialDebug();
  }
  
//  gprs.closeTCP();
//  gprs.shutTCP();
//  Serial.println("close");  
}

void loop() {    
    
}
