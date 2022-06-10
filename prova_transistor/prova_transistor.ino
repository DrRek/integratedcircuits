const int transistor = 2;

void setup()
{
  pinMode (transistor, OUTPUT);
}

void loop()
{
  digitalWrite (transistor, HIGH); //npn -> così apro il circuito e tolgo la corrente
  delay(20000);
  digitalWrite (transistor, LOW); //così -> metto la corrente chiudendo il circuito
  delay(20000);
}
