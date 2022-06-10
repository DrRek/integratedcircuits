#include "mygps.h"
#include "mygprs.h"

void setup() {
  Serial.begin(9600);
  init_gps();
  init_gprs();

  double lat, lng;
  get_gps_coordinates(&lat, &lng);
  Serial.println(lat);
  Serial.println(lng);

  send_http_message("GET /55c8ef2a-2642-4068-aba0-50e34aa27559?test=seeduino2 HTTP/1.0\r\n\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:

}
