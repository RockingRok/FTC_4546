//CONTRIBUTORS: FTC 4546
#include "hitechnic-gyro.h";
#include "hitechnic-irseeker-v2.h"

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

//defining one global variable instead of two in turn and move
float heading = 0;

void move(int power, int enc, int time = 5000)
{
	heading = 0;
	nMotorEncoder[motorFR] = 0;
	nMotorEncoder[motorFL] = 0;
	HTGYROstartCal(gyroSensor);
	wait1Msec(50);
	clearTimer(T1);

	//in case of our robot, going forward returns negative encoder values and backward is positive
	if(power > 0)
	{
		while(getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorFR]) > -enc && time1[T1] < time)
		{
			heading += HTGYROreadRot(gyroSensor) * (10/1000);
			if(heading > 1)
			{
				setMotors(power/2, power);
			}
			else if(heading < -1)
			{
				setMotors(power, power/2);
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
			heading += HTGYROreadRot(gyroSensor) * (10/1000);
			if(heading > 1)
			{
				setMotors(power, power/2);
			}
			else if(heading < -1)
			{
				setMotors(power/2, power);
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
void rotTurn(int power, int deg, int time = 5000)
{
	heading = 0;
	deg = deg * 8/9;
	HTGYROstartCal(gyroSensor);
	wait1Msec(50);
	clearTimer(T1);
	//rotational turn
	if(power > 0)
	{
		if(deg > 0)
		{
			while(heading < deg && time1[T1] < time)
			{
				heading += HTGYROreadRot(gyroSensor) * (10 / 1000);
				setMotors(power, -power);
				wait1Msec(10);
			}
		}
		else
		{
			while(heading > deg && time1[T1] < time)
			{
				heading += HTGYROreadRot(gyroSensor) * (10 / 1000);
				setMotors(-power, power);
				wait1Msec(10);
			}
		}
	}
	stopMotors();
}

void liftUp(int deg, int time = 5000)
{
	nMotorEncoder[motorLift] = 0;

	wait1Msec(500);
	clearTimer(T1);
	servo[pivotServo] = 180;
	while((nMotorEncoder[motorLift] > deg) && time1[T1] < time)
	{
		motor[motorLift] = -100;
	}
	motor[motorLift] = 0;
	servo[pivotServo] = 0;
	wait1Msec(1000);
}

void liftDown(int deg, int time = 5000)
{
	servo[latchServo] = 64;
	wait1Msec(2000);
	servo[latchServo] = 126;
	wait1Msec(1000);
	servo[pivotServo] = 160;
	nMotorEncoder[motorLift] = 0;
	wait1Msec(500);
	servo[pivotServo] = 180;
	clearTimer(T1);
	while((nMotorEncoder[motorLift] < abs(deg)-2000) && time1[T1] < time)
	{
		motor[motorLift] = 100;
	}
	motor[motorLift] = 0;
}

void autonomousLift(int deg, int time = 5000)
{
	nMotorEncoder[motorLift] = 0;
	wait1Msec(50);
	clearTimer(T1);
	servo[pivotServo] = 180;
	servo[latchServo] = 64;
	servo[wireLifter] = 55;
	while((nMotorEncoder[motorLift] > -deg) && time1[T1] < time)
	{
		motor[motorLift] = -100;
	}
	motor[motorLift] = 0;
	servo[pivotServo] = 10;
	wait1Msec(3000);
	servo[latchServo] = 126;
	wait1Msec(2000);
	servo[pivotServo] = 180;
	servo[latchServo] = 64;
	wait1Msec(1000);
	nMotorEncoder[motorLift] = 0;
	wait1Msec(50);
	clearTimer(T1);
	while((nMotorEncoder[motorLift] < deg/1.5) && time1[T1] < time)
	{
		motor[motorLift] = 100;
	}
}
void grabber(bool grab)
{
	if(grab)
	{
		servo[grabberRight] = 200;
		servo[grabberLeft] = 55;
		wait1Msec(50);
	}
	else
	{
		servo[grabberRight] = 140;
		servo[grabberLeft] = 120;
		wait1Msec(50);
	}
}

void adjustLift(int time)
{
	servo[latchServo] = 64;
	servo[pivotServo] = 180;
	clearTimer(T1);
	while(time1[T1] < time)
	{
		motor[motorLift] = -75;
	}
	motor[motorLift] = 0;
}
