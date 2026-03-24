// Special thanks to my homeboy Tenn

const int ledPin = 9;
const int ledPin2 = 7;
const int buttonPin = 4;
const int potPin = 1;
const int buzzer = 6;

bool lastButtonState;
bool onState = false;
int lastTimeButtonStateChanged = 0;
int debounceDuration = 20;

int value = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  analogReadResolution(10);
  Serial.begin(9600);
}

void loop() {
  // Tenn has a cool life hack for these buttons
  if (millis() - lastTimeButtonStateChanged >= debounceDuration)
  {
    bool buttonState = digitalRead(buttonPin);
    if (buttonState != lastButtonState)
    {
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;
      if (buttonState == HIGH) 
      {
       onState = !onState;
      }
    }
  }

  if(onState) {
    value = analogRead(potPin);
    int light = map(value, 0, 1023, 0, 255);
    int buzzertime = map(value, 0, 1023, 0, 2000);

    analogWrite(ledPin,light);
    analogWrite(ledPin2,light);
    if(value > 300){
      analogWrite(ledPin,light-40);
      analogWrite(ledPin2,light-40);
      tone(buzzer,buzzertime,10);
      delay(10);
    }
    Serial.println(value);
    }
  else {
    analogWrite(ledPin, 0);
    analogWrite(ledPin2, 0);
  }
}