#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define leftPin 5
#define rightPin 6
#define stripLength 6

//  The overall fire brightness
const int brightness = 225;

struct RGB {
  byte r;
  byte g;
  byte b;
};

//  The flame color array (the first is the default):
RGB flameColors[] = {
  { 255, 95, 0},  // Orange flame
  { 226, 15, 30}    // Red flame
};

//  Tracks the current color
const int currentColorIndex = 0;

Adafruit_NeoPixel leftStrip = Adafruit_NeoPixel(stripLength, leftPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightStrip = Adafruit_NeoPixel(stripLength, rightPin, NEO_GRB + NEO_KHZ800);


void setup() {

  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  leftStrip.begin();
  rightStrip.begin();
  leftStrip.setBrightness(brightness);
  rightStrip.setBrightness(brightness);
  leftStrip.show();
  rightStrip.show();
}

void loop() {
  //  Get the current colors based on the color index:
  RGB currentColor = flameColors[currentColorIndex];

  //  Flicker, based on our initial RGB values. 
  for (int i = 0; i < stripLength; i++) {
    int flicker = random(0, 85);
    int r1 = currentColor.r - flicker;
    int g1 = currentColor.g - flicker;
    int b1 = currentColor.b - flicker;
    if (g1 < 0) g1 = 0;
    if (r1 < 0) r1 = 0;
    if (b1 < 0) b1 = 0;
    leftStrip.setPixelColor(i, r1, g1, b1);
    rightStrip.setPixelColor(i, r1, g1, b1);
  }

  leftStrip.show();
  rightStrip.show();
  //  Adjust the delay here, if you'd like.  Right now, it randomizes the
  //  color switch delay to give a sense of realism
  delay(random(10, 45));
}
