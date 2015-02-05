//CONTRIBUTORS: FTC 4546
#include "hitechnic-gyro.h";
#include "hitechnic-irseeker-v2.h"

//defining one global variable instead of two in turn and move
float heading = 0;

//gets our "position" on the field through our IR sensors
int getPositionRamp()
{
	int irvalue = HTIRS2readACDir(irSensor);
	if(irvalue == 5)
	{
		return 1;
	}
	if(irvalue > 5)
	{
		return 2;
	}
	return 3;
}

int getPositionPark()
{
	int irvalue = HTIRS2readACDir(irSensor);
	if(irvalue >= 5)
	{
		return 1;
	}
	if(irvalue <= 4 && irvalue > 0)
	{
		return 2;
	}
	return 3;
}

//gets encoder average of the left and right motors
int getEncoderAverage(int leftMotor, int rightMotor)
{
	return (leftMotor + rightMotor) / 2;
}

//sets the motors to a certain left and right value
void setMotors(int left, int right)
{
	motor[motorFL] = left;
	motor[motorBL] = left;
	motor[motorFR] = right;
	motor[motorBR] = right;
}

//stops all motors from running
void stopMotors()
{
	motor[motorFL] = 0;
	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
}

void rotTurn(int power, float deg, int time = 5000)
{
	heading = 0;
	deg = deg * 8.55/9.0;
	wait1Msec(150);
	HTGYROstartCal(gyroSensor);
	wait1Msec(150);
	clearTimer(T1);
	if(power > 0)
	{
		if(deg > 0)
		{
			while(heading < deg && time1[T1] < time)
			{
				heading += HTGYROreadRot(gyroSensor) * (10.0/1000.0);
				setMotors(power, -power);
				wait1Msec(10);
			}
		}
		else if (deg < 0)
		{
			while(heading > deg && time1[T1] < time)
			{
				heading += HTGYROreadRot(gyroSensor) * (10.0/1000.0);
				setMotors(-power, power);
				wait1Msec(10);
			}
		}
	}
	stopMotors();
}

void move(int power, int enc, int time = 5000, float threshold = 1.0)
{
	heading = 0;
	nMotorEncoder[motorFR] = 0;
	nMotorEncoder[motorFL] = 0;
	wait1Msec(150);
	HTGYROstartCal(gyroSensor);
	wait1Msec(150);
	clearTimer(T1);

	//in case of our robot, going forward returns negative encoder values and backward is positive
	if(power > 0)
	{
		while(getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorFR]) > -enc && time1[T1] < time)
		{
			heading += HTGYROreadRot(gyroSensor) * (10.0/1000.0);
			if(heading > threshold)
			{
				setMotors(power/4, power);
			}
			else if(heading < -threshold)
			{
				setMotors(power, power/4);
			}
			else
			{
				setMotors(power, power);
			}
			wait1Msec(10);
		}
		stopMotors();
	}

	if(power < 0)
	{
		while(getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorFR]) < -enc && time1[T1] < time)
		{
			heading += HTGYROreadRot(gyroSensor) * (10.0/1000.0);
			if(heading > threshold)
			{
				setMotors(power, power/4);
			}
			else if(heading < -threshold)
			{
				setMotors(power/4, power);
			}
			else
			{
				setMotors(power, power);
			}
			wait1Msec(10);
		}
		stopMotors();
	}
}

void adjustLiftDown(int time)
{
	servo[latchServo] = 64;
	clearTimer(T1);
	while(time1[T1] < time)
	{
		motor[motorLift] = 75;
		motor[motorLift2] = 75;
	}
	motor[motorLift] = 0;
	motor[motorLift2] = 0;
}

void adjustLiftUp(int time)
{
	servo[latchServo] = 64;
	clearTimer(T1);
	while(time1[T1] < time)
	{
		motor[motorLift] = -75;
		motor[motorLift2] = -75;
	}
	motor[motorLift] = 0;
	motor[motorLift2] = 0;
}

void autonomousLift(int deg, int time = 5000)
{
	deg = deg / 2;
	nMotorEncoder[motorLift] = 0;
	wait1Msec(50);
	clearTimer(T1);
	servo[pivotServo] = 255;
	servo[latchServo] = 64;
	while((nMotorEncoder[motorLift] > -deg) && time1[T1] < time)
	{
		motor[motorLift] = -100;
		motor[motorLift2] = -100;
	}
	motor[motorLift] = 0;
	motor[motorLift2] = 0;
	servo[pivotServo] = 44;
	wait1Msec(1000);
	adjustLiftDown(200);
	wait1Msec(1000);
	servo[latchServo] = 126;
	wait1Msec(1000);
	adjustLiftUp(700);
	wait1Msec(1000);
	servo[pivotServo] = 255;
	servo[latchServo] = 64;
}
void grabber(bool grab)
{
	if(grab)
	{
		servo[grabberRight] = 245;
		servo[grabberLeft] = 10;
		wait1Msec(50);
	}
	else
	{
		servo[grabberRight] = 140;
		servo[grabberLeft] = 120;
		wait1Msec(50);
	}
}

void centerGoal()
{
	servo[latchServo] = 64;
	wait1Msec(1500);
	rotTurn(80, 180);
	wait1Msec(1500);
	nMotorEncoder[motorLift] = 0;
	wait1Msec(100);
	clearTimer(T1);
	servo[pivotServo] = 255;
	servo[latchServo] = 64;
	while((nMotorEncoder[motorLift] > -6800) && time1[T1] < 3000)
	{
		motor[motorLift] = -100;
		motor[motorLift2] = -100;
	}
	motor[motorLift] = 0;
	motor[motorLift2] = 0;
	servo[pivotServo] = 24;
	rotTurn(80, -8);
	move(-20, -50, 1000);
	wait1Msec(1500);
	servo[latchServo] = 126;
	wait1Msec(1500);
	rotTurn(80, 8);
	move(20, 200, 1000);
	wait1Msec(1500);
	servo[pivotServo] = 255;
	servo[latchServo] = 64;
	clearTimer(T1);
	while((nMotorEncoder[motorLift] < -1000) && time1[T1] < 3000)
	{
		motor[motorLift] = 100;
		motor[motorLift2] = 100;
	}
	motor[motorLift] = 0;
	motor[motorLift2] = 0;
	wait1Msec(100);
	rotTurn(80, -180);
	wait1Msec(500);
}
