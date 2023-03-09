/*
 * getDistance
 *
 * Example of using SharpIR library to calculate the distance beetween the sensor and an obstacle
 *
 * Created by Giuseppe Masino, 15 June 2016
 *
 * -----------------------------------------------------------------------------------
 *
 * Things that you need:
 * - Arduino
 * - A Sharp IR Sensor
 *
 *
 * The circuit:
 * - Arduino 5V -> Sensor's pin 1 (Vcc)
 * - Arduino GND -> Sensor's pin 2 (GND)
 * - Arduino pin A0 -> Sensor's pin 3 (Output)
 *
 *
 * See the Sharp sensor datasheet for the pin reference, the pin configuration is the same for all models.
 * There is the datasheet for the model GP2Y0A41SK0F:
 *
 * http://www.robotstore.it/open2b/var/product-files/78.pdf
 *
 */

// import the library in the sketch
#include <SharpIR.h>
int RB = 6;  // PIN D6 TO IN1
int RF = 9;  // PIN D9 TO IN2
int LB = 10; // PIN D10 TO IN3
int LF = 11; // PIN D11 TO IN4
unsigned long currentMillis = 0;
unsigned long startMillis = 0;
enum
{
  BEGINNING,
  RUSH,
  TURN_lEFT,
  TURN_RIGHT,
  JUKE,
  REVERSE,
  PUSH_STATE,
  STOP
} state;
void goForward(int vel = 150)
{
  // Serial.begin(9600);
  Serial.println("I have reached go forward!!");
  analogWrite(RB, 0);
  analogWrite(LB, 0);
  analogWrite(RF, vel);
  analogWrite(LF, vel);
}
void stopWheels()
{
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	analogWrite(RF, 0);
	analogWrite(LF, 0);
}
// Create a new instance of the library
// Call the sensor "sensor"
// The model of the sensor is "GP2YA41SK0F"
// The sensor output pin is attached to the pin A0
SharpIR sensor(SharpIR::GP2Y0A21YK0F, A0);

void setup()
{
  Serial.begin(9600); // Enable the serial comunication
  // MOTOR PINS ALL ARE PWM PINS.
  pinMode(RB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(LF, OUTPUT);
  state = BEGINNING;
}

void loop()
{

  
  while (1)
  {
    int distance = sensor.getDistance(); // Calculate the distance in centimeters and store the value in a variable
    Serial.println(distance);            // Print the value to the serial monitor 
    switch (state)
    {
      case BEGINNING:
            Serial.println("beginning");
            // Serial.println(digitalRead(START_SENSOR_INPUT));
            if (distance < 10)
            {     
                goForward(150);
                startMillis = millis();
                state = RUSH;
            }
        break;

        case RUSH:
            Serial.println("RUSH");
            currentMillis = millis();
            if ((currentMillis - startMillis) >= 5000) 
            {
                stopWheels();
                state = BEGINNING;
            }
        break;
    }
  }
}
