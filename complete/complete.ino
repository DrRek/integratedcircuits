/*
   GSMSimHTTP Example

   GSMSim_HTTP.ino

   By Erdem ARSLAN
   Version: v.2.0.1

   The MIT License (MIT)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/


/*
  ### Example Serial Output ###

  Set Phone Function... 1
  is Module Registered to Network?... 1
  Signal Quality... 14
  Operator Name... Turk Telekom
  Connect GPRS... 1
  Get IP Address... xxx.xxx.xxx.xxx
  Get... METHOD:GET|HTTPCODE:200|LENGTH:30
  Get with SSL and read returned data... METHOD:GET|HTTPCODE:200|LENGTH:30|DATA:This test data return from GET
  Post... METHOD:POST|HTTPCODE:200|LENGTH:54
  Post with SSL and read returned data... METHOD:POST|HTTPCODE:200|LENGTH:54|DATA:This test data return from POST.<br>Hello Erdem Arslan
  Close GPRS... 1

*/

#include <GSMSimHTTP.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Narcoleptic.h>

// You can use any Serial interface. I recommended HardwareSerial. Please use the library with highiest baudrate.
// In examples, i used HardwareSerial. You can change it anymore.


#define RXpinGPS 10              //this is the pin that the Arduino will use to receive data from the GPS
#define TXpinGPS 11              //this is the pin that the Arduino can use to send data (commands) to the GPS - not used

//#define RESET_PIN 10 // you can use any pin.
SoftwareSerial serialSim(8, 7);
SoftwareSerial serialGPS(RXpinGPS, TXpinGPS);

static volatile int num = 0;

GSMSimHTTP http(serialSim);//, RESET_PIN); // GSMSimHTTP inherit from GSMSimGPRS. You can use GSMSim and GSMSimGPRS methods with it.
TinyGPSPlus gps;

void send_to_server(String data) {
  serialSim.begin(9600); // If you dont change module baudrate, it comes with auto baudrate.
  while (!serialSim) {
    ;
  }

  // Init module...
  http.init(); // use for init module. Use it if you dont have any valid reason.

  Serial.print("Set Phone Function... ");
  Serial.println(http.setPhoneFunc(1));
  delay(1000);

  Serial.print("is Module Registered to Network?... ");
  Serial.println(http.isRegistered());
  delay(1000);

  Serial.print("Signal Quality... ");
  Serial.println(http.signalQuality());
  delay(1000);

  Serial.print("Operator Name... ");
  Serial.println(http.operatorNameFromSim());
  delay(1000);

  Serial.println("GPRS Init... ");
  http.gprsInit("TM"); // Its optional. You can set apn, user and password with this method. Default APN: "internet" Default USER: "" Default PWD: ""
  delay(1000);

  Serial.print("Connect GPRS... ");
  Serial.println(http.connect());
  delay(1000);

  Serial.print("Get... ");
  Serial.println(http.get("http://webhook.site/55c8ef2a-2642-4068-aba0-50e34aa27559?" + data));
  delay(1000);

  // Use your Serial interface...
  while (serialSim.available()) {
    String buffer = "";
    buffer = serialSim.readString();
    num = num + 1;
    Serial.print(num);
    Serial.print(". ");
    Serial.println(buffer);
    delay(1000);
  }
}

String get_position() {
  serialGPS.begin(9600);
  while (!serialSim) {
    ;
  }

  while (serialGPS.available()) {
    gps.encode(serialGPS.read());
  }
  if (gps.location.isUpdated()) {
    Serial.print("Satellite Count: ");
    Serial.println(gps.satellites.value());
    Serial.print("Location: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Speed MPH: ");
    Serial.println(gps.speed.mph());
    Serial.print("Altitude Feet: ");
    Serial.println(gps.altitude.feet());
    Serial.println("");
  }
  return "posizione ok";
}

void setup() {
  Serial.begin(9600); // Serial for debug...
  //get_position();
  send_to_server("hello");
}

void loop() {
  // put your main code here, to run repeatedly:
  Narcoleptic.delay(500); 
}
