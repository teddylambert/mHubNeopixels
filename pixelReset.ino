#include <Adafruit_NeoPixel.h>

#define PIN 6
#define N_LEDS 670
int counter = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  while(counter < 50) { //definitely overkill, but works
    for (uint16_t i = 0; i < N_LEDS; i++) {
      strip.setPixelColor(i, 0, 0, 0);
    }
    counter++;
  }
  strip.show();
}
void loop() {
}
