#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define N_LEDS 74

//  The overall fire brightness
int brightness = 225;

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
int currentColorIndex = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(brightness);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //  Get the current colors based on the color index:
  RGB currentColor = flameColors[currentColorIndex];

 //  Flicker, based on our initial RGB values. Check i=9; i<29 when setting up actual sign
  for(int i=9; i<29; i++) { 
    int flicker = random(0,85);
    int r1 = currentColor.r-flicker;
    int g1 = currentColor.g-flicker;
    int b1 = currentColor.b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    strip.setPixelColor(i,r1,g1, b1);
  }
 
  strip.show();

  //  Adjust the delay here, if you'd like.  Right now, it randomizes the 
  //  color switch delay to give a sense of realism
  delay(random(10,45));
}
