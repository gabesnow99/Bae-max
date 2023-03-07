int RB = 6; // PIN D6 TO IN1
int RF = 9; // PIN D9 TO IN2
int LB = 10; // PIN D10 TO IN3
int LF = 11; // PIN D11 TO IN4

void goForward(int vel) {
  analogWrite(RB, 0);
  analogWrite(LB, 0);
  analogWrite(RF, vel);
  analogWrite(LF, vel);
}

void goBackward(int vel) {
  analogWrite(RF, 0);
  analogWrite(LF, 0);
  analogWrite(RB, vel);
  analogWrite(LB, vel);
}

void setup() {
  pinMode(RB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(LF, OUTPUT);
}

void loop() {
  while(1) {
    goForward(100);
    delay(2000);
    goBackward(150);
    delay(3000);
  }
}
