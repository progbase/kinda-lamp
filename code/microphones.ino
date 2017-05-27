//const int micPin = A0; // задаём пин, куда подключён микрофон 
const int micPin1 = A1; 
const int micPin2 = A2;
void setup() { 
  Serial.begin(9600); // инициализация послед. порта 
} 
  
  void loop() { 
  //int central = analogRead(micPin) * 5.0 / 1024.0 * 1000.0; 
  int left = analogRead(micPin1);
  int right = analogRead(micPin2);
  //if(mv < 4900 || sv < 4900) { 
    ///Serial.print( "right :"); 
    //Serial.println(right); 
    Serial.print( "left :"); 
    Serial.println( left ); 
    
    if(left < 500)
    {
      
    Serial.print( "left :"); 
    Serial.println( left ); 
    
while(1);
    }
//    Serial.print( "left - right :"); 
//    Serial.println( right - left); 
    delay(50); 
//} 
//delay(100); 
// выводим в порт 
}
