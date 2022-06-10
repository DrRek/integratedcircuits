#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define SEND_TO_GPS 11
#define RECEIVE_FROM_GPS 10
#define SWITCH_ON_GPS 3

void init_gps();
void get_gps_coordinates(double* lat, double* lng);
