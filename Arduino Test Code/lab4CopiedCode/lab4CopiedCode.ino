// This is the Prototype Code for Team Gucci's robot:
// board is Arduino Uno, Programmer is AVRISP mkll
#include "Arduino.h"
#include <CapacitiveSensor.h>
#include <PWMServo.h>
// define statements
#define MOTOR_RIGHT 3
#define MOTOR_LEFT 2
#define LEFT_SERVO 8 // Maybe we'll just run both servos in parrallel off of the same pwm signal.
#define RIGHT_SERVO 8
#define PWM_LEFT_PIN 10
#define PWM_RIGHT_PIN 11
#define COLOR_THRESHOLD 1.5 // threshold from white to black?
#define LEFT_SENSOR A0
#define MIDDLE_SENSOR A1
#define RIGHT_SENSOR A3
#define PWM_OFFSET 180          // 63 //use this to subtract 25% of the speed from the motors when drifting.
#define whiteThreshold 200      // testValue to say whether the thing is actually seeing white
static PWMServo servo1, servo2; // don't know if this will actually work the way I want it to.
const int leftPwmStart = (255);
const int rightPwmStart = 255;

void setup()
{
    // put your setup code here, to run once:
    // Set up serial connection at 9600 Baud
    Serial.begin(9600);
    // Set up output pins
    pinMode(MOTOR_RIGHT, OUTPUT);
    pinMode(MOTOR_LEFT, OUTPUT);
    pinMode(PWM_LEFT_PIN, OUTPUT);
    pinMode(PWM_RIGHT_PIN, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);

    servo1.attach(LEFT_SERVO);
    servo2.attach(RIGHT_SERVO);
}

void loop()
{
    // put your main code here, to run repeatedly:
    // digitalWrite(LED_BUILTIN, LOW);

    for (int i = 0; i < 20; i++)
    {

        fsmLineFollowingShuffle();
    }
    for (int i = 0; i < 100; i++)
    {

        doStopRobot();
    }
    // delay(20000);//20 second delay, enough to grab it and hit the reset button instead.
    /*
    doDriveStraight();
    delay(2000);
    doDriveLeft();
    delay(2000);
    doDriveRight();
    delay(2000);
    doStopRobot();
    delay(20000);
    */
}
////////////////////////////////////////////////////////////////////
// FINITE STATE MACHINES//
////////////////////////////////////////////////////////////////////
void fsmLineFollowing()
{
    static int lineFollowingState = 0;

    // Serial.println(lineFollowingState);
    switch (lineFollowingState)
    {
        ////
    case 0: // default case, the robot is on the line, and is driving as straight as can be
        doDriveStraight();
        delay(250);
        doStopRobot();
        delay(500);
        if (analogRead(LEFT_SENSOR) > whiteThreshold)
        {                           // isRightOfLine()
            lineFollowingState = 1; // transition to state one. Turn left
        }
        else if (analogRead(RIGHT_SENSOR) > whiteThreshold)
        {
            lineFollowingState = 2; // transition to state 2, and turn right.
        }                           // if one of these two conditions is not met, then the robot keeps driving straight
        break;
        ////
    case 1: // robot is definitively to the left of the line, so we need to drift right to compensate.
        doDriveRight();
        delay(250);
        doStopRobot();
        delay(500);
        if (analogRead(MIDDLE_SENSOR) > whiteThreshold)
        {
            lineFollowingState = 0;
        }
        else if (analogRead(LEFT_SENSOR) > whiteThreshold)
        {
            lineFollowingState = 2;
        }
        break;
        ////
    case 2:
        doDriveLeft();
        delay(250);
        doStopRobot();
        delay(500);

        if (analogRead(MIDDLE_SENSOR) > whiteThreshold)
        {
            lineFollowingState = 0;
        }
        else if (analogRead(RIGHT_SENSOR) > whiteThreshold)
        {
            lineFollowingState = 1;
        }
        break;
    }
}
void fsmLineFollowingShuffle()
{
    static int lineFollowingState = 0;

    // Serial.println(lineFollowingState);
    switch (lineFollowingState)
    {
        ////
    case 0: // default case, robot is on the line, and will start driving to the right until it stops seeing the line.
        doDriveLeft();
        // BLACK IS HIGH!!!!
        if (analogRead(RIGHT_SENSOR) > whiteThreshold)
        {                           // isLeftOfLine()
            lineFollowingState = 1; // transition to state one. Turn right
        }

        break;
        ////
    case 1: // robot is definitively to the left of the line, so we need to drift right to compensate.
        doDriveRight();

        if (analogRead(LEFT_SENSOR) > whiteThreshold)
        { // transfer to state where we drive left again.
            lineFollowingState = 0;
        }
        break;
        ////
    }
}

////////////////////////////////////////////////////////////////////
// Function that drives the robot staight:
// Both wheels move at same speed.
////////////////////////////////////////////////////////////////////
void doDriveStraight()
{
    // This is where you add code to turn on both motors at full speed.
    doTurnMotorOn(MOTOR_RIGHT, PWM_RIGHT_PIN, rightPwmStart);
    doTurnMotorOn(MOTOR_LEFT, PWM_LEFT_PIN, leftPwmStart);
}
////////////////////////////////////////////////////////////////////
// Function that drives the robot right:
// Left wheel moves faster, robot curves right.
////////////////////////////////////////////////////////////////////
void doDriveRight()
{
    doTurnMotorOn(MOTOR_LEFT, PWM_LEFT_PIN, leftPwmStart);
    // doTurnMotorOff(MOTOR_RIGHT);
    doTurnMotorOn(MOTOR_RIGHT, PWM_RIGHT_PIN, 0.15 * 255); //
}
////////////////////////////////////////////////////////////////////
// Function that drives the robot left:
// Right wheel moves faster, robot curves left.
////////////////////////////////////////////////////////////////////
void doDriveLeft()
{
    // This is where you add code to turn on the MOTOR_RIGHT led, and the MOTOR_LEFT off.
    // doTurnMotorOff(MOTOR_LEFT);
    doTurnMotorOn(MOTOR_LEFT, PWM_LEFT_PIN, 0.15 * 255); //
    doTurnMotorOn(MOTOR_RIGHT, PWM_RIGHT_PIN, rightPwmStart);
}
////////////////////////////////////////////////////////////////////
// Function that causes the robot to stop moving.
////////////////////////////////////////////////////////////////////
void doStopRobot()
{
    // analogWrite(PWMpin, 0);
    doTurnMotorOff(MOTOR_RIGHT, PWM_RIGHT_PIN);
    doTurnMotorOff(MOTOR_LEFT, PWM_LEFT_PIN);

    // In lab 6, you will add code that makes the robot stop moving
}
// boolean functions
bool isOnLine()
{ // function that checks for whether the middle sensor is seeing
    // black, while the left and right sensors are seeing white.
    if ((isWhite(LEFT_SENSOR)) && (isWhite(RIGHT_SENSOR)))
    {
        //&&(!isWhite(MIDDLE_SENSOR))
        return (true);
    }
    else
    {
        return (false);
    }
}
bool isLeftOfLine()
{
    // function that checks for whether the left and middle sensors are seeing white, and the right sensor is seeing black.
    if ((!isWhite(RIGHT_SENSOR)))
    {
        //(isWhite(LEFT_SENSOR))&&(isWhite(MIDDLE_SENSOR))
        return (true);
    }
    else
    {
        return (false);
    }
}
bool isRightOfLine()
{
    // function that checks for whether the right and middle sensors are seeing white, and the right sensor is seeing black.
    if ((!isWhite(LEFT_SENSOR)))
    {
        //&&(isWhite(MIDDLE_SENSOR))&&(isWhite(RIGHT_SENSOR))
        return (true);
    }
    else
    {
        return (false);
    }
}
bool isWhite(int sensorInput)
{
    if (sensorInput < whiteThreshold)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}
// simple functions:
void doTurnLedOn(int led_pin)
{
    digitalWrite(led_pin, HIGH);
}

void doTurnLedOff(int led_pin)
{
    digitalWrite(led_pin, LOW);
}
void doTurnMotorOn(int MotorPin, int pwmPin, int PWMvalue)
{
    digitalWrite(MotorPin, HIGH);
    analogWrite(pwmPin, PWMvalue);
}
void doTurnMotorOff(int MotorPin, int pwmPin)
{
    digitalWrite(MotorPin, LOW);
    analogWrite(PWM_LEFT_PIN, 0);
    analogWrite(PWM_RIGHT_PIN, 0);
}
/********************************************************************
  Functions that get different values
 ********************************************************************/
////////////////////////////////////////////////////////////////////
// Function to read pin voltage
////////////////////////////////////////////////////////////////////
float getPinVoltage(int pin)
{
    // This function can be used for many different tasks in the labs
    return (5 * (float)analogRead(pin) / 1024);
}