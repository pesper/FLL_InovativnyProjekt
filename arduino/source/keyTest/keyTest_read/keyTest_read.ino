#include "Keypad.h"



const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] =
 {{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
  


byte rowPins[ROWS] = {
  43, 53, 51, 47}; //connect to the row pinouts of the keypad
//1,  2,  3,  4
byte colPins[COLS] = {
  45, 41, 49}; // connect to the column pinouts of the keypad
//1,  2,  3


int count=0;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  Serial.begin(9600);
  Serial.print("Serial working!");
  Serial.println();
}

void loop()
{
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    Serial.print(key);
    Serial.println();
  }
}
