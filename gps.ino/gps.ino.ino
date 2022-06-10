#define RXpin 10              //this is the pin that the Arduino will use to receive data from the GPS
#define TXpin 11              //this is the pin that the Arduino can use to send data (commands) to the GPS - not used

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial serial_connection(RXpin, TXpin);
TinyGPSPlus gps;

void loop(){
  while (serial_connection.available()){
    char c = serial_connection.read();
    //Serial.print(c);
    gps.encode(c);
  }
  //Serial.println();
  if(gps.location.isUpdated()){
    Serial.print("Satellite Count: ");
    Serial.println(gps.satellites.value());
    Serial.print("Location: ");
    Serial.print(gps.location.lat(),6);
    Serial.print(",");
    Serial.println(gps.location.lng(),6);
    Serial.print("Speed MPH: ");
    Serial.println(gps.speed.mph());
    Serial.print("Altitude Feet: ");
    Serial.println(gps.altitude.feet());
    Serial.println("");
  }
}


void setup(){
  pinMode (3, OUTPUT);
  digitalWrite(3, HIGH);
  
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.println("GPS Starting");
}
