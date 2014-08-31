/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include "FastLED.h"
#include <SoftwareSerial.h>
#define ledPin 2
#define dataPin 1
#define otherLed 0

#define ledCount 13

SoftwareSerial mySerial(4, 3); // RX, TX
CRGB leds[ledCount];

void setup()  
{
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, ledCount);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(otherLed, OUTPUT);
}

void loop() // run over and over
{
  cylon();
  myblink(otherLed, 2);
  delay(1000);
  if (mySerial.available())
  {
    myblink(ledPin, 2);

    byte r = mySerial.read();
    myblink(ledPin, r);
    mySerial.write(r);
  }
}

void cylon()
{
  	// First slide the led in one direction
	for(int i = 0; i < ledCount; i++) {
		// Set the i'th led to red 
		leds[i] = CRGB::Red;
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		leds[i] = CRGB::Black;
		// Wait a little bit before we loop around and do it again
		delay(30);
	}

	// Now go in the other direction.  
	for(int i = ledCount-1; i >= 0; i--) {
		// Set the i'th led to red 
		leds[i] = CRGB::Red;
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		leds[i] = CRGB::Black;
		// Wait a little bit before we loop around and do it again
		delay(30);
	}
}

void myblink(byte led, byte count)
{
  for(byte c = 0;c<count;c++)
  {
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);    
  }
}
