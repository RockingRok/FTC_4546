#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorI2CCustom)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorLift,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorFlipper,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorLift2,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C1_1,    grabberLeft,          tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    grabberRight,         tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_4,    wireLifter,           tServoStandard)
#pragma config(Servo,  srvo_S4_C1_5,    pivotServo,           tServoStandard)
#pragma config(Servo,  srvo_S4_C1_6,    latchServo,           tServoStandard)
#include "JoystickDriver.c"
#include "library.h"
float gyro = 0.0;
bool xtoggle = false;
task tankDrive()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//IF HALF SPEED MODE ISNT ON, GO NORMAL
		if(!(joy1Btn(5) == 1))
		{
			short y1 = joystick.joy1_y1;
			short y2 = joystick.joy1_y2;
			if(abs(joystick.joy1_y1) >= 15)
			{
				motor[motorFL] = y1 * .7;
				motor[motorBL] = y1 * .7;
			}
			else
			{
				motor[motorFL] = 0;
				motor[motorBL] = 0;
			}
			if(abs(joystick.joy1_y2) >= 15)
			{
				motor[motorFR] = y2 * .7;
				motor[motorBR] = y2 * .7;
			}
			else
			{
				motor[motorFR] = 0;
				motor[motorBR] = 0;
			}
		}
		//HALF SPEED MODE
		else
		{
			short y1modified = joystick.joy1_y1;
			short y2modified = joystick.joy1_y2;
			if(abs(joystick.joy1_y1) >= 15)
			{
				motor[motorFL] = (y1modified * .7)/2;
				motor[motorBL] = (y1modified * .7)/2;
			}
			else
			{
				motor[motorFL] = 0;
				motor[motorBL] = 0;
			}
			if(abs(joystick.joy1_y2) >= 15)
			{
				motor[motorFR] = (y2modified * .7)/2;
				motor[motorBR] = (y2modified * .7)/2;
			}
			else
			{
				motor[motorFR] = 0;
				motor[motorBR] = 0;
			}
		}
		//FORWARDS GYRO STABILIZATION FOR TELE OP
		if(joy1Btn(2) == 1)
		{
			gyro = 0;
			stopMotors();
			wait1Msec(50);
			HTGYROstartCal(gyroSensor);
			while(joy1Btn(2) == 1)
			{
				gyro += HTGYROreadRot(gyroSensor) * (10/1000.0);
				if(gyro > 1)
				{
					setMotors(25, 100);
				}
				else if(gyro < -1)
				{
					setMotors(100, 25);
				}
				else
				{
					setMotors(100, 100);
				}
				wait1Msec(10);
			}
			stopMotors();
		}
		//BACKWARDS GYRO STABILIZATION FOR TELE OP
		if(joy1Btn(1) == 1)
		{
			gyro = 0;
			stopMotors();
			wait1Msec(50);
			HTGYROstartCal(gyroSensor);
			while(joy1Btn(1) == 1)
			{
				gyro += HTGYROreadRot(gyroSensor) * (10/1000.0);
				if(gyro > 1)
				{
					setMotors(-100, -25);
				}
				else if(gyro < -1)
				{
					setMotors(-25, -100);
				}
				else
				{
					setMotors(-100, -100);
				}
				wait1Msec(10);
			}
			stopMotors();
		}
	}
}

task manipulation()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//LB, FLIP IN
		if(joy2Btn(5) == 1)
		{
			motor[motorFlipper] = 100;
		}
		//RB, FLIP OUT
		else if(joy2Btn(6) == 1)
		{
			motor[motorFlipper] = -100;
		}
		//BOTTOM ARROW, HALF SPEED FLIPPERS
		else if(joystick.joy2_TopHat == 4)
		{
			motor[motorFlipper] = 50;
		}
		else
		{
			motor[motorFlipper] = 0;
		}
		//RT, MAKE LIFT GO DOWN
		if(joy2Btn(8) == 1)
		{
			motor[motorLift] = 100;
			motor[motorLift2] = 100;
		}
		//LT, MAKE LIFT GO UP
		else if(joy2Btn(7) == 1)
		{
			motor[motorLift] = -100;
			motor[motorLift2] = -100;
		}
		else
		{
			motor[motorLift] = 0;
			motor[motorLift2] = 0;
		}
		//Y, LATCH IS CLOSED
		if(joy2Btn(4) == 1)
		{
			servo[latchServo] = 64;
		}
		//B, LATCH IS OPEN
		else if (joy2Btn(3) == 1)
		{
			servo[latchServo] = 126;
		}
		//X, IF IT IS DOWN THEN GO UP
		if(joy2Btn(1) == 1 && !xtoggle)
		{
			servo[pivotServo] = 24;
			xtoggle = true;
			wait1Msec(200);
		}
		//X, IF IT IS UP THEN GO DOWN
		else if(joy2Btn(1) == 1 && xtoggle)
		{
			servo[pivotServo] = 255;
			xtoggle = false;
			wait1Msec(200);
		}
		//A, BUCKET IS DOWN
		else if(joy2Btn(2) == 1)
		{
			servo[pivotServo] = 255;
		}
		//TOP ARROW, ANGLED BUCKET
		else if(joystick.joy2_TopHat == 0)
		{
			servo[pivotServo] = 180;
		}
		//FALSE GRABBERS, B
		if(joy1Btn(3) == 1)
		{
			servo[grabberRight] = 140;
			servo[grabberLeft] = 120;
			wait1Msec(50);
		}
		//TRUE GRABBERS, Y
		else if(joy1Btn(4) == 1)
		{
			servo[grabberRight] = 245;
			servo[grabberLeft] = 10;
			wait1Msec(50);
		}
	}
}
void initializeRobot()
{
  servo[pivotServo] = 255;
	servo[grabberRight] = 140;
	servo[grabberLeft] = 120;
	servo[latchServo] = 64;
	nMotorEncoder[motorLift] = 0;
	wait1Msec(200);
  return;
}
task main()
{
	waitForStart();
	initializeRobot();
	startTask(tankDrive);
	startTask(manipulation);
	while(true)
	{
		wait1Msec(5);
	}
}
