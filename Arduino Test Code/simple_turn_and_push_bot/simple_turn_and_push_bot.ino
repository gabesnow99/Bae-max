
#include <avr/io.h>
#include "Arduino.h"
// #include <SharpIR.h>
#include "motor_functions.h"

// define statements

#define LONG_SENSOR_INPUT A7
#define SHORT_SENSOR_INPUT 12
#define START_SENSOR_INPUT A5
#define LINE_SENSOR_FRONT_LEFT 7  // the digital input pin for line sensor 1
#define LINE_SENSOR_FRONT_RIGHT 2 //'' for line sensor 2
#define LINE_SENSOR_BACK_LEFT 4
#define LINE_SENSOR_BACK_RIGHT 3
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
unsigned int pastValue = 0;
unsigned int thisValue = 0;
int diff = 0;

// create new distance sensor object
SharpIR long_sensor(SharpIR::GP2Y0A21YK0F, LONG_SENSOR_INPUT);

bool isFrontRightWhite()
{
    if (!digitalRead(LINE_SENSOR_FRONT_RIGHT))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isFrontLeftWhite()
{
    if (!digitalRead(LINE_SENSOR_FRONT_LEFT))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isBackLeftWhite()
{
    if (!digitalRead(LINE_SENSOR_BACK_LEFT))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isBackRightWhite()
{
    if (!digitalRead(LINE_SENSOR_BACK_RIGHT))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool additionalDistanceFilter()
{
    thisValue = getFilteredDist(long_sensor);
    if (thisValue < 50)
    { // we have detected enemy robot!! Charge!!
        delay(5);
        diff = getFilteredDist(long_sensor) - thisValue;
        if (abs(diff) <= 10)
        {
            return true;
        }
    }
}

void setup()
{
    state = BEGINNING;
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
    pinMode(LINE_SENSOR_FRONT_LEFT, INPUT);
    pinMode(LINE_SENSOR_FRONT_RIGHT, INPUT);
    pinMode(LINE_SENSOR_BACK_LEFT, INPUT);
    pinMode(LINE_SENSOR_BACK_RIGHT, INPUT);
    pastValue = getFilteredDist(long_sensor);
    stopWheels();
    // lONG_SENSOR_INPUT is already configured by the object creation.
    // This article explains how to remap the default pwm frequencies for arduino
    // https://microcontrollerslab.com/arduino-pwm-tutorial-generate-fix-and-variable-frequency-signal/#:~:text=The%20analogWrite()%20function%20which,using%20the%20analogWrite()%20command.
}

void loop()
{
    // Begin the State Machine Layout
    // distance = long_sensor.getDistance();
    // Serial.println("Current State"state);

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
            if (true)
            {
                startMillis = millis();
                goForward(255);
                state = RUSH;
            }
            else
            {
                spinLeft(80);
                state = TURN_lEFT;
            }
        }
        break;
    case RUSH:
        Serial.println("RUSH");
        currentMillis = millis();
        if (getFilteredDist(long_sensor) > 50)
        { // we have lost the enemy
            spinLeft(80);
            state = TURN_lEFT;
        }
        else if (getFilteredDist(long_sensor) < 10)
        {
            jukeTurn(25, 200);
            startMillis = millis();
            state = JUKE;
        }

        break;

    case TURN_lEFT:
        if (additionalDistanceFilter())
        {
            startMillis = millis();
            goForward(255);
            state = RUSH;
        }

        break;

    case JUKE:
        Serial.println("JUKE");
        currentMillis = millis();
        if (currentMillis - startMillis >= 50)
        {
            state = PUSH_STATE;
            goBackward(255);
        }
        break;

    case (REVERSE):
        Serial.println("REVERSE");
        currentMillis = millis();
        if (currentMillis - startMillis >= 2000)
        {
            if (getFilteredDist(long_sensor) < 50)
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

    case PUSH_STATE:
        // in this push state we need to check to see if we're heading off the edge.
        if (isFrontLeftWhite() || isFrontRightWhite() || isBackLeftWhite() || isBackRightWhite())
        {
            goForward();
            startMillis = millis();
            state = RUSH;
            delay(3000);
            stopWheels();
            state = BEGINNING;
        }
            break;
        case STOP:
            delay(5000);
            state = BEGINNING;
            break;
        case TEST:
            // goForward();
            //  Serial.print("Front Left "); //THIS IS THE PROBLEMATIC ONE!!!
            //  Serial.println(isFrontLeftWhite());
            //  delay(100);
            //  // Serial.print("Front Right ");
            //  Serial.println(isFrontRightWhite());
            //  delay(100);
            //  // Serial.print("Back Left ");
            //  Serial.println(isBackLeftWhite());
            //  delay(100);
            //  // Serial.print("Back Right ");
            //  Serial.println(isBackRightWhite());

            // if (isFrontRightWhite())
            // {
            //     escapeRightBack();
            // }
            // else if (isFrontLeftWhite())
            // {
            //     escapeLeftBack();
            // }
            // else
            // {
            //     goBackward();
            // }
            break;
        default:
            break;
        }
    }
