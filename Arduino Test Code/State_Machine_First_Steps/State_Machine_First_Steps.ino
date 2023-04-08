
#include <avr/io.h>
#include "Arduino.h"
//#include <SharpIR.h>
#include "motor_functions.h"

// define statements

#define LONG_SENSOR_INPUT A7
#define SHORT_SENSOR_INPUT 12
#define START_SENSOR_INPUT 5
<<<<<<< HEAD
#define LINE_SENSOR_LEFT 7 //the digital input pin for line sensor 1
#define LINE_SENSOR_RIGHT 8 //'' for line sensor 2
#include <SharpIR.h>

//create new distance sensor object
SharpIR long_sensor( SharpIR::GP2Y0A21YK0F, LONG_SENSOR_INPUT );

//Global Variables
=======
#define LINE_SENSOR_FRONT_LEFT 7  // the digital input pin for line sensor 1
#define LINE_SENSOR_FRONT_RIGHT 8 //'' for line sensor 2
#define LINE_SENSOR_BACK_LEFT 3
#define LINE_SENSOR_BACK_RIGHT 2
// Global Variables
>>>>>>> abcc10b67a30059429bc70ad5d430f6001c48ccc
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

<<<<<<< HEAD
void motor_functions_test(){
	//test each one of the motor functions in turn
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
=======
// create new distance sensor object
SharpIR long_sensor(SharpIR::GP2Y0A21YK0F, LONG_SENSOR_INPUT);
>>>>>>> abcc10b67a30059429bc70ad5d430f6001c48ccc

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
bool isFrontRightBlack()
{
    if (digitalRead(LINE_SENSOR_FRONT_RIGHT))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isFrontLeftBlack()
{
<<<<<<< HEAD
	//Begin the State Machine Layout 
	distance = long_sensor.getDistance();
	//Serial.println("Current State"state);
	//stopWheels();
	switch (state)
	{
		case BEGINNING:
   
			Serial.println("begin");


      while(1) {
        Serial.println(getFilteredDist(long_sensor));
      }


      
			if(!digitalRead(START_SENSOR_INPUT)){
				startupSensorSeen = true;
				delay(5000); //we wait for 5 seconds
			}
			if(startupSensorSeen) 
			{//we've read the start sensor that wants us to drive!!
				

				if(long_sensor.getDistance() < 50) { //we have detected enemy robot!! Charge!!
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
			
			if(long_sensor.getDistance() > 50){ //we have lost the enemy
				spinLeft();
				state = TURN_lEFT;
			}
      else if (long_sensor.getDistance() < 10) {
//        gabesSuperFunFloat = currentMillis;
        state = JUKE;
      }

		break;

		case TURN_lEFT:
			if(long_sensor.getDistance() <= 50)
			{ //we have detected enemy robot!! Charge!!
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
      while(1);
			break;
		case STOP:
			delay(5000);
			state = BEGINNING;
			break;
		default:
			break;
	}
	
=======
    if (digitalRead(LINE_SENSOR_FRONT_LEFT))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isBackLeftBlack()
{
    if (digitalRead(LINE_SENSOR_BACK_LEFT))
    {
        return true;
    }else{
        return false;
    }
}
bool isBackRightBlack()
{
    if (digitalRead(LINE_SENSOR_BACK_RIGHT))
    {
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
    pinMode(LINE_SENSOR_FRONT_LEFT, INPUT);
    pinMode(LINE_SENSOR_FRONT_RIGHT, INPUT);
    pinMode(LINE_SENSOR_BACK_LEFT, INPUT);
    pinMode(LINE_SENSOR_BACK_RIGHT, INPUT);

    stopWheels();
    // lONG_SENSOR_INPUT is already configured by the object creation.
    // This article explains how to remap the default pwm frequencies for arduino
    // https://microcontrollerslab.com/arduino-pwm-tutorial-generate-fix-and-variable-frequency-signal/#:~:text=The%20analogWrite()%20function%20which,using%20the%20analogWrite()%20command.
}
>>>>>>> abcc10b67a30059429bc70ad5d430f6001c48ccc

void loop()
{
    // Begin the State Machine Layout
    distance = long_sensor.getDistance();
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
        // Serial.println(currentMillis);
        Serial.println(long_sensor.getDistance());
        //      float distance = long_sensor.getDistance();
        if (long_sensor.getDistance() > 50)
        { // we have lost the enemy
            spinLeft();
            state = TURN_lEFT;
        }
        else if (long_sensor.getDistance() < 10)
        {
            // gabesSuperFunFloat = currentMillis;
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
        //DO WE WANT TO USE THIS?
        break;

    case JUKE:
        Serial.println("JUKE");
        pivotLeft(270);
        goForward();
        state = PUSH_STATE;
        break;

    case (REVERSE):

        break;

    case PUSH_STATE:
        //in this push state we need to check to see if we're heading off the edge.
        if(isFrontLeftBlack()){
            goBackward();
            state = REVERSE;            
        }else if(isFrontRightBlack()){
            goBackward();
            state = REVERSE;
        }else if(isBackLeftBlack()){
            goBackward();
            state = REVERSE;
        }else if(isBackRightBlack()){
            goBackward();
            state = REVERSE;
        }
        break;
    case STOP:
        delay(5000);
        state = BEGINNING;
        break;
    case TEST:
        Serial.print("Front Left ");
        Serial.println(digitalRead(LINE_SENSOR_FRONT_LEFT));
        delay(100);
        Serial.print("Front Right ");
        Serial.println(digitalRead(LINE_SENSOR_FRONT_RIGHT));
        delay(100);
        Serial.print("Back Left ");
        Serial.println(digitalRead(LINE_SENSOR_BACK_LEFT));
        delay(100);
        Serial.print("Back Right ");
        Serial.println(digitalRead(LINE_SENSOR_BACK_RIGHT));
        
        // if (isFrontRightBlack())
        // {
        //     escapeRightBack();
        // }
        // else if (isFrontLeftBlack())
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
