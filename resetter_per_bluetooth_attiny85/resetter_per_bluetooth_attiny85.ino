#define INPUT_PIN 1
#define OUTPUT_PIN 2

bool shouldIWatchForLow;

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, HIGH);
  shouldIWatchForLow = true;
}

void loop() {
  if(digitalRead(INPUT_PIN) == HIGH){
    shouldIWatchForLow = true;
  } else {
    if(shouldIWatchForLow){
      shouldIWatchForLow = false;
      digitalWrite(OUTPUT_PIN, LOW);
      delay(100);
      digitalWrite(OUTPUT_PIN, HIGH);
    }
  }
}
