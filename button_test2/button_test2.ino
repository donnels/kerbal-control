const int buttonPin = 9;    
const int ledPin = LED_BUILTIN;    
//start with led OFF  
int ledState = LOW;        
int buttonState; 
//unpressed is assumd            
int lastButtonState;   
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 5;   

void setup() {
  //default unpressed=HIGH
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  digitalWrite(ledPin, ledState);
  int buttonState = digitalRead(buttonPin);
  lastButtonState=buttonState;
  Serial.println("setup complete");
  Serial.print("Button is ");
  Serial.println(buttonState);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) >= debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      Serial.println("transition");
    }
    if (buttonState == LOW ) {
      Serial.println("transition High2Low");
      ledState = LOW;
    } 
    else {
      Serial.println("transition Low2High");
      ledState = HIGH;
    }
  }
  delay(500);
  digitalWrite(ledPin,ledState);
  lastButtonState = reading;
}
