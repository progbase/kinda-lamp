
#include <Servo.h>

Servo servo;
int pos = 0;
void setup() {
  servo.attach(10);
  pinMode(9, OUTPUT);
  pinMode (11, OUTPUT);
}

void loop() {
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  for (pos = 0; pos < 360; pos++)
  {
    if (pos <= 180)
    {
      servo.write(pos);
    }
    else 
    {
      servo.write(360 - pos);
    }
    if (pos % 100 == 0 && pos < 180)
    {
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
    }
    else if (pos % 100 == 0 && pos >= 180)
    {
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
    }
    delay(40);
    
  }
}
