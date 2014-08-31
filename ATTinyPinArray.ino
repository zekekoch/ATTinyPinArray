#include "FastLED.h"
#include <SoftwareSerial.h>
#include <Stepper.h>

#define dataPin 1
#define stepPinA 2
#define stepPinB 0
#define txPin 3
#define rxPin 4

#define ledCount 13
#define STEPS 300

Stepper stepper(STEPS, stepPinA, stepPinB);

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
CRGB leds[ledCount];

void setup()  
{
  FastLED.addLeds<NEOPIXEL, dataPin>(leds, ledCount);

  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  stepper.setSpeed(120);
  
  // reset to the bottom
  stepper.step(STEPS);
}

void loop() // run over and over
{
  // check to see if there are any instructions
  if (mySerial.available())
  {
    // get the instruction and set it into r
    byte r = mySerial.read();

    // set the appropriate LED on the strip
    setSingleLed(r,CRGB::Blue);
    
    // push the pin in and out the appropriate distance
    stepper.step(-r*30);
    stepper.step(r*30);
    
    // set back to black
    setSingleLed(r,CRGB::Black);
    
    mySerial.write(r*30);
  }
}

void setSingleLed(byte led, byte color)
{
  fill_solid(leds, ledCount, CRGB::Black);
  leds[led] = color;
  FastLED.show();
}
