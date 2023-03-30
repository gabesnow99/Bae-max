
#include <avr/io.h>
#include "Arduino.h"
#include <SharpIR.h>
#include "motor_functions.h"

// define statements

#define LONG_SENSOR_INPUT A7
#define SHORT_SENSOR_INPUT 12
#define START_SENSOR_INPUT 5
#define LINE_SENSOR_LEFT 7  // the digital input pin for line sensor 1
#define LINE_SENSOR_RIGHT 8 //'' for line sensor 2

// Global Variables
unsigned int turnSpeed = 150;
unsigned int fullSpeed = 255;
unsigned int Max_Distance_longSensor = 80;
unsigned long currentMillis = 0;
unsigned long startMillis = 0;
unsigned int distance = 0;
bool startupSensorSeen = false;
enum
{
    BEGINNING,
    RUSH,
    TURN_lEFT,
    TURN_RIGHT,
    JUKE,
    REVERSE,
    PUSH_STATE,
    STOP,
    TEST
} state;
// start off in the beginning, a very good place to start.

int gabesSuperFunInt = 0;
float gabesSuperFunFloat = 0.0;

// create new distance sensor object
SharpIR long_sensor(SharpIR::GP2Y0A21YK0F, LONG_SENSOR_INPUT);

void respond(){
  //ISR function
  Serial.println("STOP!");
}

void motor_functions_test()
{
    // test each one of the motor functions in turn
    goForward(fullSpeed, 5000);
    delay(1000);
    turnLeft(90, turnSpeed);
    delay(5000);
    stopWheels();
    delay(1000);
    turnRight(90, turnSpeed);
    delay(5000);
    stopWheels();
    delay(1000);
    goBackward(fullSpeed, 5000);
    delay(5000);
    stopWheels();
    delay(10000); // caution!!! final delay is long, but after ten seconds it will probably surprise you by running.
}

bool isRightBlack(){
    if(digitalRead(LINE_SENSOR_RIGHT)){
        return true;
    }else{
        return false;
    }
}

bool isLeftBlack(){
    if(digitalRead(LINE_SENSOR_LEFT)){
        return true;
    }else{
        return false;
    }
}
void setup()
{
    state = TEST;
    Serial.begin(9600);
    // Pins to configure.
    // MOTOR PINS ALL ARE PWM PINS.
    pinMode(RB, OUTPUT);
    pinMode(RF, OUTPUT);
    pinMode(LB, OUTPUT);
    pinMode(LF, OUTPUT);
    // SENSOR INPUT PINS
    pinMode(SHORT_SENSOR_INPUT, INPUT);
    pinMode(START_SENSOR_INPUT, INPUT);
    pinMode(LINE_SENSOR_LEFT, INPUT);
    pinMode(LINE_SENSOR_RIGHT, INPUT);
    stopWheels();
    // lONG_SENSOR_INPUT is already configured by the object creation.
    // This article explains how to remap the default pwm frequencies for arduino
    // TCCR2B = TCCR2B & B1111000 | B00000111;
    // we may not use the above code, but here is the link to the article I was reading
    // https://microcontrollerslab.com/arduino-pwm-tutorial-generate-fix-and-variable-frequency-signal/#:~:text=The%20analogWrite()%20function%20which,using%20the%20analogWrite()%20command.

    //interrupt
    attachInterrupt(LINE_SENSOR_RIGHT, respond, CHANGE) ;//i THINK WE want rising

}

void loop()
{
    // Begin the State Machine Layout
    distance = long_sensor.getDistance();
    // Serial.println("Current State"state);
    // stopWheels();
    switch (state)
    {
    case BEGINNING:
        Serial.println("begin");
        if (!digitalRead(START_SENSOR_INPUT))
        {
            startupSensorSeen = true;
            delay(5000); // we wait for 5 seconds
        }
        if (startupSensorSeen)
        { // we've read the start sensor that wants us to drive!!

            if (long_sensor.getDistance() < 50)
            { // we have detected enemy robot!! Charge!!
                startMillis = millis();
                goForward(155);
                state = RUSH;
                Serial.println("RUSH");
            }
            else
            {
                spinLeft();
                state = TURN_lEFT;
            }
        }
        break;

    case RUSH:
        currentMillis = millis();
        //			Serial.println(currentMillis);
        Serial.println(long_sensor.getDistance());

        //      float distance = long_sensor.getDistance();

        if (long_sensor.getDistance() > 50)
        { // we have lost the enemy
            spinLeft();
            state = TURN_lEFT;
        }
        else if (long_sensor.getDistance() < 10)
        {
            //        gabesSuperFunFloat = currentMillis;
            state = JUKE;
        }

        break;

    case TURN_lEFT:
        if (long_sensor.getDistance() <= 50)
        { // we have detected enemy robot!! Charge!!
            startMillis = millis();
            goForward(155);
            state = RUSH;
            Serial.println("RUSH");
        }

        break;

    case TURN_RIGHT:

        break;

    case JUKE:
        Serial.println("JUKE");
        pivotLeft(270);
        state = PUSH_STATE;
        break;

    case (REVERSE):

        break;

    case PUSH_STATE:
        goForward();
        while (1)
            ;
        break;
    case STOP:
        delay(5000);
        state = BEGINNING;
        break;
    case TEST:
        // Serial.println(digitalRead(LINE_SENSOR_LEFT));
        // if(isRightBlack()){
        //   escapeRightBack();
        // }else if(isLeftBlack()){
        //   escapeLeftBack();
        // }else{
        //   goBackward();
        // }
        break;
    default:
        break;
    }
}
