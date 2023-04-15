#include <Arduino.h>
#include <SharpIR.h>

int RB = 6;	 // PIN D6 TO IN1
int RF = 9;	 // PIN D9 TO IN2
int LB = 10; // PIN D10 TO IN3
int LF = 11; // PIN D11 TO IN4

void stopWheels()
{
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	analogWrite(RF, 0);
	analogWrite(LF, 0);
}

void goForward(int vel = 150)
{
	// Serial.begin(9600);
	Serial.println("I have reached go forward!!");
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	analogWrite(RF, vel);
	analogWrite(LF, vel);
}

void goForward(int vel, int milliseconds)
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

void goBackward(int vel, int milliseconds)
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

void turnRight(int deg = 90, int vel = 150) // going to need to test the blocking that occurs here!!
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

void turnLeft(int deg = 90, int vel = 150) // going to need to test the blocking that occurs here!!
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

void spinLeft(int vel = 150)
{
	analogWrite(LF, 0);
	analogWrite(RB, 0);
	analogWrite(LB, vel);
	analogWrite(RF, vel);
}

void pivotLeft(int deg = 90, int vel = 150)
{
	int time = 2 * round(250 * deg / vel);
	analogWrite(LF, 0);
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	analogWrite(RF, vel);
	delay(time);
	stopWheels();
}

void escapeRightBack()
{
	int vel = 200;
	int faster = 250;
	int milliseconds = 1000;
	analogWrite(RF, faster);
	analogWrite(LF, vel);
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	delay(milliseconds);
	analogWrite(RF, 0);
	analogWrite(LF, 0);
	analogWrite(RB, 0);
	analogWrite(LB, 0);
}

void escapeLeftBack()
{
	int vel = 200;
	int faster = 250;
	int milliseconds = 1000;
	analogWrite(RF, vel);
	analogWrite(LF, faster);
	analogWrite(RB, 0);
	analogWrite(LB, 0);
	delay(milliseconds);
	analogWrite(RF, 0);
	analogWrite(LF, 0);
	analogWrite(RB, 0);
	analogWrite(LB, 0);
}
//this function will filter the signal from the sensor and return the average of the last 10 readings
unsigned long getFilteredDist(SharpIR long_sensor)
{
	int windowSize = 10;
	// unsigned long distArr[windowSize];
	unsigned long sum = 0;
	for (int i = 0; i < windowSize; i++)
	{
		sum += long_sensor.getDistance();
	}
	return sum / windowSize;
}
void jukeTurn(int slowVel, int fastVel){
	analogWrite(RB, slowVel);
	analogWrite(LB, fastVel);
	analogWrite(RF, 0);
	analogWrite(LF, 0);

}

//create an alpha filter to smooth out the readings from the sensor
void alternateAlphaFilter(unsigned long *distArr, unsigned long dist, int windowSize)
{
	for (int i = 0; i < windowSize - 1; i++)
	{
		distArr[i] = distArr[i + 1];
	}
	distArr[windowSize - 1] = dist;
}

//this function will allow the arduino to connect with bluetooth
void connectBluetooth()
{
	// Serial.begin(9600);
	// Serial.println("Connecting to bluetooth");
	// Serial.println("Waiting for connection");
	// while (!Serial)
	// 	;
	// Serial.println("Connected");
}