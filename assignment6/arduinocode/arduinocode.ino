// Pins
const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int ledPin = 7;

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

int inByte = 0;

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    inByte = Serial.read();
    if(inByte == 'A')
    {
      digitalWrite(ledPin, 1);

      buttonState1 = !digitalRead(buttonPin1);
      buttonState2 = !digitalRead(buttonPin2);

      Serial.print(buttonState1);
      Serial.print(",");
      Serial.print(buttonState2);
      Serial.print("\n");
    }
  }
  else
  {
    digitalWrite(ledPin, 0);
    Serial.println("Rx Byte is nothing");
  }
}