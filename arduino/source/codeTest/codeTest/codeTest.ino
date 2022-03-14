void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  char teraz[20] = "28/02/2022";
  String code = "696969";
  validCode(code, teraz);
  delay(2000);
  Serial.println();
}

bool validCode(String code, char teraz[20]){
  char den[3];
  den[0] = teraz[0];
  den[1] = teraz[1];
  den[2] = '\0';
  String den_s = ( String(den[0])+String(den[1]) );
  int start = den_s.toInt();
        
  float value1 = start * 2;
  float value2 = start * 3;
  float value3 = start * 4;
  float value4 = start * 5;
  float  value5 = start * 6;
  float  value6 = start * 7;


        //oprava chybného výsledku

        do {
          value1 = value1 / 2;
        } while (value1 > 9);

        value1 = round(value1);

        do {
          value2 = value2 / 2;
        } while (value2 > 9);

        value2 = round(value2);

        do {
          value3 = value3 / 2;
        } while (value3 > 9);

        value3 = round(value3);

        do {
          value4 = value4 / 2;
        } while (value4 > 9);

        value4 = round(value4);

        do {
          value5 = value5 / 2;
        } while (value5 > 9);

        value5 = round(value5);

        do {
          value6 = value6 / 2;
        } while (value6 > 9);

        value6 = round(value6);


  int v1 = value1;
  int v2 = value2;
  int v3 = value3;
  int v4 = value4;
  int v5 = value5;
  int v6 = value6;

  
  String code_gen = String(v1)+String(v2)+String(v3)+String(v4)+String(v5)+String(v6 q);
  Serial.print(code_gen);
  if (code == code_gen) return true;
  return false; 
}
