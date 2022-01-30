#include <FastLED.h>
#define NUM_LEDS 22
#define NUM_RING_LEDS 12
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

void setup() { 
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    leds[16] = CHSV(0, 255, 16);
    leds[12] = CHSV(128, 255, 16);
    leds[21] = CHSV(255, 255, 16);
    FastLED.show();
}

void loop() {
    for(int dot = 0; dot < NUM_RING_LEDS; dot++) { 
        leds[dot] = CHSV(64, 255, 16);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot] = CRGB::Black;
        delay(150);
    }
}