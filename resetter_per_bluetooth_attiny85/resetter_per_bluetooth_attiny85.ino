/**
 * Questo programma semplicemente quando vede che un segnale da LOW diventa HIGH sul pin 1 manda un impulso di un sec sul pin2
 */

#define INPUT_PIN 1
#define OUTPUT_PIN 2

bool shouldIWatch;

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, HIGH);
  shouldIWatch = true;
}

void loop() {
  if(digitalRead(INPUT_PIN) == LOW){
    shouldIWatch = true;
  } else {
    if(shouldIWatch){
      shouldIWatch = false;
      digitalWrite(OUTPUT_PIN, LOW);
      delay(100);
      digitalWrite(OUTPUT_PIN, HIGH);
    }
  }
  delay(500);
}
