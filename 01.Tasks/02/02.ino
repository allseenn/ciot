// C++ code
//
int red = 2;
int yellow = 3;
int green = 4;
int red2 = 9;
int yellow2 = 10;
int green2 = 11;
int button = 7;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(button, INPUT);
}

void loop()
{
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(red2, HIGH);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
  
  if (digitalRead (button)==HIGH)
               {
                 digitalWrite (red2, LOW);
                 digitalWrite (yellow2, HIGH);
                 digitalWrite (green2, LOW);
                 digitalWrite (red, LOW);
                 digitalWrite (yellow, HIGH);
                 digitalWrite (green, LOW);
                 delay(3000);
                 
           digitalWrite (red2, LOW);
                 digitalWrite (yellow2, LOW);
                 digitalWrite (green2, HIGH);
                 digitalWrite (red, HIGH);
                 digitalWrite (yellow, LOW);
                 digitalWrite (green, LOW);
                 delay(3000);
    
           digitalWrite (red2, LOW);
                 digitalWrite (yellow2, HIGH);
                 digitalWrite (green2, LOW);
                 digitalWrite (red, LOW);
                 digitalWrite (yellow, HIGH);
                 digitalWrite (green, LOW);
                 delay(3000);
               }
}
