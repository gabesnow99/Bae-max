
#include <avr/iom328p.h>
#include "Arduino.h"
#include <SharpIR.h>
#include "motor_functions.h"

//define statements

#define LONG_SENSOR_INPUT A0
#define SHORT_SENSOR_INPUT 12
#define START_SENSOR_INPUT 5
#define LINE_SENSOR_LEFT 7 //the digital input pin for line sensor 1
#define LINE_SENSOR_RIGHT 8 //'' for line sensor 2

//Global Variables
int Max_Distance_longSensor = 80;

//create new distance sensor object
SharpIR long_sensor( SharpIR::GP2Y0A21YK0F, LONG_SENSOR_INPUT );

void setup() {
	// Pins to configure.
	//MOTOR PINS
	pinMode(LEFT_MOTOR_DIR1, OUTPUT);
	pinMode(LEFT_MOTOR_DIR2, OUTPUT);
	pinMode(RIGHT_MOTOR_DIR1, OUTPUT);
	pinMode(RIGHT_MOTOR_DIR2, OUTPUT);
	//SENSOR INPUT PINS
	pinMode(SHORT_SENSOR_INPUT, INPUT);
	pinMode(START_SENSOR_INPUT, INPUT);
	pinMode(LINE_SENSOR_LEFT, INPUT);
	pinMode(LINE_SENSOR_RIGHT, INPUT);
	//lONG_SENSOR_INPUT is already configured by the object creation.
	//TCCR2B = TCCR2B & B1111000 | B00000111;
	//may not use the above code, but here is the link to the article I was reading
	//https://microcontrollerslab.com/arduino-pwm-tutorial-generate-fix-and-variable-frequency-signal/#:~:text=The%20analogWrite()%20function%20which,using%20the%20analogWrite()%20command.
}


void loop() {
	//Begin the State Machine Layout
	enum {BEGINNING, RUSH, TURN_lEFT, TURN_RIGHT, JUKE, REVERSE, PUSH_STATE, STOP} state;
	state  = BEGINNING;
	//stop motors. 
	stop_motors();
	switch (state)
	{
		case BEGINNING:
			if(digitalRead(START_SENSOR_INPUT))
			{//we've read the start sensor that wants us to drive!!
				delay(5000); //we wait for 5 seconds
				//then initialize motors and drive forward
				if(long_sensor.getDistance() <= Max_Distance_longSensor)
				{ //we have detected enemy robot!! Charge!!
					drive_forward();
					state = RUSH;
				}else
				{ //we have lost the enemy!!
					drive_left();
					state = TURN_lEFT;
				}
			}
			break;
		
		case RUSH:

			break;

		case TURN_lEFT:

			break;

		case TURN_RIGHT:

			break;

		case JUKE:

			break;

		case (REVERSE):

			break;

		case(PUSH_STATE):

			break;

		default:
			break;
	}

}
