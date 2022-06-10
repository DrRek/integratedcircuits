#include "mygps.h"

SoftwareSerial gps_serial(RECEIVE_FROM_GPS, SEND_TO_GPS);
TinyGPSPlus gps;

void init_gps(){
  pinMode (SWITCH_ON_GPS, OUTPUT);
  digitalWrite(SWITCH_ON_GPS, LOW);
}

void get_gps_coordinates(double* lat, double* lng){
  Serial.println("Accendo il GPS");
  digitalWrite(SWITCH_ON_GPS, HIGH);

  //inizio la comunicazione
  Serial.println("In attesa della porta seriale");
  gps_serial.begin(9600);
  while(!gps_serial);

  //get raw data
  Serial.println("Attendo la posizione");
  Serial.println("--DATI RAW GPS--");
  while(!gps.location.isUpdated()){
    while (gps_serial.available()){
      char c = gps_serial.read();
      Serial.print(c);
      gps.encode(c);
    }
    delay(1);
  }
  Serial.println("\n--FINE DATI RAW GPS--");

  //setto i valori di ritorno
  *lat = gps.location.lat();
  *lng = gps.location.lng();

  Serial.println("Spengo il GPS");
  digitalWrite(SWITCH_ON_GPS, LOW);

  return;
}
