#include <FastLED.h>
#include <Keyboard.h>

// Pin definitions
#define LED_DATA_PIN 7
#define ARM_BUTTON_PIN 8
#define STAGE_BUTTON_PIN 9

// LED setup
#define NUM_LEDS 22
#define RING_LEDS 12
CRGB leds[NUM_LEDS];

// Button states
int armButtonState = HIGH; // HIGH = unpressed (pullup)
int lastArmButtonState = HIGH;
unsigned long lastArmDebounceTime = 0;

int stageButtonState = HIGH;
int lastStageButtonState = HIGH;
unsigned long lastStageDebounceTime = 0;

unsigned long debounceDelay = 50;

// System state
bool armed = false;

void setup() {
  // LEDs
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(10); // Low brightness
  updateLEDs();

  // Buttons
  pinMode(ARM_BUTTON_PIN, INPUT_PULLUP);
  pinMode(STAGE_BUTTON_PIN, INPUT_PULLUP);

  // Keyboard
  Keyboard.begin();
}

void loop() {
  handleArmButton();
  handleStageButton();
  FastLED.show();
}

void handleArmButton() {
  int reading = digitalRead(ARM_BUTTON_PIN);
  if (reading != lastArmButtonState) {
    lastArmDebounceTime = millis();
  }
  if ((millis() - lastArmDebounceTime) > debounceDelay) {
    if (reading != armButtonState) {
      armButtonState = reading;
      if (armButtonState == LOW) { // Pressed
        armed = !armed;
        updateLEDs();
      }
    }
  }
  lastArmButtonState = reading;
}

void handleStageButton() {
  int reading = digitalRead(STAGE_BUTTON_PIN);
  if (reading != lastStageButtonState) {
    lastStageDebounceTime = millis();
  }
  if ((millis() - lastStageDebounceTime) > debounceDelay) {
    if (reading != stageButtonState) {
      stageButtonState = reading;
      if (stageButtonState == LOW && armed) { // Pressed and armed
        Keyboard.press(' '); // Spacebar for stage
        delay(10);
        Keyboard.releaseAll();
        flashStageLED();
      }
    }
  }
  lastStageButtonState = reading;
}

void updateLEDs() {
  // Clear all
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  if (armed) {
    // Green for armed
    leds[0] = CRGB::Green;
  } else {
    // Red for disarmed
    leds[0] = CRGB::Red;
  }
}

void flashStageLED() {
  // Flash ring red briefly
  for (int i = 0; i < RING_LEDS; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  delay(200);
  updateLEDs();
}