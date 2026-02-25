// left button toggles which light is being selected
// right button toggles the light on and off
// holding both buttons collectively sets all lights

const int ledPin1 = 4;
const int ledPin2 = 5;
const int ledPin3 = 6;
const int ledPin4 = 7;

const int buttonPin1 = 15;
const int buttonPin2 = 16;

const int potPin = 17;

bool buttonState1 = 0;
bool lastButtonState1 = 0;
bool toggle1 = 0;
bool fallToggle1 = 0;

bool buttonState2 = 0;
bool lastButtonState2 = 0;
bool toggle2 = 0;
bool fallToggle2 = 0;

int lightNumber = 1;
bool b1push = 0;
bool b2push = 0;

int ledLevel1 = 0;
int ledLevel2 = 0;
int ledLevel3 = 0;
int ledLevel4 = 0;

bool ledToggle1 = 0;
bool ledToggle2 = 0;
bool ledToggle3 = 0;
bool ledToggle4 = 0;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  
  analogReadResolution(10);
  pinMode(potPin, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {
  int adcVal = analogRead(potPin);
  int currentValue = map(adcVal, 0, 1023, 0, 255);
  buttonState1 = !digitalRead(buttonPin1);
  buttonState2 = !digitalRead(buttonPin2);

  if (buttonState1 && lastButtonState1)
  {
    if (lightNumber > 4)
    {
      lightNumber = 1;
    }
    else
    {
      lightNumber++;
    }

    b1push = 1;
    toggle1 = !toggle1;
  }
  if (!buttonState1 && lastButtonState1)
  {
    b1push = 0;
    fallToggle1 = !fallToggle1;
  }
  lastButtonState1 = buttonState1;

  if (buttonState2 && lastButtonState2)
  {
    b2push = 1;
    toggle2 = !toggle2;
  }
  if (!buttonState2 && lastButtonState2)
  {
    b2push = 0;
    fallToggle2 = !fallToggle2;
  }
  lastButtonState2 = buttonState2;

  if (b1push && b2push)
  {
    analogWrite(ledPin1, ledLevel1);
    analogWrite(ledPin2, ledLevel2);
    analogWrite(ledPin3, ledLevel3);
    analogWrite(ledPin4, ledLevel4);
  }
  else if (lightNumber == 1)
  {
    ledLevel1 = adcVal;
    analogWrite(ledPin1, ledLevel1);
  }
  else if (lightNumber == 2)
  {
    analogWrite(ledPin2, ledLevel2);
  }
  else if (lightNumber == 3)
  {
    analogWrite(ledPin3, ledLevel3);
  }
  else if (lightNumber == 4)
  {
    analogWrite(ledPin4, ledLevel4);
  }
  
  if (!ledToggle1)
  {
    analogWrite(ledPin1, 0);
  }
  if (!ledToggle2)
  {
    analogWrite(ledPin2, 0);
  }
  if (!ledToggle3)
  {
    analogWrite(ledPin3, 0);
  }
  if (!ledToggle4)
  {
    analogWrite(ledPin4, 0);
  }
}
