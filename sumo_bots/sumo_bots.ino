int RB = 6; // PIN D6 TO IN1
int RF = 9; // PIN D9 TO IN2
int LB = 10; // PIN D10 TO IN3
int LF = 11; // PIN D11 TO IN4

void stopWheels() {
  analogWrite(RB, 0);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(LF, 0);
}

void goForward(int vel = 150) {
  analogWrite(RB, 0);
  analogWrite(LB, 0);
  analogWrite(RF, vel);
  analogWrite(LF, vel);
}

void goForward(int vel, int milliseconds) {
  analogWrite(RB, 0);
  analogWrite(LB, 0);
  analogWrite(RF, vel);
  analogWrite(LF, vel);
  delay(milliseconds);
  analogWrite(RB, 0);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(LF, 0);
}

void goBackward(int vel = 150) {
  analogWrite(RF, 0);
  analogWrite(LF, 0);
  analogWrite(RB, vel);
  analogWrite(LB, vel);
}

void goBackward(int vel, int milliseconds) {
  analogWrite(RF, 0);
  analogWrite(LF, 0);
  analogWrite(RB, vel);
  analogWrite(LB, vel);
  delay(milliseconds);
  analogWrite(RF, 0);
  analogWrite(LF, 0);
  analogWrite(RB, 0);
  analogWrite(LB, 0);
}

void turnRight(int deg = 90, int vel = 150) {
  int time = 250*deg/vel;
  analogWrite(RF, 0);
  analogWrite(LB, 0);
  analogWrite(RB, vel);
  analogWrite(LF, vel);
  delay(time);
  analogWrite(RB, 0);
  analogWrite(LF, 0);
}

void turnLeft(int deg = 90, int vel = 150) {
  int time = 250*deg/vel;
  analogWrite(LF, 0);
  analogWrite(RB, 0);
  analogWrite(LB, vel);
  analogWrite(RF, vel);
  delay(time);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
}

void setup() {
  pinMode(RB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(LF, OUTPUT);
}

void cupidShuffle() {
  // to the right
  turnRight(15);
  delay(500);
  turnRight(15);
  delay(500);
  turnRight(15);
  delay(250);
  turnRight(15);
  delay(250);
  turnRight(15);
  delay(500);

  // to the left
  turnLeft(15);
  delay(500);
  turnLeft(15);
  delay(500);
  turnLeft(15);
  delay(250);
  turnLeft(15);
  delay(250);
  turnLeft(15);
  delay(500);

  // kick, now kick
  for (int i = 0; i < 4; i++) {
    goForward(150, 80);
    goBackward(150, 80);
    delay(350);
  }

  // walk it by yourself
  for (int i = 0; i < 4; i++) {
    turnRight(30, 100);
    delay(250);
    turnLeft(30, 100);
    delay(250);
  }

  turnLeft(120);
}

void loop() {
  while(1) {
    delay(1000);
    cupidShuffle();
  }
}
