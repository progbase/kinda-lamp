#include <Wire.h>
#include <BH1750FVI.h>
#include <CapacitiveSensor.h>

#define OFF 0
#define MED 6
#define MAX 50
#define range 300
#define distort 5
#define step distort

const int led1 = 9; 
const int led2 = 11; 
double brightness = 0;
bool thisGlobalMode = true; 
long r1, r2, r3, r4, r5, r6;
double deltaBrightness = 10;
const double maxLux = 12000;
int curr9 = OFF, curr11 = OFF;
const double maxBrightness = 255;
double prevBrightness = brightness;
bool key1_1, key1_2, key1_3, key2_1, key2_2, key2_3;
int state8 = LOW, state9 = LOW, state10 = LOW, state11 = LOW;

CapacitiveSensor cs_1_1 = CapacitiveSensor(12, 2); 
CapacitiveSensor cs_1_2 = CapacitiveSensor(12, 3); //50%
CapacitiveSensor cs_1_3 = CapacitiveSensor(12, 4); //100%
//REGULATE COLORS' INTENSITIES (2 PANEL)
CapacitiveSensor cs_2_1 = CapacitiveSensor(12, 5); //white (Wh)
CapacitiveSensor cs_2_2 = CapacitiveSensor(12, 6); //50/50 (Wh+Ye)
CapacitiveSensor cs_2_3 = CapacitiveSensor(12, 7); //yelOFF (Ye)

BH1750FVI LightSensor;

#define p1Act (key1_1 || key1_2 || key1_3)
#define p2Act (key2_1 || key2_2 || key2_3)

void setup() { 
  Setup_Sensor();
  Setup_Lightness();
  Serial.begin(9600);
} 
  
void loop() { 
  Serial.println("____________________");
  bool change = p1Act && p2Act;
  if (thisGlobalMode)
    Brightness_handDrivenMode();
  else 
    Brightness_automaticRegulation ();
  if (change)
    thisGlobalMode = !thisGlobalMode;
  if (cs_1_2.capacitiveSensor(30) > r2)
    thisGlobalMode = !thisGlobalMode;
}

void Brightness_handDrivenMode(void){
  if (curr9 >= (state9 - distort) && 
      curr9 <= (state9 + distort) && 
      curr11 >= (state11 - distort) && 
      curr11 <= (state11 + distort)) {
    curr9 = state9;
    curr11 = state11;
    long _p1_k1 = cs_1_1.capacitiveSensor(30);
    long _p1_k2 = cs_1_2.capacitiveSensor(30);
    long _p1_k3 = cs_1_3.capacitiveSensor(30);
    long _p2_k1 = cs_2_1.capacitiveSensor(30);
    long _p2_k2 = cs_2_2.capacitiveSensor(30);
    long _p2_k3 = cs_2_3.capacitiveSensor(30);
    
    key1_1 = (_p1_k1 > r1);
    key1_2 = (_p1_k2 > r2);
    key1_3 = (_p1_k3 > r3);
    key2_1 = (_p2_k1 > r4);
    key2_2 = (_p2_k2 > r5);
    key2_3 = (_p2_k3 > r6);
    if (cs_1_2.capacitiveSensor(30) > r2)
      thisGlobalMode = false;
    if (key1_1) {
      state8 = LOW;
      state10 = LOW;
      state9 = LOW;
      state11 = LOW;
    } else if (key1_2) {
  if (state8 == LOW && state9 == LOW && state10 == LOW && state11 == LOW) {
          state8 = HIGH;
          state10 = HIGH;
        } else {
          if (state10 == HIGH || state11 == HIGH) {
            state10 = HIGH;
            state11 = LOW;
          }
          if (state8 == HIGH || state9 == HIGH) {
            state8 = HIGH;
            state9 = LOW;
          }
  }
    }  else if (key1_3) {
      if (state8 == LOW && state9 == LOW && state10 == LOW && state11 == LOW) {
        state9 = HIGH;
        state11 = HIGH;
      } else {
        if (state10 == HIGH || state11 == HIGH) {
          state10 = LOW;
          state11 = HIGH;
        }
        if (state8 == HIGH || state9 == HIGH) {
          state8 = LOW;
          state9 = HIGH;
        }
      }
    } else if (key2_1) {
      if (state8 == HIGH || state10 == HIGH) {
        state8 = LOW;
        state9 = LOW;
        state10 = HIGH;
        state11 = LOW;
      } else if (state9 == HIGH || state11 == HIGH) {
        state8 = LOW;
        state9 = LOW;
        state10 = LOW;
        state11 = HIGH;
      }
    } else if (key2_2) {
      if (state8 == HIGH || state10 == HIGH) {
        state8 = HIGH;
        state9 = LOW;
        state10 = HIGH;
        state11 = LOW;
      } else if (state9 == HIGH || state11 == HIGH) {
        state8 = LOW;
        state9 = HIGH;
        state10 = LOW;
        state11 = HIGH;
      }
    } else if (key2_3) {
      if (state8 == HIGH || state10 == HIGH) {
        state8 = HIGH;
        state9 = LOW;
        state10 = LOW;
        state11 = LOW;
      } else if (state9 == HIGH || state11 == HIGH) {
        state8 = LOW;
        state9 = HIGH;
        state10 = LOW;
        state11 = LOW;
      }
    }
//  } else {
//    //todo: automatic regulatings here in future //note: yes, I can boogie
//    state8 = LOW;
//    state10 = LOW;
//    state9 = HIGH;
//    state11 = HIGH;
//  }
  if (state8 == LOW) {
    digitalWrite(8, state8);
    digitalWrite(10, state10);
  } else {
    digitalWrite(10, state10);
    digitalWrite(8, state8);
  }
  if (state9 == LOW) {
    digitalWrite(9, state9);
    digitalWrite(11, state11);
  } else {
    digitalWrite(11, state11);
    digitalWrite(9, state9);
  }

   //  delay(200); // FOR WHAT?
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
  } 
  else {
    if (curr9 < state9)
      curr9 += step;
    if (curr9 > state9)
      curr9 -= step;
    if (curr11 < state11)
      curr11 += step;
    if (curr11 > state11)
      curr11 -= step;
  }
  
 // delay(800); 
  digitalWrite(led1, curr9);
  digitalWrite(led2, curr11);
  
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

void Brightness_automaticRegulation (){
  uint16_t lux = LightSensor.GetLightIntensity();
  brightness = maxBrightness - lux * maxBrightness / maxLux;
  if (deltaBrightness > 5)
  {
    if (brightness > 0){
      if (brightness > maxBrightness){
        analogWrite(led1, maxBrightness); 
        analogWrite(led2, maxBrightness);
      }
      else{
        analogWrite(led1, brightness); 
        analogWrite(led2, brightness);
      }
      Serial.print("Light: ");
      Serial.println(lux, DEC);
      Serial.print("Brightness: ");
      Serial.println(brightness, DEC);
      Serial.println("");
    } 
    else{
      analogWrite(led1, 0); 
      analogWrite(led2, 0);
    }
 }
 deltaBrightness = abs(prevBrightness - brightness);
 prevBrightness = brightness;  
}

void Setup_Lightness(void){
  LightSensor.begin(); 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  LightSensor.SetAddress(0x23);// 0x5C или 0x23 
  LightSensor.SetMode(Continuous_H_resolution_Mode);
}

void Setup_Sensor(void){
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  cs_1_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
  r1 = range + cs_1_1.capacitiveSensor(30);
  r2 = range + cs_1_2.capacitiveSensor(30);
  r3 = range + cs_1_3.capacitiveSensor(30);
  r4 = range + cs_2_1.capacitiveSensor(30);
  r5 = range + cs_2_2.capacitiveSensor(30);
  r6 = range + cs_2_3.capacitiveSensor(30);
}
