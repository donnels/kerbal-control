#include <FastLED.h>
//fastled stuff
#define NUM_LEDS 22
#define NUM_RING_LEDS 12
#define DATA_PIN 7
#define disarmed_LED 12
#define armed_LED 13
#define SAS_LED 14
#define rot1p_LED 15
#define rot1m_LED 16
#define rot1b_LED 17
CRGB leds[NUM_LEDS];

//button stuff
const int buttonPin = 8;      
//start with led OFF         
int armButtonState; 
//unpressed is assumd            
int lastarmButtonState;   
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 5;   
//LED brightness stuff
int brightness = 5;

void setup() { 
  //LED stuff
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  leds[disarmed_LED] = CRGB::Red;
  leds[armed_LED] = CRGB::Black;
  leds[SAS_LED] = CRGB::Black;
  leds[rot1p_LED] = CRGB::Black;
  leds[rot1m_LED] = CRGB::Black;
  leds[rot1b_LED] = CRGB::Black;
  //spare
  leds[18] = CHSV(0, 255, 16);
  leds[19] = CHSV(63, 255, 16);
  leds[20] = CHSV(127, 255, 16);
  leds[21] = CHSV(255, 255, 16);
  //END LEDS
  FastLED.show();
  //button stuff
  //default unpressed=HIGH
  pinMode(buttonPin, INPUT_PULLUP);
  int armButtonState = digitalRead(buttonPin);
  lastarmButtonState=armButtonState;
  //The rest
  Serial.begin(115200);
  Serial.println("setup complete");
  Serial.print("Button is ");
  Serial.println(armButtonState);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastarmButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != armButtonState) {
      armButtonState = reading;
      Serial.println("transition");
      if (armButtonState == HIGH ) {
        Serial.println("ARMED");
        leds[disarmed_LED] = CRGB::Red;
        leds[armed_LED] = CRGB::Black;
      } 
      else {
        Serial.println("DISARMED");
        leds[armed_LED] = CRGB::Green;
        leds[disarmed_LED] = CRGB::Black;;
      }
    }
  }

  FastLED.show();
  lastarmButtonState = reading;
}
