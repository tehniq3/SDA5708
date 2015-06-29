// sketch: http://blog.smue.org/archives/433-DBOX1-SDA5708-display-+-arduino.html
// data: http://www.sbprojects.com/knowledge/footprints/sda5708/index.php
// data2: http://www.bralug.de/wiki/Display_SDA5708
// adapted sketch by niq_ro: http://arduinotehniq.blogspot.com/

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include "DHT.h"
#define DHTPIN 7     // what pin we're connected to D7
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
float t;
int h, t0, t1, t2, h1, h2;

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
const int LOAD  = 2;
const int DATA  = 3;
const int SDCLK  = 4;
const int RESET  = 5;

void setup() {
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


  // Initialize HTD sensor
  dht.begin();
  
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



//*********************************************************************
//*********************************************************************
//*********************************************************************
void loop() {

  // Reading temperature or humidity 
 h = dht.readHumidity();
 t = dht.readTemperature(); 
 delay(250);
 t1 = t + 0.5; 
 
  
  String fisier2 = "";
    // put temperature
     fisier2 += t1;
    // put degree and Celsius symbol + one space
    fisier2 += "*C ";
    // put humidity
    fisier2 += h;
    // put % symbol
    fisier2 += "%";

// http://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino
char charBuf[9];
fisier2.toCharArray(charBuf, 9);
print2display(charBuf); 

delay(1000);

}
