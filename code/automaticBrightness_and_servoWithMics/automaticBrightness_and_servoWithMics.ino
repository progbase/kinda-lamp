#include <Wire.h>
#include <Servo.h>
#include <BH1750FVI.h>

const int led1 = 9; 
const int led2 = 11; 
int servoPosition = 90;
double brightness = 0;
const int micPin = A0;
const int micPin1 = A1; 
const int micPin2 = A2;
double deltaBrightness = 10;
const double maxLux = 12000;
const double maxBrightness = 255;
double prevBrightness = brightness;

BH1750FVI LightSensor;
Servo servo;

void setup() { 
  Setup_Lightness();
  Serial.begin(9600);
  servo.attach(10);
  for (int i = 0; i < 91; i++)
  {
    servo.write(i);
    delay(40);
  }
  servo.detach();
} 
  
void loop() { 
  int micro = 0;
  int left = analogRead(micPin1);
  int right = analogRead(micPin2);
  int central = analogRead(micPin);
  Serial.println("____________________");
  Brightness_automaticRegulation ();
  if(left < 500) 
  {
      Serial.print("left: ");
      Serial.println(left);
      Servo_turn(1);
  }
  if(right < 500)
  {
      Serial.print("right: ");
      Serial.println(right);
      Servo_turn(2);
  }
  if(central < 500) 
  
  {
      Serial.print("central: ");
      Serial.println(central);
      Servo_turn(3);
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
  delay(100); // in Den's code here were 500
}

void Brightness_automaticRegulation (){
  uint16_t lux = LightSensor.GetLightIntensity();
  brightness = maxBrightness - lux * maxBrightness / maxLux;
  if (deltaBrightness > 5)
  {
    if (brightness > 0){
      if (brightness > maxBrightness){
        digitalWrite(led1, maxBrightness); 
        digitalWrite(led2, maxBrightness);
      }
      else{
        digitalWrite(led1, brightness); 
        digitalWrite(led2, brightness);
      }
      Serial.print("Light: ");
      Serial.println(lux, DEC);
      Serial.print("Brightness: ");
      Serial.println(brightness, DEC);
      Serial.println("");
    } 
    else{
      digitalWrite(led1, 0); 
      digitalWrite(led2, 0);
    }
 }
 deltaBrightness = abs(prevBrightness - brightness);
 prevBrightness = brightness;  
}

void Setup_Lightness(void){
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  LightSensor.begin(); 
  LightSensor.SetAddress(0x23);// 0x5C или 0x23 
  LightSensor.SetMode(Continuous_H_resolution_Mode);
}

