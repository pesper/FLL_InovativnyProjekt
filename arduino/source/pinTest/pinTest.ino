int startPin = 18;
int endPin = 22; //+1

void setup(){
  for (int i = startPin; i < endPin; i++) {
    pinMode(i, INPUT);
    }
  Serial.begin(9600);
  Serial.print("PinTest ready");
  Serial.println();
}

void loop(){
  for (int i = startPin; i < endPin; i++) {
    if (digitalRead(i) == 1) {
      Serial.print("Button " + String(i) + " state: " + digitalRead(i));
      Serial.println();
      }
    
     delay(10);
   }
   Serial.println();
   delay(5000);
}
