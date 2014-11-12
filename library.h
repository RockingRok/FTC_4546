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
		return 1;
	}
	return 3;
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

float heading = 0;

float valInRange(float val, float threshold = 1.0) {
	return (abs(val) <= threshold) ? 0 : val;
}
bool isInRange(float heading, float targetHeading, float threshold = 1.0) {
	return abs(heading - targetHeading) <= threshold;
}
void moveTo(int power, int deg, float threshold = 2.0, long time = 5000, float cor = 4.0) {
	heading = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;

	wait1Msec(500);
	HTGYROstartCal(gyroSensor);
	wait1Msec(500);

	clearTimer(T1);

	if (power > 0) {
		while (time1[T1] < time && getEncoderAverage(-nMotorEncoder[motorFL], -nMotorEncoder[motorBL]) < deg) {
			// Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
			heading += valInRange(HTGYROreadRot(gyroSensor), threshold) * (float)(20 / 1000.0);

			// Checks if the gyro is outside of the specified threshold (1.0)
			if (isInRange(heading, 0, threshold)) {
				setMotors(power, power);
			}

			// If not, lower the speed of the required side of the robot to adjust back to 0
			else {
				if (heading > 0) {
					setMotors(power / cor, power);
				}
				if (heading < 0) {
					setMotors(power, power / cor);
				}
			}
			wait1Msec(20);
		}
	}

	else {
		while (time1[T1] < time && getEncoderAverage(-nMotorEncoder[motorFL], -nMotorEncoder[motorFR]) > deg) {
			// Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
			heading += valInRange(HTGYROreadRot(gyroSensor), threshold) * (float)(20 / 1000.0);

			// Checks if the gyro is outside of the specified threshold (1.0)
			if (isInRange(heading, 0, threshold)) {
				setMotors(power, power);
			}

			// If not, lower the speed of the required side of the robot to adjust back to 0
			else {
				if (heading > 0) {
					setMotors(power, (power / cor));
				}
				if (heading < 0) {
					setMotors((power / cor), power);
				}
			}

			wait1Msec(20);
		}
	}

	stopMotors();
}

void arcTurn(int power, int deg, int time = 3000) {

	// 90 Degree Modifier
	if (abs(deg) == 90) {
		int modifier = deg * 14/9;
		deg = modifier;
	}

	// 45 Degree Modifier
	else if (abs(deg) == 45) {
		int modifier = deg * 13/9;
		deg = modifier;
	}

	heading = 0;
	clearTimer(T1);
	wait1Msec(500);
	HTGYROstartCal(gyroSensor);
	wait1Msec(500);
	// Forward arcTurn
	if (power > 0) {
		if (deg > 0) {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(gyroSensor) * (float)(20 / 1000.0);
				setMotors(power, 0);
				wait1Msec(20);
			}
		}

		else {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(gyroSensor) * (float)(20 / 1000.0);
				setMotors(0, power);
				wait1Msec(20);
			}
		}
	}
	stopMotors();
}

void lifter(int deg, int time = 5000)
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
	servo[latchServo] = 126;
	wait1Msec(2000);
	servo[latchServo] = 64;
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

void grabber(bool grab)
{
	if(grab)
	{
			servo[grabberRight] = 200;
			servo[grabberLeft] = 55;
	}
	else
	{
			servo[grabberRight] = 140;
			servo[grabberLeft] = 120;
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

void moveIR(int ir, int power)
{
	while(!(getIR() == ir))
	{
		setMotors(power, power);
	}
}
