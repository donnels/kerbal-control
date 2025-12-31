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
bool startup = true;
bool stagePressed = false;

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

  // Serial debugging
  Serial.begin(9600);
  Serial.println("Kerbal Controller Started - Disarmed");
}

void loop() {
  handleArmButton();
  handleStageButton();
  
  // LED animation when armed
  if (armed && !stagePressed) {
    static unsigned long lastLEDChange = 0;
    static int activeLED = 6;
    if (millis() - lastLEDChange > 100) {
      for(int i=6; i<=10; i++) leds[i] = CRGB::Black;
      leds[activeLED] = CRGB::Green;
      activeLED = (activeLED >= 10) ? 6 : activeLED + 1;
      lastLEDChange = millis();
    }
  }
  
  // Blink LEDs 6-10 orange while stage pressed
  if (stagePressed) {
    static unsigned long lastBlink = 0;
    static bool blinkState = false;
    if (millis() - lastBlink > 200) {
      CRGB color = blinkState ? CRGB::Orange : CRGB::Black;
      for(int i=6; i<=10; i++) leds[i] = color;
      blinkState = !blinkState;
      lastBlink = millis();
    }
  }
  
  // Debug output every second
  static unsigned long lastDebug = 0;
  if (millis() - lastDebug > 1000) {
    Serial.print("Armed: ");
    Serial.print(armed ? "YES" : "NO");
    Serial.print(" | ARM switch: ");
    Serial.print(armButtonState == LOW ? "ON" : "OFF");
    Serial.print(" | STAGE button: ");
    Serial.println(digitalRead(STAGE_BUTTON_PIN) == LOW ? "PRESSED" : "RELEASED");
    lastDebug = millis();
  }
  
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
      if (startup) {
        startup = false;
      } else {
        armed = (armButtonState == LOW);
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
      if (stageButtonState == LOW && armed) {
        if (!stagePressed) {
          Keyboard.press(' '); // Spacebar for stage
          delay(10);
          Keyboard.releaseAll();
          flashStageLED();
          stagePressed = true;
        }
      } else if (stageButtonState == HIGH) {
        stagePressed = false;
      }
    }
  }
  lastStageButtonState = reading;
}

void updateLEDs() {
  if (armed) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[0] = CRGB::Green; // Toggle indicator
  } else {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
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