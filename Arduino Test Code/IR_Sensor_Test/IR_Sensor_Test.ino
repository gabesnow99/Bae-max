
#include "Arduino.h"
#define IR_SENSOR_PIN A5
int IR_sensor_state;

void setup()
{
    Serial.begin(9600);
    pinMode(IR_SENSOR_PIN, INPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  IR_sensor_state = analogRead(IR_SENSOR_PIN);
  Serial.println(IR_sensor_state);
  delay(1);
}