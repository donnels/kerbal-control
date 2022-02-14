const int buttonPin = 9;    
const int ledPin = LED_BUILTIN;    
//start with led OFF  
int ledState = LOW;        
int buttonState; 
//unpressed is assumd            
int lastButtonState;   
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;   

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
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      Serial.println("transition");
      if (buttonState == LOW ) {
        Serial.println("ARMED");
        ledState = LOW;
      } 
      else {
        Serial.println("DISARMED");
        ledState = HIGH;
      }
    }
  }
  digitalWrite(ledPin,ledState);
  lastButtonState = reading;
}
