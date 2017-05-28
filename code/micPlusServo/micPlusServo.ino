#include <Servo.h>

const int micPin = A0; // задаём пин, куда подключён микрофон 
const int micPin1 = A1; 
const int micPin2 = A2;


Servo servo;

void setup() { 
  Serial.begin(9600); // инициализация послед. порта

  servo.attach(10);
  servo.write(90);
  servo.detach();
} 
  
  void loop() { 
  int micro = 0;
  int left = analogRead(micPin1);
//  int right = analogRead(micPin2);
  int central = analogRead(micPin);
  if(left < 500) {
      
      Serial.print(  "left :");
      Serial.println(left);
      micro = 1;
      servo.attach(10);
      servo.write(40);
      servo.detach();
      delay(500);

  }
//  if(right < 500)
//  {
//      
//      Serial.print(  "right :");
//      Serial.println(right);
//      micro = 2;
//      servo.attach(10);
//      servo.write(140);
//      servo.detach(10);
//      delay(500);
//
//  }
  
  if(central < 500) 
  
  {
    
      micro = 3;
      Serial.print(  "central :");
      Serial.println(central);
      servo.attach(10);
      servo.write(90);
      servo.detach();
      delay(500);
  }

}
