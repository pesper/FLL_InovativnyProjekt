//First Lego League [FLL] - inovativny projekt 
//Program pre domaci balikobox




  // Arduino casovy modul
// pripojenia modulu: CLK -> pin 11; DAT -> pin 10; RST -> pin 9; VCC a GND v setup() {cez digitalne piny};
int clk = 11;
int dat = 10;
int rst = 9;

// kniznice pre komunikaciu s casovym modulom
#include <ThreeWire.h>  
#include <RtcDS1302.h>

// inicializacia spojenia
ThreeWire myWire(dat,clk,rst);
RtcDS1302<ThreeWire> Rtc(myWire);




  // Arduino klavesnica
//pripojenia modulu: podla standardu RJ45-T568B otocene (od hnedej po slabo oranzovu) s tym ze sa hnedy vodic vynecha a zapaja sa od pinu 53 kazdy dalsi vodic o 2 menej (51, 49,...) az po pin 41
// kniznica pre komunikaciu s klavesnicou
#include "Keypad.h"
 
const byte ROWS = 4; //4 riadky
const byte COLS = 3; //3 stlpce
char keys[ROWS][COLS] =
 {{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};

byte rowPins[ROWS] = {
  43, 53, 51, 47}; //pripojenie do riadkov
//1,  2,  3,  4
byte colPins[COLS] = {
  45, 41, 49}; // pripojenie do stlpcov
//1,  2,  3

// inicializacia klavesnica
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

  // Arduino displej
//pripojenia modulu: (MODRY KONIEC)SCL -> SCL, (ZELENY KONIEC)SDA -> SDA, (ORANZOVY KONIEC)VCC -> 5V, (ZLTY KONIEC)GND -> GND
// kniznice
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// inicializacia displeja
LiquidCrystal_I2C lcd(0x27,16,2);  //  0x27 pre 16 znakov a 2 riadky


void setup () {
  // Arduino casovy modul - pripojenie k prudu
  digitalWrite (13, HIGH); // output 5V for VCC
  digitalWrite (12, LOW); // ground set to 0V
  pinMode (12, OUTPUT); // turn on GND pin first (important!)
  pinMode (13, OUTPUT); // turn on VCC power
  // kratke oneskorenie len pre zicher
  delay(100); 

  // Arduino casovy modul - inicializacia
  Rtc.Begin();  
  
  // Arduino LCD inicializacia
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Balikobox");
  lcd.setCursor(1,1);
  lcd.print("ZS s MS Lokca");

  // arduino zamok/rele
  pinMode(2, OUTPUT);
  
  Serial.begin(9600);

}

#define countof(a) (sizeof(a) / sizeof(a[0]))
// premenne rozne ucely

bool awake = true;

// chybove hlasky
bool Error = false;
String ErrorMessage = ""; // chybová hláška do Serial Monitora
String ErrorMessageDisplay_sk = "Lutujeme, nastala chyba!";
String ErrorMessageDisplay_en = "We are sorry, an error occured!";


String code = "";
String code_previsouls = "";
int code_lenght = 0;
String code_master = "236632";
void loop () {
  RtcDateTime now = Rtc.GetDateTime(); // v premennej "teraz" je ulozeny aktualny cas
  if (!now.IsValid()){
    Error = true;
    ErrorMessage += "Chyba RTC";   
  }
  char teraz[20];
  snprintf_P(teraz, countof(teraz), PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
  now.Day(), now.Month(), now.Year(),
  now.Hour(), now.Minute(), now.Second() );
  char datum[11];
  snprintf_P(datum, countof(datum), PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
  now.Day(), now.Month(), now.Year());
  while (Error) {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(ErrorMessageDisplay_sk);
    lcd.setCursor(1,1);
    lcd.print(ErrorMessageDisplay_en);
    delay(20000);
    lcd.clear();
    delay(500);
    lcd.noBacklight();
  }
  while (awake) {
    char key = keypad.getKey();
    if (key != NO_KEY){
      if ( String(key) == "*") {
        if (code_lenght != 0  ) {
          if ( validCode(code, teraz) ) {
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print("Kod akceptovany");
            lcd.setCursor(1,1);
            lcd.print("otvaram");
            otvorVrata();
            delay(2000);
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print(datum);
          } else {
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print("Bol zadany");
            lcd.setCursor(1,1);
            lcd.print("nespravny kod");
            delay(2000);
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print(datum);
          }
          code = "";
          code_lenght = 0;
        }
      }
      else if ( String(key) == "#") {
        if (code_lenght > 0) {
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print(datum);
          lcd.setCursor(1,1);
          lcd.print("Reset");
          delay(1000);
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print(datum);
          code = "";
          code_lenght = 0;
        }
      } else if (code_lenght < 6) {
        code = code + String(key);
        code_lenght++;
      }
    }
    if (code != code_previsouls) {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(datum);
        lcd.setCursor(1,1);
        lcd.print(code);
        code_previsouls = code;
    }
  }



    
    delay(5000); // tu by sa program nemal dostať
}

// Citas?

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

  

  String code_gen = String(v1)+String(v2)+String(v3)+String(v4)+String(v5)+String(v6);
  Serial.print(code_gen);
  if (code == code_gen || code == code_master) return true;
  return false; 
}

void otvorVrata(){
  digitalWrite(2, HIGH);
  delay(3000);
  digitalWrite(2, LOW);
  delay(200);
}
