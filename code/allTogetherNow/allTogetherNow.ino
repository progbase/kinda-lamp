#include <Wire.h>
#include <Servo.h>
#include <BH1750FVI.h>
#include <CapacitiveSensor.h>

#define range 500

#define OFF 0
#define MED 6
#define MAX 50
#define distort 5
#define p1Act (key1_1 || key1_2 || key1_3)
#define p2Act (key2_1 || key2_2 || key2_3)

const int led1 = 9; 
const int led2 = 11; 
int servoPosition = 90;
double brightness = 0;
const int micPin = A0;
const int micPin1 = A1; 
const int micPin2 = A2;
bool thisGlobalMode = true;
long r1, r2, r3, r4, r5, r6;
double deltaBrightness = 10;
const double maxLux = 12000;
int curr9 = OFF, curr11 = OFF;
int state9 = OFF, state11 = OFF;
const double maxBrightness = 255;
double prevBrightness = brightness;

CapacitiveSensor cs_1_1 = CapacitiveSensor(12, 2); 
CapacitiveSensor cs_1_2 = CapacitiveSensor(12, 3); //50%
CapacitiveSensor cs_1_3 = CapacitiveSensor(12, 4); //100%
//REGULATE COLORS' INTENSITIES (2 PANEL)
CapacitiveSensor cs_2_1 = CapacitiveSensor(12, 5); //white (Wh)
CapacitiveSensor cs_2_2 = CapacitiveSensor(12, 6); //50/50 (Wh+Ye)
CapacitiveSensor cs_2_3 = CapacitiveSensor(12, 7); //yelOFF (Ye)


BH1750FVI LightSensor;
Servo servo;

void setup() { 
  Setup_Lightness();
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  cs_1_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  r1 = range + cs_1_1.capacitiveSensor(30);
  r2 = range + cs_1_2.capacitiveSensor(30);
  r3 = range + cs_1_3.capacitiveSensor(30);
  r4 = range + cs_2_1.capacitiveSensor(30);
  r5 = range + cs_2_2.capacitiveSensor(30);
  r6 = range + cs_2_3.capacitiveSensor(30);
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
  if (thisGlobalMode)
  {
    Brightness_handDrivenMode();
  }
  else 
  {
    Brightness_automaticRegulation ();
  }
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

void Brightness_handDrivenMode(void){
  
  if (curr9 >= (state9 - distort) && curr9 <= (state9 + distort) && curr11 >= (state11 - distort) && curr11 <= (state11 + distort)) {
  curr9 = state9;
  curr11 = state11;
  long _p1_k1 = cs_1_1.capacitiveSensor(30);
  long _p1_k2 = cs_1_2.capacitiveSensor(30);
  long _p1_k3 = cs_1_3.capacitiveSensor(30);
  long _p2_k1 = cs_2_1.capacitiveSensor(30);
  long _p2_k2 = cs_2_2.capacitiveSensor(30);
  long _p2_k3 = cs_2_3.capacitiveSensor(30);
  
  bool key1_1, key1_2, key1_3, key2_1, key2_2, key2_3;
  
  key1_1 = (_p1_k1 > r1);
  key1_2 = (_p1_k2 > r2);
  key1_3 = (_p1_k3 > r3);
  key2_1 = (_p2_k1 > r4);
  key2_2 = (_p2_k2 > r5);
  key2_3 = (_p2_k3 > r6);
  
  
  bool change = p1Act && p2Act;
  
  //if both panels are active we gonna change the mode!
  
  if (change) {
  thisGlobalMode = !thisGlobalMode;
  }
  
      if (thisGlobalMode) {
      if (key1_1) {
        state9 = OFF;
        state11 = OFF;
      } 
      else if (key1_2) {
      if (state9 == OFF && state11 == OFF) {
        state9 = MED;
        state11 = MED;
      } 
      else {
        if (state11 == MAX) {
          state11 = MED;
        }
        if (state9 == MAX) {
          state9 = MED;
        }
      }
      } else if (key1_3) {
        if (state9 != MAX && state11 != MAX) {
          state9 = MAX;
          state11 = MAX;
        } else {
          if (state11 == MED) {
            state11 = MAX;  
          }
          if (state9 == MED) {
            state9 = MAX;
          }
        }
      } else if (key2_1) {
      if (state9 == MED || state11 == MED) {
        state11 = MED;
      } 
      else if (state9 == MAX || state11 == MAX) {
        state11 = MAX;
      }
      } else if (key2_2) {
        if (state9 == MED || state11 == MED) {
          state9 = MED;
          state11 = MED;
        } 
        else if (state9 == MAX || state11 == MAX) {
          state9 = MAX;
          state11 = MAX;
        }
      } 
      else if (key2_3) {
        if (state9 == MED || state11 == MED) {
          state9 = MED;
        } 
        else if (state9 == MAX || state11 == MAX) {
          state9 = MAX;
        }
      }
  } 
  else {
    Serial.print("auto: MODE ACTIVE");
  }
  delay(200);
  Serial.print("1_1: ");
  Serial.print(key1_1);
  Serial.print(" , 2_1: ");
  Serial.print(key2_1);
  Serial.print('\n');
  
  Serial.print("1_2: ");
  Serial.print(key1_2);
  Serial.print(", 2_2: ");
  Serial.print(key2_2);
  Serial.print('\n');
  
  Serial.print("1_3: ");
  Serial.print(key1_3);
  Serial.print(", 2_3: ");
  Serial.print(key2_3);
  Serial.print('\n');
  Serial.print('\n');
  } else {
  //(ps: distortion = 5)
  #define step distort
  //for pin 9
  smooth set
  
  if (curr9 < state9) {
  curr9 += step;
  }
  if (curr9 > state9) {
  curr9 -= step;
  }
  //for pin 11 smooth set
  if (curr11 < state11) {
  curr11 += step;
}
  if (curr11 > state11) {
  curr11 -= step;
  }
  }
  
  delay(800);
  digitalWrite(9, curr9);
  digitalWrite(11, curr11);
  
  Serial.print("curr9: ");
  Serial.print(curr9);
  Serial.print(", state9: ");
  Serial.print(state9);
  Serial.print('\n');
  
  Serial.print("curr11: ");
  Serial.print(curr11);
  Serial.print(", state11: ");
  Serial.print(state11);
  Serial.print('\n');
  Serial.print('\n');
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
