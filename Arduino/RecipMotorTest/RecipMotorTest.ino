void setup()
{
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
}

void loop()
{
  digitalWrite(0, HIGH);
  delay(50);
  digitalWrite(0, LOW);
  delay(2000);
  
  digitalWrite(0, HIGH);
  delay(50);
  digitalWrite(0, LOW);
  delay(2000);

  digitalWrite(1, HIGH);
  delay(50);
  digitalWrite(1, LOW);
  delay(2000);

  digitalWrite(1, HIGH);
  delay(50);
  digitalWrite(1, LOW);
  delay(2000);
}
