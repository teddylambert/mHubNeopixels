/*
NOTE: The colors encoded are not permanent. Any RGB tulpe (except for the ones currently listed as (0,0,0)) can 
be changed to a new color as desired
*/

#include <Adafruit_NeoPixel.h>

#define LEDPin 6
#define numberOfNeopixels 670 //approximate value, maybe be a few less (around 667)
#define sensorPin 0 //pin that potentiometer is connected to

int sensorValue = 0;
int resetCounter = 0;
int potModes;
int lastPotMode = 0;
const int defaultMode = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberOfNeopixels, LEDPin, NEO_RGB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.show();
  clearPixels();
  colorPicker(defaultMode);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  potModes = map(sensorValue, 0, 1023, 0, 6); //if more modes required, change the 6 here
  if (lastPotMode != potModes) { //keeps the loop from overloading the pixels
    clearPixels();
    colorPicker(potModes);
    lastPotMode = potModes;
  }
  if (potModes == 5) { //These two if statements make sure that the loop doesn't terminate prematurely
    clearPixels();
    chase(strip.Color(255, 0, 255)); //Change this rgb color if desired
    lastPotMode = potModes;
  }
  if (potModes == 6) {
    clearPixels();
    bounce(strip.Color(0, 0, 255));
    lastPotMode = potModes;
  }
}

void colorPicker(int colorMode) {
  switch (colorMode) {
    case 1:
      for (uint16_t case1a = 0; case1a < 180; case1a++) { //This double for loops (and the others like it) bypass the broken pixels
        strip.setPixelColor(case1a, 255, 0, 0);
      }
      for (uint16_t case1b = 190; case1b < numberOfNeopixels; case1b++) {
        strip.setPixelColor(case1b, 255, 0, 0);
      }
      strip.show();
      break;

    case 2:
      for (uint16_t case2a = 0; case2a < 180; case2a++) {
        strip.setPixelColor(case2a, 0, 0, 255);
      }
      for (uint16_t case2b = 190; case2b < numberOfNeopixels; case2b++) {
        strip.setPixelColor(case2b, 0, 0, 255);
      }
      strip.show();
      break;

    case 3:
      for (uint16_t case3a = 0; case3a < 180; case3a++) {
        strip.setPixelColor(case3a, 0, 255, 0);
      }
      for (uint16_t case3b = 190; case3b < numberOfNeopixels; case3b++) {
        strip.setPixelColor(case3b, 0, 255, 0);
      }
      strip.show();
      break;

    case 4:
      for (uint16_t case4a = 0; case4a < 180; case4a++) {
        strip.setPixelColor(case4a, 255, 0, 255);
      }
      for (uint16_t case4b = 190; case4b < 227; case4b++) {
        strip.setPixelColor(case4b, 0, 0, 255);
      }
      for (uint16_t case4c = 227; case4c < 414; case4c++) {
        strip.setPixelColor(case4c, 255, 0, 255);
      }
      for (uint16_t case4d = 414; case4d < 464; case4d++) {
        strip.setPixelColor(case4d, 0, 0, 255);
      }
      for (uint16_t case4d = 464; case4d < numberOfNeopixels; case4d++) {
        strip.setPixelColor(case4d, 255, 0, 255);
      }
      strip.show();
      break;

    default:
      for (uint16_t defaulta = 0; defaulta < 180; defaulta++) {
        strip.setPixelColor(defaulta, 255, 0, 255);
      }
      for (uint16_t defaultb = 190; defaultb < numberOfNeopixels; defaultb++) {
        strip.setPixelColor(defaultb, 255, 0, 255);
      }
      strip.show();
      break;
  }
}

void clearPixels() {
  while (resetCounter < 5) {
    for (uint16_t i = 0; i < numberOfNeopixels; i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    resetCounter++;
  }
  resetCounter = 0;
}

static void chase(uint32_t line) {
  for (uint16_t i = 0; i < strip.numPixels() + 4; i++) {
    strip.setPixelColor(i  , line); // Draw new pixel
    strip.setPixelColor(i - 6, 0, 0, 0); // Erase pixel a few steps back
    strip.setPixelColor(185, 0, 0, 0);
    strip.setPixelColor(186, 0, 0, 0);
    strip.show();
    delay(20);
  }
  for (uint16_t i = 0; i < strip.numPixels() + 4; i++) { //Makes sure all pixels are reset before restarting
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
  delay(100);
}

static void bounce(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels() - 4; i++) {
    strip.setPixelColor(i  , c); // Draw new pixel
    strip.setPixelColor(i - 6, 0, 0, 0); // Erase pixel a few steps back
    strip.setPixelColor(185, 0, 0, 0);
    strip.setPixelColor(186, 0, 0, 0);
    strip.show();
    delay(20);
  }
  for (uint16_t q = 665; q > 0; q--) {
    strip.setPixelColor(q  , c); // Draw new pixel
    strip.setPixelColor(q + 6, 0, 0, 0); // Erase pixel a few steps back
    strip.setPixelColor(185, 0, 0, 0);
    strip.setPixelColor(186, 0, 0, 0);
    strip.show();
    delay(20);
  }

  for (uint16_t i = 0; i < strip.numPixels() + 4; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
  delay(100);
}

//Created by Teddy Lambert
