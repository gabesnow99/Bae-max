#include <Arduino.h>

#define RB 6 // PIN D6 TO IN1
#define RF 9	 // PIN D9 TO IN2
#define LB 10 // PIN D10 TO IN3
#define LF 11 // PIN D11 TO IN4

void stopWheels()
{
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	analogWrite(RF, 0);
	analogWrite(LF, 0);
}

void goForward(int vel = 150)
{
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	analogWrite(RF, vel);
	analogWrite(LF, vel);
}

void goForward_withDelay(int vel, int milliseconds)
{
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	analogWrite(RF, vel);
	analogWrite(LF, vel);
	delay(milliseconds);
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	analogWrite(RF, 0);
	analogWrite(LF, 0);
}

void goBackward(int vel = 150)
{
	analogWrite(RF, 0);
	analogWrite(LF, 0);
	analogWrite(RB, vel);
	analogWrite(LB, vel);
}

void goBackward_withDelay(int vel, int milliseconds)
{
	analogWrite(RF, 0);
	analogWrite(LF, 0);
	analogWrite(RB, vel);
	analogWrite(LB, vel);
	delay(milliseconds);
	analogWrite(RF, 0);
	analogWrite(LF, 0);
	analogWrite(RB, 0);
	analogWrite(LB, 0);
}

void turnRight(int deg = 90, int vel = 150) //going to need to test the blocking that occurs here!!
{
	int time = round(250 * deg / vel);
	analogWrite(RF, 0);
	analogWrite(LB, 0);
	analogWrite(RB, vel);
	analogWrite(LF, vel);
	delay(time);
	analogWrite(RB, 0);
	analogWrite(LF, 0);
}

void turnLeft(int deg = 90, int vel = 150)//going to need to test the blocking that occurs here!!
{
	int time = round(250 * deg / vel);
	analogWrite(LF, 0);
	analogWrite(RB, 0);
	analogWrite(LB, vel);
	analogWrite(RF, vel);
	delay(time);
	analogWrite(LB, 0);
	analogWrite(RF, 0);
}
