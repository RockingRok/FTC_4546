//CONTRIBUTORS: FTC 4546
#include "hitechnic-gyro.h";
#include "hitechnic-irseeker-v2.h"

//gets encoder average of the left and right motors
int getEncoderAverage(int leftMotor, int rightMotor)
{
	return (leftMotor + rightMotor) / 2;
}

//gets the current IR value
int getIR()
{
	return HTIRS2readACDir(irSensor);
}

//threshhold method for going forward/backward
//essentially, if the robot is not +1/-1 degrees of going exactly forward it will return false
bool gyroThreshhold(float heading, int trueValue, int threshhold)
{
	if(heading > 0)
	{
		if((heading > (trueValue + threshhold)) || (heading > (trueValue - threshhold)))
		{
			return false;
		}
	}
	if(heading < 0)
	{
		if((heading < (trueValue + threshhold)) || (heading < (trueValue - threshhold)))
		{
			return false;
		}
	}
	return true;
}

//method for rotational threshhold
bool gyroThreshRot(float heading, int trueValue, int threshhold)
{
	if(trueValue < 0)
	{
		if(heading > trueValue)
		{
			return false;
		}
	}
	if(trueValue > 0)
	{
		if(heading < trueValue)
		{
			return false;
		}
	}
	return true;

}

//gets our "position" on the field through our IR sensors
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

//our way to move forward and backwards while allowing the gyro to adjust the robot if needed
void move(int encoderValue, int power, int time = 5000)
{
	float heading = 0; //what our gyro will read
	float trueHeading = 0; //what it truly is in our case
	HTGYROstartCal(gyroSensor); //calibrates the gyro to set its current position to "default"

	wait1Msec(500); //wait for the gyro to complete its calibration
	clearTimer(T1); //clear the nxt timer so we can use it

	if(encoderValue > 0) //if the encoder value is positive, we are going forward
	{
		nMotorEncoder[motorFR] = 0; //motor encoder reset to 0 before going forward
		nMotorEncoder[motorFL] = 0; //motor encoder reset to 0 before going forward
		//this is where the magic happens, while we are not reaching our distance yet and we still have time
		while((getEncoderAverage(nMotorEncoder[motorFR], nMotorEncoder[motorFL]) < encoderValue) && (time1[T1] < time))
		{
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			trueHeading += heading * (20/1000); //converts the current rotation value to the true degree

			//if the robot is not +1/-1 its forward heading
			if(!gyroThreshhold(trueHeading, 0, 1))
			{
				if(trueHeading > 0) //if the robot drifted to the right
				{
					setMotors(power/4, power); //sets the motors to adjust
				}

				if(trueHeading < 0) //if the robot drifted to the left
				{
					setMotors(power, power/4); //sets the motors to adjust
				}
			}
			else //if the robot did not drift
			{
				setMotors(power, power); //sets the motors to simply go forward
			}
			wait1Msec(20); // gyro can check its rotation value every 20 ms
		}
	}

	if(encoderValue < 0)
	{
		nMotorEncoder[motorFR] = 0; //motor encoder reset to 0 before going forward
		nMotorEncoder[motorFL] = 0; //motor encoder reset to 0 before going forward
		while((getEncoderAverage(nMotorEncoder[motorFR], nMotorEncoder[motorFL]) > encoderValue) && (time1[T1] < time))
		{
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			trueHeading += heading * (20/1000); //converts the current rotation value to the true degrees

			if(!gyroThreshhold(trueHeading, 0, 1))
			{
				if(trueHeading > 0) //if the robot drifted to the left
				{
					setMotors(-power, -power/4);
				}

				if(trueHeading < 0) //if the robot drifted to the right
				{
					setMotors(-power/4, -power);
				}
			}
			else //if the robot did not drift
			{
				setMotors(-power, -power);
			}
			wait1Msec(20); // gyro can check its rotation value every 20 ms
		}
	}

	stopMotors();
}

void turn(int power, int deg, int time = 5000)
{
	float heading = 0;
	float trueHeading = 0;

	HTGYROstartCal(gyroSensor);

	wait1Msec(500);
	clearTimer(T1);
	//turning right
	if(deg > 0)
	{
		while(!gyroThreshRot(trueHeading, deg, 1) && (time1[T1] < time))
		{
			setMotors(power, 0); //left and right
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			trueHeading += heading * (20/1000); //converts the current rotation value to the true degrees
			wait1Msec(20);
		}
		stopMotors();
	}
	//turning left
	if(deg < 0)
	{
		while(!gyroThreshRot(trueHeading, deg, 1) && (time1[T1] < time))
		{
			setMotors(0, power); //left and right
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			trueHeading += heading * (20/1000); //converts the current rotation value to the true degrees
			wait1Msec(20);
		}
		stopMotors();
	}
	stopMotors();
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
	servo[pivotServo] = 0;
	servo[latchServo] = 126;
	wait1Msec(500);
	servo[latchServo] = 64;
	servo[pivotServo] = 160;
	while((nMotorEncoder[motorLift] > 0) && time1[T1] < time)
	{
		motor[motorLift] = -100;
	}
	motor[motorLift] = 0;
}

void grabber(bool x)
{
	//true, AKA Grab
	if(x)
	{
			servo[grabberRight] = 255;
			servo[grabberLeft] = 0;
	}
	else
	{
			servo[grabberRight] = 140;
			servo[grabberLeft] = 120;
	}
}
