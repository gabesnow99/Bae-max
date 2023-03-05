#include <Arduino.h>

#define LEFT_MOTOR_DIR1 3
#define LEFT_MOTOR_DIR2 4

#define RIGHT_MOTOR_DIR1 1
#define RIGHT_MOTOR_DIR2 2 

void stop_motors()
{
	//Write all motor direction pins to low
	digitalWrite(LEFT_MOTOR_DIR1, LOW);
	digitalWrite(LEFT_MOTOR_DIR2, LOW);
	digitalWrite(RIGHT_MOTOR_DIR1, LOW);
	digitalWrite(LEFT_MOTOR_DIR2, LOW);
}
void drive_forward()
{
	//Write every other direction pin to high.
	digitalWrite(LEFT_MOTOR_DIR1, HIGH);
	digitalWrite(LEFT_MOTOR_DIR2, LOW);
	digitalWrite(RIGHT_MOTOR_DIR1, HIGH);
	digitalWrite(LEFT_MOTOR_DIR2, LOW);
}
void drive_backwards()
{
	//Write both motors to drive backwards
	digitalWrite(LEFT_MOTOR_DIR1, LOW);
	digitalWrite(LEFT_MOTOR_DIR2, HIGH);
	digitalWrite(RIGHT_MOTOR_DIR1, LOW);
	digitalWrite(LEFT_MOTOR_DIR2, HIGH);
}
void drive_left()
{
	//Write left motor to go backwards, and right motor to keep going forwards.
	digitalWrite(LEFT_MOTOR_DIR1, LOW);
	digitalWrite(LEFT_MOTOR_DIR2, HIGH);
	digitalWrite(RIGHT_MOTOR_DIR1, HIGH);
	digitalWrite(LEFT_MOTOR_DIR2, LOW);
}
void drive_right()
{
	//Write right motor to go backwards, and left motor to keep going forwards.
	digitalWrite(LEFT_MOTOR_DIR1, HIGH);
	digitalWrite(LEFT_MOTOR_DIR2, LOW);
	digitalWrite(RIGHT_MOTOR_DIR1, LOW);
	digitalWrite(LEFT_MOTOR_DIR2, HIGH);
}
