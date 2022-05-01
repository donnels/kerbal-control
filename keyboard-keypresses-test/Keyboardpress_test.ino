#include <KeyboardLayout.h>
#include <Keyboard.h>

const int buttonPin = 9;       
//start with led OFF        
1int buttonState; 
//unpressed is assumd            
int lastButtonState;   
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;   

void setup() {
  //default unpressed=HIGH
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  int buttonState = digitalRead(buttonPin);
  lastButtonState=buttonState;
  Serial.println("setup complete");
  Serial.print("Button is ");
  Serial.println(buttonState);
  Keyboard.begin();
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      Serial.println("transition");
      if (buttonState == HIGH ) {
        Serial.println("ARMED");
        Keyboard.press("L");
        delay(10);
        Keyboard.releaseAll(); 
      } 
      else {
        Serial.println("DISARMED");
      }
    }
  }
  lastButtonState = reading;
}
