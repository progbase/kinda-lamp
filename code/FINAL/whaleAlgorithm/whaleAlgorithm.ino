#include <Wire.h>
#include <Servo.h>

const int micPin = A0;
const int micPin1 = A1; 
const int micPin2 = A2;
int servoPosition = 90;

Servo servo;

void setup() { 
  Setup_Servo();
  Serial.begin(9600);
} 
  
void loop() { 
  Serial.println("____________________");
  Servo_turn(Servo_getRotationDirection());
}

void Setup_Servo(){
  servo.attach(10);
  for (int i = 0; i < 91; i++)
  {
    servo.write(i);
    delay(40);
  }
  servo.detach();
}

// returns 1 for left, 2 for right & 3 for center
int Servo_getRotationDirection(void){
  int left = analogRead(micPin1);
  int right = analogRead(micPin2);
  int central = analogRead(micPin);
  if(left < 500) // (left > right && left > center)
  {
      Serial.print("left: ");
      Serial.println(left);
      return 1;
      
  }
  else if(right < 500) // (left < right && right > center)
  {
      Serial.print("right: ");
      Serial.println(right);
      return 2;
  }
  else if(central < 500) // else if (left < center && right < center)
  
  {
      Serial.print("central: ");
      Serial.println(central);
      return 3;
  }  
}

void Servo_turn(int micro){
  servo.attach(10);
  if (micro == 1)
  {
    // turns to angle, which == 40
    for (int i = servoPosition - 1; i > 39; i--)
    {
      servo.write(i);
      delay(40);
    }
    servoPosition = 40;
  }
  else if (micro == 2)
  {
    // turns to angle, which == 140
    for (int i = servoPosition + 1; i < 141; i++)
    {
      servo.write(i);
      delay(40);
    }
    servoPosition = 140;
  }
  else
  {
    // turns to angle, which == 90
    if (servoPosition > 90)
    {
      for (int i = servoPosition - 1; i > 89; i--)
      {
        servo.write(i);
        delay(40);
      }
    }
    else if (servoPosition < 90)
    {
      for (int i = servoPosition + 1; i < 91; i++)
      {
        servo.write(i);
        delay(40);
      }
    }
    servoPosition = 90;
  }
  servo.detach();
  delay(100); // in Den's code here were 500 // *to try to delete this delay
}

