// remote console light switcher
//
int incomingByte;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop()
{
  if (Serial.available ()>0)
  {
  incomingByte = Serial.read();
  Serial.write (incomingByte);
    
    
  if (incomingByte == '1')
    digitalWrite(2, HIGH);
  else if (incomingByte == '0')
    digitalWrite(2, LOW);
  }
}
