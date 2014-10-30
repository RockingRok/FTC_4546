//CONTRIBUTORS: FTC 4546
#include "hitechnic-gyro.h";
#include "hitechnic-irseeker-v2.h"

int getEncoderAverage(int leftMotor, int rightMotor)
{
	return (leftMotor + rightMotor) / 2;
}

int getIR()
{
	return HTIRS2readACDir(irSensor);
}

bool gyroThreshhold(float heading, int trueValue, int threshhold)
{
	if(abs(heading) > (trueValue + threshhold))
	{
		return false;
	}
	return true;
}

int getPosition()
{
	int x = getIR();
	if(x >= 6)
	{
		return 2;
	}
	if(x <= 5 && x > 0)
	{
		return 3;
	}
	return 1;
}

void setMotors(int left, int right)
{
	motor[motorFL] = left;
	motor[motorBL] = left;
	motor[motorFR] = right;
	motor[motorBR] = right;
}

void stopMotors()
{
	motor[motorFL] = 0;
	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
}

void move(int dir, int encoderValue, int power, int time = 5000) //encoders go up to 280 with the new motors = 1 rotation
{
	float heading = 0;
	float trueHeading = 0; //the direction the robot is really facing, in case the gyro screws up
	HTGYROstartCal(gyroSensor); //heading 180 -180 while() L- R+

	wait1Msec(500);
	clearTimer(T1);
	if(dir == 1) //if direction is 1, go forward
	{
		nMotorEncoder[motorFR] = 0; //motor encoder reset to 0 before going forward
		nMotorEncoder[motorFL] = 0; //motor encoder reset to 0 before going forward
		while((getEncoderAverage(nMotorEncoder[motorFR], nMotorEncoder[motorFL]) < encoderValue) && (time1[T1] < time))
		{
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			trueHeading += heading * (20/1000); //converts the current rotation value to the true degrees

			if(!gyroThreshhold(trueHeading, 0, 1))
			{
				if(trueHeading > 0) //if the robot drifted to the right
				{
					setMotors(power/4, power);
				}

				if(trueHeading < 0) //if the robot drifted to the left
				{
					setMotors(power, power/4);
				}
			}
			else //if the robot did not drift
			{
				setMotors(power, power);
			}
			wait1Msec(20); // gyro can check its rotation value every 20 ms
		}
	}
	stopMotors();
}

void turn(int power, int deg, int dir, int time = 5000)
{
	float heading = 0;
	float trueHeading = 0;

	HTGYROstartCal(gyroSensor);
	wait1Msec(500);
	clearTimer(T1);
	//turning right
	if(dir == 1)
	{
		while(!gyroThreshhold(trueHeading, deg, 1) && (time1[T1] < time))
		{
			setMotors(power, 0);
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			trueHeading += heading * (20/1000); //converts the current rotation value to the true degrees
			wait1Msec(20);
		}
	}
	//turning left
	if(dir == 2)
	{
		while(!gyroThreshhold(trueHeading, deg, 1) && (time1[T1] < time))
		{
			setMotors(0, power);
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			trueHeading += heading * (20/1000); //converts the current rotation value to the true degrees
			wait1Msec(20);
		}
	}
}

void moveOffRamp(int deg, int power, int time = 3000)
{
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;

	wait1Msec(500);
	clearTimer(T1);
	while((getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorFR]) < deg) && time1[T1] < time)
	{
		setMotors(power, power);
	}
	stopMotors();
}

void lifter(int deg, int time = 5000)
{
	nMotorEncoder[motorLift] = 0;

	wait1Msec(500);
	clearTimer(T1);
	while((nMotorEncoder[motorLift] < deg) && time1[T1] < time)
	{
		motor[motorLift] = 100;
	}
	motor[motorLift] = 0;
}
