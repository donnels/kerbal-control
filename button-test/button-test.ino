#include <KeyboardLayout.h>
#include <Keyboard.h>

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  //begins emulating a keyboard
  Keyboard.begin();
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    //press spacebar on a keyboard
    Keyboard.press((char) 0x20);
    delay(10);
    Keyboard.releaseAll();
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
