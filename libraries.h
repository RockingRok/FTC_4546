#include "hitechnic-gyro.h"
#include "hitechnic-irseeker-v2.h"

void stopMotors()
{
	motor[motorBR] = 0;
	motor[motorFR] = 0;
	motor[motorBL] = 0;
	motor[motorFL] = 0;
}

void startMotors(int speed)
{
	motor[motorBR] = speed;
	motor[motorFR] = speed;
	motor[motorBL] = speed;
	motor[motorFL] = speed;
}

bool irSeeker()
{

}
