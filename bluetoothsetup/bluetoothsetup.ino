  //Controllare il BAUD RATE di upload quando lo scrivi nei comandi AT, tipo sulla uno è di 115200 https://42bots.com/resources/arduino-program-sketch-upload-speeds/

#include <SoftwareSerial.h>
SoftwareSerial HC05(2,3); 
void setup()
{
Serial.begin(9600);
Serial.println("Enter AT commands:");
HC05.begin(57600); //38400 for AT commands, 57600 otherwise
}
void loop()
{
  if (HC05.available())
    Serial.write(HC05.read());
  if (Serial.available())
    HC05.write(Serial.read());
}
