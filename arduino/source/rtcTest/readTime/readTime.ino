    /* 
Modified on Nov 25, 2020
Modified by MehranMaleki from Arduino Examples
Home
*/


// CONNECTIONS:
// DS1302 CLK/SCLK --> 5
// DS1302 DAT/IO --> 4
//int clk = 5;
//int dat = 4;
//int rst_cd = 2;
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND



int clk = 11;
int dat = 10;
int rst_cd = 9;

#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(dat,clk,rst_cd); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () {
  
digitalWrite (13, HIGH); // output 5V for VCC
digitalWrite (12, LOW); // ground set to 0V
pinMode (12, OUTPUT); // turn on GND pin first (important!)
pinMode (13, OUTPUT); // turn on VCC power
delay(100); // short delay to let chip power up
    Serial.begin(9600);
    Rtc.Begin();

}

void loop () {
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    delay(5000); // five seconds
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Day(),
            dt.Month(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
