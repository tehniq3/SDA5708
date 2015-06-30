// niq_ro used SDA5708 docs from:
// http://blog.smue.org/archives/433-DBOX1-SDA5708-display-+-arduino.html
// http://www.sbprojects.com/knowledge/footprints/sda5708/index.php
// http://www.bralug.de/wiki/Display_SDA5708

// sketch by niq_ro from http://arduinotehniq.blogspot.com
// and http://nicuflorica.blogspot.ro
// actual version 1.2 in 30.06.2015

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include "DHT.h"
#define DHTPIN 8     // what pin we're connected to D8
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// if is just sensor:
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

// declaration for type of value
float t, h, t1;

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
// original sketck from http://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/
// add part with SQW=1Hz from http://tronixstuff.wordpress.com/2010/10/20/tutorial-arduino-and-the-i2c-bus/

// Dawn & Dusk controller. http://andydoz.blogspot.ro/2014_08_01_archive.html
// 16th August 2014 - (C) A.G.Doswell 2014

#include <Wire.h>
#include "RTClib.h" // from https://github.com/adafruit/RTClib
#include <Encoder.h> // from http://www.pjrc.com/teensy/td_libs_Encoder.html

RTC_DS1307 RTC; // Tells the RTC library that we're using a DS1307 RTC
Encoder knob(2,3); //encoder connected to pins 8 and 9 (and ground)

//the variables provide the holding values for the set clock routine
int setyeartemp; 
int setmonthtemp;
int setdaytemp;
int sethourstemp;
int setminstemp;
int setsecs = 0;
int maxday; // maximum number of days in the given month
int TimeOut = 10;
int TimeOutCounter;

// These variables are for the push button routine
int buttonstate = 0; //flag to see if the button has been pressed, used internal on the subroutine only
int pushlengthset = 2000; // value for a long push in mS
int pushlength = pushlengthset; // set default pushlength
int pushstart = 0;// sets default push value for the button going low
int pushstop = 0;// sets the default value for when the button goes back high

int knobval; // value for the rotation of the knob
boolean buttonflag = false; // default value for the button flag

const unsigned char font[752] PROGMEM ={

   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,    //letter Space


   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00000000,
   0b00100000,    //letter !

   0b01010000,
   0b01010000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,    //letter "

   0b01010000,
   0b01010000,
   0b11111000,
   0b01010000,
   0b11111000,
   0b01010000,
   0b01010000,    //letter #

   0b00100000,
   0b01111000,
   0b10100000,
   0b01110000,
   0b00101000,
   0b00110000,
   0b00100000,    //letter $

   0b11000000,
   0b11001000,
   0b00010000,
   0b00100000,
   0b01000000,
   0b10011000,
   0b00011000,    //letter %


   0b01000000,
   0b10100000,
   0b01000000,
   0b10100000,
   0b10010000,
   0b10001000,
   0b01110000,    //letter &

   0b00010000,
   0b00010000,
   0b00100000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,    //letter '

   0b00100000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b00100000,    //letter (

   0b00010000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00010000,    //letter )

/*
   0b00000000,
   0b10001000,
   0b01010000,
   0b11111000,
   0b01010000,
   0b10001000,
   0b00000000,    //letter *
*/

   0b00110000,
   0b01001000,
   0b01001000,
   0b00110000,
   0b00000000,
   0b00000000,
   0b00000000,    //letter o upper (degree) instead *

   0b00000000,
   0b00100000,
   0b00100000,
   0b11111000,
   0b00100000,
   0b00100000,
   0b00000000,    //letter +

   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b01000000,
   0b01000000,
   0b10000000,    //letter ,

   0b00000000,
   0b00000000,
   0b00000000,
   0b11111000,
   0b00000000,
   0b00000000,
   0b00000000,    //letter -

   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b11000000,
   0b11000000,   //letter .

   0b00000000,
   0b00001000,
   0b00010000,
   0b00100000,
   0b01000000,
   0b10000000,
   0b00000000,   //letter /

   0b01110000,
   0b10001000,
   0b10011000,
   0b10101000,
   0b11001000,
   0b10001000,
   0b01110000,   //letter 0

   0b00100000,
   0b01100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b01110000,   //letter 1

   0b01110000,
   0b00001000,
   0b00001000,
   0b01110000,
   0b10000000,
   0b10000000,
   0b11111000,   //letter 2

   0b11110000,
   0b00001000,
   0b00001000,
   0b01110000,
   0b00001000,
   0b00001000,
   0b11110000,   //letter 3

   0b00001000,
   0b00011000,
   0b00101000,
   0b01001000,
   0b11111000,
   0b00001000,
   0b00001000,   //letter 4

   0b11111000,
   0b10000000,
   0b10000000,
   0b11110000,
   0b00001000,
   0b10001000,
   0b01110000,   //letter 5

   0b01110000,
   0b10000000,
   0b10000000,
   0b11110000,
   0b10001000,
   0b10001000,
   0b01110000,   //letter 6

   0b11111000,
   0b00001000,
   0b00001000,
   0b00010000,
   0b00100000,
   0b01000000,
   0b10000000,   //letter 7

   0b01110000,
   0b10001000,
   0b10001000,
   0b01110000,
   0b10001000,
   0b10001000,
   0b01110000,   //letter 8

   0b01110000,
   0b10001000,
   0b10001000,
   0b01111000,
   0b00010000,
   0b00100000,
   0b01000000,   //letter 9

   0b00000000,
   0b00000000,
   0b01100000,
   0b01100000,
   0b00000000,
   0b01100000,
   0b01100000,    //letter :

   0b00000000,
   0b00000000,
   0b01100000,
   0b01100000,
   0b00000000,
   0b00100000,
   0b01000000,    //letter ;

   0b00010000,
   0b00100000,
   0b01000000,
   0b10000000,
   0b01000000,
   0b00100000,
   0b00010000,    //letter <

   0b00000000,
   0b00000000,
   0b11111000,
   0b00000000,
   0b11111000,
   0b00000000,
   0b00000000,    //letter =

   0b01000000,
   0b00100000,
   0b00010000,
   0b00001000,
   0b00010000,
   0b00100000,
   0b01000000,    //letter >

   0b01110000,
   0b10001000,
   0b00001000,
   0b00110000,
   0b01000000,
   0b00000000,
   0b01000000,    //letter ?

   0b01110000,
   0b10001000,
   0b10111000,
   0b10101000,
   0b10111000,
   0b10000000,
   0b01111000,    //letter @


//-----------------------------------Capital Letters
   0b00100000,
   0b01010000,
   0b10001000,
   0b11111000,
   0b10001000,
   0b10001000,
   0b10001000,    //letter A

   0b11110000,
   0b10001000,
   0b10001000,
   0b11110000,
   0b10001000,
   0b10001000,
   0b11110000,    //letter B

   0b01110000,
   0b10001000,
   0b10000000,
   0b10000000,
   0b10000000,
   0b10001000,
   0b01110000,    //letter C

   0b11110000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b11110000,    //letter D

   0b11111000,
   0b10000000,
   0b10000000,
   0b11110000,
   0b10000000,
   0b10000000,
   0b11111000,    //letter E

   0b11111000,
   0b10000000,
   0b10000000,
   0b11110000,
   0b10000000,
   0b10000000,
   0b10000000,    //letter F

   0b01110000,
   0b10001000,
   0b10000000,
   0b10000000,
   0b10011000,
   0b10001000,
   0b01111000,    //letter G

   0b10001000,
   0b10001000,
   0b10001000,
   0b11111000,
   0b10001000,
   0b10001000,
   0b10001000,    //letter H

   0b01110000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b01110000,    //letter I

   0b11111000,
   0b00010000,
   0b00010000,
   0b00010000,
   0b10010000,
   0b10010000,
   0b01100000,    //letter J

   0b10001000,
   0b10010000,
   0b10100000,
   0b11000000,
   0b10100000,
   0b10010000,
   0b10001000,    //letter K

   0b10000000,
   0b10000000,
   0b10000000,
   0b10000000,
   0b10000000,
   0b10000000,
   0b11111000,    //letter L

   0b10001000,
   0b11011000,
   0b10101000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,    //letter M

   0b10001000,
   0b11001000,
   0b10101000,
   0b10011000,
   0b10001000,
   0b10001000,
   0b10001000,    //letter N

   0b01110000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b01110000,    //letter O

   0b11110000,
   0b10001000,
   0b10001000,
   0b11110000,
   0b10000000,
   0b10000000,
   0b10000000,    //letter P

   0b01110000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10101000,
   0b10011000,
   0b01111000,    //letter Q

   0b11110000,
   0b10001000,
   0b10001000,
   0b11110000,
   0b10100000,
   0b10010000,
   0b10001000,    //letter R

   0b01111000,
   0b10000000,
   0b10000000,
   0b01110000,
   0b00001000,
   0b00001000,
   0b11110000,    //letter S

   0b11111000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,    //letter T

   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b01110000,    //letter U

   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b01010000,
   0b00100000,    //letter V

   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10101000,
   0b11011000,
   0b10001000,    //letter W

   0b10001000,
   0b10001000,
   0b01010000,
   0b00100000,
   0b01010000,
   0b10001000,
   0b10001000,    //letter X

   0b10001000,
   0b10001000,
   0b10001000,
   0b01010000,
   0b00100000,
   0b00100000,
   0b00100000,    //letter Y

   0b11111000,
   0b00001000,
   0b00010000,
   0b00100000,
   0b01000000,
   0b10000000,
   0b11111000,    //letter Z
//-----------------------------------End capital letters
   0b11100000,
   0b10000000,
   0b10000000,
   0b10000000,
   0b10000000,
   0b10000000,
   0b11100000,    //letter [

   0b00000000,
   0b10000000,
   0b01000000,
   0b00100000,
   0b00010000,
   0b00001000,
   0b00000000,    //letter

   0b00111000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00111000,    //letter ]

   0b00100000,
   0b01010000,
   0b10001000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,    //letter ^

   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b11111000,    //letter _

   0b00010000,
   0b00010000,
   0b00001000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,    //letter '

   0b00000000,
   0b00000000,
   0b01110000,
   0b10001000,
   0b10001000,
   0b10011000,
   0b01101000,    //letter a

   0b10000000,
   0b10000000,
   0b11110000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b11110000,    //letter b

   0b00000000,
   0b00000000,
   0b01111000,
   0b10000000,
   0b10000000,
   0b10000000,
   0b01111000,    //letter c

   0b00001000,
   0b00001000,
   0b01111000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b01111000,    //letter d

   0b00000000,
   0b00000000,
   0b01110000,
   0b10001000,
   0b11111000,
   0b10000000,
   0b01111000,    //letter e

   0b00010000,
   0b00101000,
   0b01110000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,    //letter f

   0b00000000,
   0b00000000,
   0b01110000,
   0b10001000,
   0b01111000,
   0b00001000,
   0b01110000,    //letter g

   0b10000000,
   0b10000000,
   0b11110000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10001000,    //letter h

   0b00100000,
   0b00000000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,    //letter i

   0b00100000,
   0b00000000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b10100000,
   0b01000000,    //letter j

   0b10000000,
   0b10000000,
   0b10001000,
   0b10010000,
   0b10100000,
   0b11010000,
   0b10001000,    //letter k

   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00100000,    //letter l

   0b00000000,
   0b00000000,
   0b11010000,
   0b10101000,
   0b10101000,
   0b10101000,
   0b10101000,    //letter m

   0b00000000,
   0b00000000,
   0b10110000,
   0b11001000,
   0b10001000,
   0b10001000,
   0b10001000,    //letter n

   0b00000000,
   0b00000000,
   0b01110000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b01110000,    //letter o

   0b00000000,
   0b00000000,
   0b11110000,
   0b10001000,
   0b11110000,
   0b10000000,
   0b10000000,    //letter p

   0b00000000,
   0b00000000,
   0b01111000,
   0b10001000,
   0b01111000,
   0b00001000,
   0b00001000,    //letter q

   0b00000000,
   0b00000000,
   0b10110000,
   0b11001000,
   0b10000000,
   0b10000000,
   0b10000000,    //letter r

   0b00000000,
   0b00000000,
   0b01111000,
   0b10000000,
   0b01110000,
   0b00001000,
   0b11110000,    //letter s

   0b00100000,
   0b00100000,
   0b01110000,
   0b00100000,
   0b00100000,
   0b00100000,
   0b00110000,    //letter t

   0b00000000,
   0b00000000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b10011000,
   0b01101000,    //letter u

   0b00000000,
   0b00000000,
   0b10001000,
   0b10001000,
   0b10001000,
   0b01010000,
   0b00100000,    //letter v

   0b00000000,
   0b00000000,
   0b10001000,
   0b10001000,
   0b10101000,
   0b10101000,
   0b01010000,    //letter w

   0b00000000,
   0b00000000,
   0b10001000,
   0b01010000,
   0b00100000,
   0b01010000,
   0b10001000,    //letter x

   0b00000000,
   0b00000000,
   0b10001000,
   0b10001000,
   0b11111000,
   0b00001000,
   0b01110000,    //letter y

   0b00000000,
   0b00000000,
   0b11111000,
   0b00010000,
   0b00100000,
   0b01000000,
   0b11111000,    //letter z

   0b00100000,
   0b01000000,
   0b01000000,
   0b10000000,
   0b01000000,
   0b01000000,
   0b00100000,    //letter {

   0b00100000,
   0b00100000,
   0b00100000,
   0b00000000,
   0b00100000,
   0b00100000,
   0b00100000,    //letter |

   0b00100000,
   0b00010000,
   0b00010000,
   0b00001000,
   0b00010000,
   0b00010000,
   0b00100000,    //letter }

   0b01010000,
   0b10100000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000    //letter ~

};


/**************************************************************
 *      Template zur Ansteuerung des Display SDA5707
 *      ============================================
 *                   Uwe Berger; 2009   
 * 
 * 20131101, randy:
 *  - rewrite for arduino IDE
 * 
 * 
 * 
 * --> Hardware-Protokoll-Beschreibung des Display SDA5708: 
 * Quelle: http://www.sbprojects.com/knowledge/footprints/sda5708.php
 *  
 * 
 * SDA5708 Pins (Pin 1 is right of the back side)
 * -------------------------------------------------
 * Pin Function
 * 1   Vcc
 * 2   LOAD
 * 3   DATA
 * 4   SDCLK
 * 5   RESET
 * 6   GND
 * 
 * 
 * SDA5708 Datagramm
 * -----------------
 * 
 * LOAD  ---+                          +---
 *          |                          |
 *          +--------------------------+
 * DATA  ----+----+----+----+----+----+----+----+----+-----
 *           | D0 | D1 | D2 | D3 | D4 | D5 | D6 | D7 |
 *       ----+----+----+----+----+----+----+----+----+-----
 * SDCLK --+    +--+ +--+ +--+ +--+ +--+ +--+ +--+ +--+
 *         |    |  | |  | |  | |  | |  | |  | |  | |  | 
 *         +----+  +-+  +-+  +-+  +-+  +-+  +-+  +-+  +-----
 * 
 * 
 * SDA5708 Register
 * ----------------
 * 
 * SDA5708 --> Control-Register
 * 76543210
 * ||||||||
 * |||||000 --> 100% Brightness
 * |||||001 --> 53%
 * |||||010 --> 40%
 * |||||011 --> 27%
 * |||||100 --> 20%
 * |||||101 --> 13%
 * |||||110 --> 6.6%
 * |||||111 --> 0% (dark ;-))
 * ||||+------> 0=max. peak current; 1=12.5% of max. peak current
 * |||0
 * ||+--------> 0=clear display; 1=normal
 * 11
 * 
 * 
 * SDA5807 --> Adress-Register (Digit 0 left; Digit 7 right)
 * 76543210
 * ||||||||
 * |||||000 --> Digit 0
 * |||||001 --> Digit 1
 * |||||010 --> ...
 * |||||111 --> Digit 7
 * 10100
 * 
 * ---------
 * Have fun!
 * 
 ***************************************************************/ 
#include <avr/pgmspace.h>
//#include "font.h" 

int wait=0;

// Hardwarekonfiguration MCU
const int LOAD  = 4;
const int DATA  = 5;
const int SDCLK  = 6;
const int RESET  = 7;


void setup()
{
 
// Initialize DHT sensor
dht.begin();

    Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    //Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
 
// part code from http://tronixstuff.wordpress.com/
Wire.beginTransmission(0x68);
Wire.write(0x07); // move pointer to SQW address
//Wire.write(0x10); // sends 0x10 (hex) 00010000 (binary) to control register - turns on square wave
Wire.write(0x13); // sends 0x13 (hex) 00010011 (binary) to control register - turns on square wave at 32kHz
Wire.endTransmission();
// end part code from http://tronixstuff.wordpress.com/

pinMode(A0,INPUT);//push button on encoder connected to A0 (and GND)
digitalWrite(A0,HIGH); //Pull A0 high


 Serial.begin(9600);
 Serial.println("test for niq_ro");
 Serial.println("------------------");


  // set the digital pin as output:
  pinMode(DATA, OUTPUT);      
  pinMode(LOAD, OUTPUT);      
  pinMode(SDCLK, OUTPUT);      
  pinMode(RESET, OUTPUT);      


// Port-Initialisierung, Display-Reset
	init_SDA5708();
  
	// Helligkeit einstellen 
        // 0 == ganz hell, 7 == aus
	brightness_SDA5708(1);
  
//Zeichenkette ausgeben
//  	print2display("23*C 47%"); 
print2display(" niq_ro "); 
delay (1000);
print2display("        "); 
delay (250);
}

void loop()
{
 // Reading temperature or humidity takes about 250 milliseconds!
 t = dht.readTemperature(); 
 h = dht.readHumidity();
 delay(250);  
/* test part  
// test humidity value
h = 37;
// test temperature value
t = 19;
*/


// temperatue and humidity on display
for(int j=0; j<200; j++){
temphum (t+0.5,h);

    pushlength = pushlengthset;
    pushlength = getpushlength ();
    delay (10);
    if (pushlength <pushlengthset) {
      ShortPush ();   
    }
       //This runs the setclock routine if the knob is pushed for a long time
       if (pushlength >pushlengthset) {
 //      lc.clearDisplay(0); // Clear display register 
         DateTime now = RTC.now();
         setyeartemp=now.year(),DEC;
         setmonthtemp=now.month(),DEC;
         setdaytemp=now.day(),DEC;
         sethourstemp=now.hour(),DEC;
         setminstemp=now.minute(),DEC;
         setclock();
         pushlength = pushlengthset;
       };
}

// time on display
for(int j=0; j<10; j++){
DateTime now = RTC.now();
int ora0 = now.hour();
int minut0 = now.minute();
int second0 = now.second();
/*
// serial monitor
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print(" -> ");
  Serial.print(ora1);
  Serial.println(":");
  Serial.print(minut1);
  Serial.print(":");
  Serial.print(second1);
  Serial.println("------------------");
*/
ora (ora0, minut0, second0);

    pushlength = pushlengthset;
    pushlength = getpushlength ();
    delay (10);
    if (pushlength <pushlengthset) {
      ShortPush ();   
    }
       //This runs the setclock routine if the knob is pushed for a long time
       if (pushlength >pushlengthset) {
    //     lc.clearDisplay(0); // Clear display register 
         DateTime now = RTC.now();
         setyeartemp=now.year(),DEC;
         setmonthtemp=now.month(),DEC;
         setdaytemp=now.day(),DEC;
         sethourstemp=now.hour(),DEC;
         setminstemp=now.minute(),DEC;
         setclock();
         pushlength = pushlengthset;
       };
delay (250);
}
}


void temphum (int temp, int umidit)
{
String fisier = "";
    // put temperature
     fisier += temp;
    // put degree and Celsius symbol + one space
    fisier += "*C ";
    // put humidity
    fisier += umidit;
    // put % symbol
    fisier += "%";

// http://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino
char charBuf[9];
fisier.toCharArray(charBuf, 9);
print2display(charBuf); 
}



void ora (int ora1, int minut1, int second1) 
{

String fisier = "";
    // put hour
    if (ora1 <10)
     fisier += " ";
    fisier += ora1;
    // put :
     fisier += ":";
    // put minutes
   if (minut1 <10)
     fisier += "0";
    fisier += minut1;
    // put :
     fisier += ":";
    // put minutes
   if (second1 <10)
     fisier += "0";
    fisier += second1;

// http://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino
char charBuf[9];
fisier.toCharArray(charBuf, 9);
print2display(charBuf); 

}




void data (int ziua1, int luna1, int anul1) 
{
String fisier4 = "";
    // put day
    if (ziua1 <10)
     fisier4 += "0";
    fisier4 += ziua1;
    // put .
     fisier4 += ".";
    // put mounth
   if (luna1 <10)
     fisier4 += "0";
    fisier4 += luna1;
    // put .
     fisier4 += ".";
    // put minutes
    anul1 = anul1 - 2000;
   if (anul1 <10)
     fisier4 += "0";
    fisier4 += anul1;

// http://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino
char charBuf4[9];
fisier4.toCharArray(charBuf4, 9);
print2display(charBuf4); 
delay(500);
}


//sets the clock
void setclock (){
print2display("        ");   
   setyear ();
//print2display("--------"); 
   setmonth ();
//print2display("--------");
   setday ();
//print2display("--------");
   sethours ();
//print2display("--------");
   setmins ();
//print2display("--------");
   
   RTC.adjust(DateTime(setyeartemp,setmonthtemp,setdaytemp,sethourstemp,setminstemp,setsecs));

   delay (500);
   
}

// subroutine to return the length of the button push.
int getpushlength () {
  buttonstate = digitalRead(A0);  
       if(buttonstate == LOW && buttonflag==false) {     
              pushstart = millis();
              buttonflag = true;
          };
          
       if (buttonstate == HIGH && buttonflag==true) {
         pushstop = millis ();
         pushlength = pushstop - pushstart;
         buttonflag = false;
       };
       return pushlength;
}

// The following subroutines set the individual clock parameters
int setyear () {
//  print2display("        ");
//delay(100);  
//print2display("year");   
  
    pushlength = pushlengthset;
    pushlength = getpushlength ();
    if (pushlength != pushlengthset) {
      return setyeartemp;
    }
//int setyeartemp0 = 0; // temporary year
//print2display("        ");
    knob.write(0);
    delay (50);
    knobval=knob.read();
    if (knobval < -1) { //bit of software de-bounce
      knobval = -1;
      delay (50);
    }
    if (knobval > 1) {
      knobval = 1;
      delay (50);
    }
    setyeartemp=setyeartemp + knobval;
    if (setyeartemp < 2014) { //Year can't be older than currently, it's not a time machine.
      setyeartemp = 2014;
    }
Serial.println(setyeartemp);

/*
if (setyeartemp < 2014) print2display("year2014");
if (setyeartemp == 2015) print2display("year2015");
if (setyeartemp == 2016) print2display("year2016");
if (setyeartemp == 2017) print2display("year2017");
if (setyeartemp == 2018) print2display("year2018");
if (setyeartemp == 2019) print2display("year2019");
if (setyeartemp == 2020) print2display("year2020");
if (setyeartemp == 2021) print2display("year2021");
if (setyeartemp == 2022) print2display("year2022");
if (setyeartemp == 2022) print2display("year2023");
if (setyeartemp == 2022) print2display("year2024");
if (setyeartemp == 2022) print2display("year2025");
if (setyeartemp == 2022) print2display("year2026");
if (setyeartemp == 2022) print2display("year2027");
if (setyeartemp == 2022) print2display("year2028");
if (setyeartemp == 2022) print2display("year2029");
if (setyeartemp >= 2030) print2display("year203+");
*/
int anul = setyeartemp -2000;
print2display("year20");

int anulz = anul/10;
int anulu = anul-10*anulz;
// use ASCII code for number: http://www.asciitable.com/
digit_to_SDA5708(48+anulz, 6);
digit_to_SDA5708(48+anulu, 7);

    setyear();    
}

  
int setmonth () {
    pushlength = pushlengthset;
    pushlength = getpushlength ();
    if (pushlength != pushlengthset) {
      return setmonthtemp;
    }
//print2display("        ");
    knob.write(0);
    delay (50);
    knobval=knob.read();
    if (knobval < -1) {
      knobval = -1;
      delay(50);
    }
    if (knobval > 1) {
      knobval = 1;
      delay(50);
    }
    setmonthtemp=setmonthtemp + knobval;
    if (setmonthtemp < 1) {// month must be between 1 and 12
      setmonthtemp = 1;
    }
    if (setmonthtemp > 12) {
      setmonthtemp=12;
    }

if (setmonthtemp == 1 ) print2display("month.01");
if (setmonthtemp == 2 ) print2display("month.02");
if (setmonthtemp == 3 ) print2display("month.03");
if (setmonthtemp == 4 ) print2display("month.04");
if (setmonthtemp == 5 ) print2display("month.05");
if (setmonthtemp == 6 ) print2display("month.06");
if (setmonthtemp == 7 ) print2display("month.07");
if (setmonthtemp == 8 ) print2display("month.08");
if (setmonthtemp == 9 ) print2display("month.09");
if (setmonthtemp == 10 ) print2display("month.10");
if (setmonthtemp == 11 ) print2display("month.11");
if (setmonthtemp == 12 ) print2display("month.12");

     setmonth();
}

int setday () {
  if (setmonthtemp == 4 || setmonthtemp == 5 || setmonthtemp == 9 || setmonthtemp == 11) { //30 days hath September, April June and November
    maxday = 30;
  }
  else {
  maxday = 31; //... all the others have 31
  }
  if (setmonthtemp ==2 && setyeartemp % 4 ==0) { //... Except February alone, and that has 28 days clear, and 29 in a leap year.
    maxday = 29;
  }
  if (setmonthtemp ==2 && setyeartemp % 4 !=0) {
    maxday = 28;
  }

    pushlength = pushlengthset;
    pushlength = getpushlength ();
    if (pushlength != pushlengthset) {
      return setdaytemp;
    }
//print2display("        ");
    knob.write(0);
    delay (50);
    knobval=knob.read();
    if (knobval < -1) {
      knobval = -1;
      delay(50);
    }
    if (knobval > 1) {
      knobval = 1;
      delay(50);
    }
    setdaytemp=setdaytemp+ knobval;
    if (setdaytemp < 1) {
      setdaytemp = 1;
    }
    if (setdaytemp > maxday) {
      setdaytemp = maxday;
    }
 
    
// use ASCII code for number: http://www.asciitable.com/
print2display("day.  ");
int ziz = setdaytemp/10;
int ziu = setdaytemp-10*ziz;
digit_to_SDA5708(48+ziz, 6);
digit_to_SDA5708(48+ziu, 7);
    setday();
}

int sethours () {

    pushlength = pushlengthset;
    pushlength = getpushlength ();
    if (pushlength != pushlengthset) {
      return sethourstemp;
    }
//print2display("        ");
    knob.write(0);
    delay (50);
    knobval=knob.read();
    if (knobval < -1) {
      knobval = -1;
      delay(50);
    }
    if (knobval > 1) {
      knobval = 1;
      delay(50);
    }
    sethourstemp=sethourstemp + knobval;
    if (sethourstemp < 1) {
      sethourstemp = 1;
    }
    if (sethourstemp > 23) {
      sethourstemp=23;
    }

if (sethourstemp == 0 ) print2display("hour. 00");
if (sethourstemp == 1 ) print2display("hour. 01");
if (sethourstemp == 2 ) print2display("hour. 02");
if (sethourstemp == 3 ) print2display("hour. 03");
if (sethourstemp == 4 ) print2display("hour. 04");
if (sethourstemp == 5 ) print2display("hour. 05");
if (sethourstemp == 6 ) print2display("hour. 06");
if (sethourstemp == 7 ) print2display("hour. 07");
if (sethourstemp == 8 ) print2display("hour. 08");
if (sethourstemp == 9 ) print2display("hour. 09");
if (sethourstemp == 10 ) print2display("hour. 10");
if (sethourstemp == 11 ) print2display("hour. 11");
if (sethourstemp == 12 ) print2display("hour. 12");
if (sethourstemp == 13 ) print2display("hour. 13");
if (sethourstemp == 14 ) print2display("hour. 14");
if (sethourstemp == 15 ) print2display("hour. 15");
if (sethourstemp == 16 ) print2display("hour. 16");
if (sethourstemp == 17 ) print2display("hour. 17");
if (sethourstemp == 18 ) print2display("hour. 18");
if (sethourstemp == 19 ) print2display("hour. 19");
if (sethourstemp == 20 ) print2display("hour. 20");
if (sethourstemp == 21 ) print2display("hour. 21");
if (sethourstemp == 22 ) print2display("hour. 22");
if (sethourstemp == 23 ) print2display("hour. 23");

    sethours();
}

int setmins () {

    pushlength = pushlengthset;
    pushlength = getpushlength ();
    if (pushlength != pushlengthset) {
      return setminstemp;
    }
//print2display("        ");
    knob.write(0);
    delay (50);
    knobval=knob.read();
    if (knobval < -1) {
      knobval = -1;
      delay(50);
    }
    if (knobval > 1) {
      knobval = 1;
      delay(50);
    }
    setminstemp=setminstemp + knobval;
    if (setminstemp < 0) {
      setminstemp = 0;
    }
    if (setminstemp > 59) {
      setminstemp=59;
    }
int miniz = setminstemp/10;
int miniu = setminstemp - 10*miniz;


if (miniz == 0 ) print2display("minut.0");
if (miniz == 1 ) print2display("minut.1");
if (miniz == 2 ) print2display("minut.2");
if (miniz == 3 ) print2display("minut.3");
if (miniz == 4 ) print2display("minut.4");
if (miniz == 5 ) print2display("minut.5");

// use ASCII code for number: http://www.asciitable.com/
if (miniu == 0 ) digit_to_SDA5708(48, 7);
if (miniu == 1 ) digit_to_SDA5708(49, 7);
if (miniu == 2 ) digit_to_SDA5708(50, 7);
if (miniu == 3 ) digit_to_SDA5708(51, 7);
if (miniu == 4 ) digit_to_SDA5708(52, 7);
if (miniu == 5 ) digit_to_SDA5708(53, 7);
if (miniu == 6 ) digit_to_SDA5708(54, 7);
if (miniu == 7 ) digit_to_SDA5708(55, 7);
if (miniu == 8 ) digit_to_SDA5708(56, 7);
if (miniu == 9 ) digit_to_SDA5708(57, 7);


    setmins();
}


void ShortPush () {
for(int j=0; j<2 ; j++){
DateTime now = RTC.now();
int ziua0 = now.day();
int luna0 = now.month();
int anul0 = now.year();
/*
// serial monitor
  Serial.print(now.day(), DEC);
  Serial.print(":");
  Serial.print(now.month(), DEC);
  Serial.print(":");
  Serial.print(now.year(), DEC);
  Serial.print(" -> ");
  Serial.print(ziua0);
  Serial.println(".");
  Serial.print(luna0);
  Serial.print(".");
  Serial.print(anul0);
  Serial.println("------------------");
*/

data (ziua0, luna0, anul0);

    pushlength = pushlengthset;
    pushlength = getpushlength ();
    delay (10);
    if (pushlength <pushlengthset) {
      ShortPush ();   
    }
       //This runs the setclock routine if the knob is pushed for a long time
 delay (500);
}
print2display("        "); 
delay(250);
}


//*********************************************************************
void init_SDA5708(void)
{
      // RESET toggeln
      digitalWrite(LOAD, HIGH);
      digitalWrite(RESET, LOW);
      digitalWrite(RESET, HIGH);
}

//*********************************************************************
void send_byte_to_SDA5708(uint8_t byte)
{
	uint8_t x;	
	// LOAD auf Low
        digitalWrite(LOAD, LOW);
	// jede Byte-Stelle ans Display senden
	for (x=0; x<=7;x++)	{
		// DATA entsprechend setzen
		if ((byte>>x)&1) {
                  digitalWrite(DATA, HIGH);
                } else {
                  digitalWrite(DATA, LOW);
                }
		// SDCLK toggeln
                digitalWrite(SDCLK, HIGH);
                digitalWrite(SDCLK, LOW);
	}
	// LOAD auf High
      digitalWrite(LOAD, HIGH);
}


//*********************************************************************
void brightness_SDA5708(uint8_t val)
{
	// Helligkeit von 0...8, wobei 0 ganz hell ist!
	// mit dem 4.Bit koennte man noch die Multiplex-Impulslaenge des 
	// Display-Controllere manipulieren und damit das Ding noch dunkler
	// machen... (siehe auch Hardware-/Protokoll-Beschreibung oben!)
	send_byte_to_SDA5708(0b11100000|(val&0b00000111));
}

//*********************************************************************
void digit_to_SDA5708(uint8_t sign, uint8_t digit)
{
	uint8_t i;
	// anzeigbares Zeichen? Wenn nein, dann Leerzeichen!
	if ((sign < 0x20) || (sign > 0x7b)) sign = 0x20;
	// Digit im Bereich?
	if (digit > 7) digit = 0;
	// Digit-Adresse zum Display senden
	send_byte_to_SDA5708(0b10100000|digit);
	// jede Zeile des Fonts adressieren, lesen, ausgeben
	for(i=0; i<7; i++) {
		// Font ist linksbuendig, deshalb 3 Bit nach rechts schieben...
		send_byte_to_SDA5708(pgm_read_byte(&font[(sign-0x20)*7+i])/8);
	}
}

//*********************************************************************
void print2display(char *text)
{
	uint8_t cursor=0;
	char *p=text;
	while (*p) {
		digit_to_SDA5708(*p, cursor);
		cursor++;
		p++;
	}
}
