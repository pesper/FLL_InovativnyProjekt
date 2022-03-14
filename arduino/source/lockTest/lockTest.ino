void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
    delay(1500);
  }

void loop() {
  digitalWrite(2, HIGH);
  Serial.print("off");
  Serial.println();
  delay(2000);
  digitalWrite(2, LOW);
  Serial.print("on");
  Serial.println();
  delay(2000);
  }
