const int buttonPin = 8;    
const int ledPin = LED_BUILTIN;      
int ledState = LOW;        
int buttonState;             
int lastButtonState = LOW;   
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 5;   

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  digitalWrite(ledPin, ledState);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      Serial.println("transition High2Low");
      if (buttonState == LOW ) {
        ledState = !ledState;
        Serial.println("transition Low2High");
      }
    }
  }

  digitalWrite(ledPin, ledState);  
  lastButtonState = reading;
}
