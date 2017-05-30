#include <Wire.h>
#include <BH1750FVI.h>

int i = 0;
int led1 = 9; 
int led2 = 11; 
double brightness = 0;
double maxBrightness = 255;
double maxLux = 12000;
double prevBrightness = brightness;
double deltaBrightness = 10;
//12000;

BH1750FVI LightSensor;
 
void setup() {   
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  LightSensor.begin();
  LightSensor.SetAddress(0x23);// 0x5C или 0x23
  LightSensor.SetMode(Continuous_H_resolution_Mode);
  Serial.begin(9600);
}
 //4734
 
void loop() {
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
    delay(500);
 }
 deltaBrightness = abs(prevBrightness - brightness);
 prevBrightness = brightness;
}
