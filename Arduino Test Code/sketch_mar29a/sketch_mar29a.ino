const byte interruptPin1 = 4;  // Define the first interrupt pin
const byte interruptPin2 = 5;  // Define the second interrupt pin

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin1, INPUT); // Set the first interrupt pin as an input with a pull-up resistor
  pinMode(interruptPin2, INPUT); // Set the second interrupt pin as an input with a pull-up resistor
  attachInterrupt(digitalPinToInterrupt(interruptPin1), interruptFunction1, RISING); // Attach first interrupt to the pin and specify the first interrupt function and trigger condition
  attachInterrupt(digitalPinToInterrupt(interruptPin2), interruptFunction2, RISING); // Attach second interrupt to the pin and specify the second interrupt function and trigger condition
}

void loop() {
  // Your main program code
}

void interruptFunction1() {
  // Your first interrupt function code
  Serial.println("Inter 1");
}

void interruptFunction2() {
  // Your second interrupt function code
  Serial.println("inter 2");
}