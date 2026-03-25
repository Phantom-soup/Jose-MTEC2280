// Pins
const int potPin1 = 7;
const int potPin2 = 4;
const int buttonPin1 = 17;
const int buttonPin2 = 46;

// Pot Values
int potVal1 = 0;
int potVal2 = 0;

// Button Toggle
bool buttonState1 = 0;
bool lastButtonState1;
int lastTimeButtonStateChanged1 = 0;
int debounceDuration = 14;

bool buttonState2 = 0;

// Send Timers
int lastTime = 0;
int currentTime = 0;
int timerInterval = 5;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  analogReadResolution(10);
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  potVal1 = analogRead(potPin1);
  potVal2 = analogRead(potPin2);

  buttonState1 = !digitalRead(buttonPin1);
  buttonState2 = !digitalRead(buttonPin2);
  
  if (currentTime - lastTime >= timerInterval){
    lastTime = currentTime;

    Serial.print(buttonState1);
    Serial.print(",");
    Serial.print(buttonState2);
    Serial.print(",");
    Serial.print(potVal1);
    Serial.print(",");
    Serial.print(potVal2);
    Serial.print("\n");
  }
}