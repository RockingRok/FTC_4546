#include "hitechnic-gyro.h"
#include "hitechnic-irseeker-v2.h"
// stops the motors
void stopMotors()
{
	motor[motorBR] = 0;
	motor[motorFR] = 0;
	motor[motorBL] = 0;
	motor[motorFL] = 0;
}
// This method is refrenced whenever the robot needs to move.
void startMotors(int left, int right)
{
	motor[motorBR] = right;
	motor[motorFR] = right;
	motor[motorBL] = left;
	motor[motorFL] = left;
}
// This method finds whether or not there is an ir signal coming from direction n.
// The ir sensor uses a 180 degree arc split into smaller sections which are each assigned a number.
bool irSeeker(int n)
{
	return (HTIRS2readACDir(irSensor) == n);
}
// if the gyro sensor is within the range of the inputs, this will return true. else, it will return false
bool gyroInRange(float heading, float target, float threshhold)
{
	return abs(heading - target) <= threshhold;
}
//The turning method uses two inputs; direction and distance. direction is used to tell whether to turn right or left, and distance is how much to turn.
void turn(int dir, int encoderValue)
{
	//if dir is positive, turn right
	if(dir > 0)
	{
		nMotorEncoder[motorFR] = 0;
		while(nMotorEncoder[motorFR] < encoderValue)
		{
			startMotors(50, -50);
		}
		stopMotors();
		nMotorEncoder[motorFR] = 0;
	}

	//if dir is negative, turn left
	if(dir < 0)
	{
		nMotorEncoder[motorFR] = 0;
		while(nMotorEncoder[motorFR] < encoderValue)
		{
			startMotors(-50, 50);
		}
		stopMotors();
		nMotorEncoder[motorFR] = 0;
	}
}

// the variables are, in order; direction of movement, amount of wheel rotations, speed of motors
// gyro measures degrees of rotation (+ means to the right, - means to the left) / second
// Deg/sec * sec rotating will give us total amount of degrees rotated

//This is the full movement method. It has three inputs: direction, distance, and speed.
void move(int dir, int encoderValue, int power) //encoders go up to 280 with the new motors = 1 rotation
{
	float heading = 0;
	float trueHeading = 0; //the direction the robot is really facing, in case the gyro screws up
	HTGYROstartCal(gyroSensor); //heading 180 -180 while() L- R+
	wait1Msec(500);
	if(dir == 1) //if direction is 1, go forward
	{
		nMotorEncoder[motorFR] = 0; //motor encoder reset to 0 before going forward
		while(nMotorEncoder[motorFR] < encoderValue) //while the wheels are going forward, 280 = 1 rotation of a wheel
		{
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			trueHeading += heading * (20/1000); //converts the current rotation value to the true degrees

			if(!gyroInRange(trueHeading, 0, 1))
			{
				if(trueHeading > 0) //if the robot drifted to the right
				{
					startMotors(power/4, power);
				}

				if(trueHeading < 0) //if the robot drifted to the left
				{
					startMotors(power, power/4);
				}
			}
			else //if the robot did not drift
			{
				startMotors(power, power);
			}
			wait1Msec(20); // gyro can check its rotation value every 20 ms
		}
	}
	stopMotors();
}
//Moves the robot slowly to get off the ramp without falling over
void moveOffRamp(int encoderValue) //remember, 280 is 4pi rotations
{
	while(nMotorEncoder[motorFR] < encoderValue)
	{
		startMotors(25, 25);
	}
}
//Is this for testing?
void moveBasic(int encoderValue, int dir)
{
	if(dir > 0)
	{
		while(nMotorEncoder[motorFR] < encoderValue)
		{
			startMotors(50,50);
		}
	}

	if(dir < 0)
	{
		while(abs(nMotorEncoder[motorFR]) < encoderValue)
		{
			startMotors(-50,-50);
		}
	}
}
