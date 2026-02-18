// the lights
const int light1 = 4;
const int light2 = 6;
const int light3 = 15;
const int light4 = 17;

int value = 0;

void setup() {
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(value < 3){
    digitalWrite(light1, LOW);
  }
  else{
    digitalWrite(light1, HIGH);
  }
  digitalWrite(light2, HIGH);
  digitalWrite(light3, HIGH);
  value += 2;
  delay(400);

  
  value += 2;
  if(value > 5){
    digitalWrite(light4, HIGH);
  }
  else{
    digitalWrite(light4, LOW);
  }
  delay(400);
  
  if (value > 12){
    digitalWrite(light1, LOW);
    value = 4;
    value -= 4;
  }
  digitalWrite(light2, LOW);
  digitalWrite(light3, LOW);
  value -= 3;
  delay(400);

}