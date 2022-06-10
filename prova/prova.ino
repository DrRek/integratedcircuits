#include <GSMSim.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(8,7);

int readBuffer(int count, unsigned int timeOut) {
    int i = 0;
    unsigned long timerStart;
    timerStart = millis();
    while (1) {
        while (Serial1.available()) {
            char c = Serial1.read();
            Serial.print((char)c);
            i++;
            if (i > count - 1) {
                break;
            }
        }
        if (i > count - 1) {
            break;
        }
        if (millis() - timerStart > 1000 * timeOut) {
            break;
        }
    }
    delay(500);
    while (Serial1.available()) {  // display the other thing..
        Serial.print(Serial1.read());
    }
    return 0;
}

void setup() {
  Serial1.begin(9600); // If you dont change module baudrate, it comes with auto baudrate.

  Serial.begin(9600); // Serial for debug...

  while(1){
  delay(5000);
  Serial.println("asd");

  Serial1.write("AT\r\n");

  readBuffer(64, 5);

  /*/ Use your Serial interface...
  if(Serial1.available()) {
    Serial.println(Serial1.readString());
  }*/
  }
}

void loop() {

}
