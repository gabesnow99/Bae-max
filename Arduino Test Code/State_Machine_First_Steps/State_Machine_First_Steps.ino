

#include "Arduino.h"
#include <SharpIR.h>
#include "motor_functions.h"
//define statements

#define LONG_SENSOR_INPUT A0
#define SHORT_SENSOR_INPUT 12
#define START_SENSOR_INPUT 5
#define LINE_SENSOR_LEFT 7 //the digital input pin for line sensor 1
#define LINE_SENSOR_RIGHT 8 //'' for line sensor 2
#define MAX_DISTANCE_LONGSENSOR 80

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
			{
				delay(5000); //we wait for 5 seconds
				//then initialize motors and drive forward
				if(long_sensor.getDistance() <= MAX_DISTANCE_LONGSENSOR)
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
