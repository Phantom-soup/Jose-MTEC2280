const int button_1 = 1;
const int button_2 = 2;
const int button_3 = 42;
const int button_4 = 41;
const int button_5 = 4;
const int button_6 = 5;

bool buttonState_1 = 0;
bool buttonState_2 = 0;
bool buttonState_3 = 0;
bool buttonState_4 = 0;
bool buttonState_5 = 0;
bool buttonState_6 = 0;

int lastTime = 0;
int currentTime = 0;
int timerInterval = 5;

void setup() {
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  pinMode(button_5, INPUT_PULLUP);
  pinMode(button_6, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {
  buttonState_1 = !digitalRead(button_1);
  buttonState_2 = !digitalRead(button_2);
  buttonState_3 = !digitalRead(button_3);
  buttonState_4 = !digitalRead(button_4);
  buttonState_5 = !digitalRead(button_5);
  buttonState_6 = !digitalRead(button_6);
  
  currentTime = millis();                       //read current elapsed time
  if (currentTime - lastTime >= timerInterval)  //if we have reached our timer interval...
  {
    lastTime = currentTime;  //store current time as lastTime so we know when timer last triggered

    Serial.print(buttonState_1);
    Serial.print(',');
    Serial.print(buttonState_2);
    Serial.print(',');
    Serial.print(buttonState_3);
    Serial.print(',');
    Serial.print(buttonState_4);
    Serial.print(',');
    Serial.print(buttonState_5);
    Serial.print(',');
    Serial.print(buttonState_6);
    Serial.print('\n');
  }
}