// trafic light
//
int red = 2;
int yellow = 3;
int green = 4;
void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void SwitchLight(int led,int time)
{
  digitalWrite(led, HIGH);
    delay(time);
    digitalWrite(led, LOW);
}

void ToggleLight(int led, int time)
{
  for (int i =1; i<4; i++)
  {
    delay(time); 
    digitalWrite(led, HIGH);
    delay(time); 
    digitalWrite(led, LOW);
  }
}

void loop()
{
  SwitchLight(red, 3000);
  SwitchLight (yellow, 1500);
  SwitchLight (green, 3000);
  ToggleLight(green,500);
  SwitchLight (yellow, 1500);
}
