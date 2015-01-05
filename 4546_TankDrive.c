#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S2,     irSensor,       sensorI2CCustom)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorLift,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorFlipper,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_2,    grabberLeft,          tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    grabberRight,         tServoStandard)
#pragma config(Servo,  srvo_S4_C1_4,    wireLifter,           tServoStandard)
#pragma config(Servo,  srvo_S4_C1_5,    pivotServo,           tServoStandard)
#pragma config(Servo,  srvo_S4_C1_6,    latchServo,           tServoStandard)
#include "JoystickDriver.c"
#include "library.h"
float gyro = 0.0;
float liftAvg = 0.0;
task tankDrive()
{
	while(true)
	{
		getJoystickSettings(joystick);
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
		while(joy1Btn(5) == 1)
		{
			getJoystickSettings(joystick);
			short y1 = joystick.joy1_y1;
			short y2 = joystick.joy1_y2;
			if(abs(joystick.joy1_y1) >= 15)
			{
				motor[motorFL] = (y1 * .7)/2;
				motor[motorBL] = (y1 * .7)/2;
			}
			else
			{
				motor[motorFL] = 0;
				motor[motorBL] = 0;
			}
			if(abs(joystick.joy1_y2) >= 15)
			{
				motor[motorFR] = (y2 * .7)/2;
				motor[motorBR] = (y2 * .7)/2;
			}
			else
			{
				motor[motorFR] = 0;
				motor[motorBR] = 0;
			}
		}
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
					setMotors(50, 100);
				}
				else if(gyro < -1)
				{
					setMotors(100, 50);
				}
				else
				{
					setMotors(100, 100);
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
		//LB
		if(joy2Btn(5) == 1)
		{
			motor[motorFlipper] = 100;
		}
		//RB
		else if(joy2Btn(6) == 1)
		{
			motor[motorFlipper] = -100;
		}
		//BOTTOM ARROW, HALF SPEED FLIPPERS
		else if(joystick.joy2_TopHat == 4)
		{
			servo[motorFlipper] = 50;
		}
		else
		{
			motor[motorFlipper] = 0;
		}
		//LT
		if(joy2Btn(8) == 1)
		{
			motor[motorLift] = 100;
			//motor[motorLift2] = 100;
		}
		//RT
		else if(joy2Btn(7) == 1)
		{
			motor[motorLift] = -100;
			//motor[motorLift2] = -100;
		}
		/*
		//top right arrow, top goal
		else if(joystick.joy2_TopHat == 1)
		{
			servo[pivotServo] = 180;
			liftAvg = (nMotorEncoder[motorLift] + nMotorEncoder[motorLift2]) / 2
			if(!(liftAvg == -10000))
			{
				if(liftAvg > -10000)
				{
					motor[motorLift] = 100;
					motor[motorLift2] = 100;
				}
				if(liftAvg < -10000)
				{
					motor[motorLift] = -100;
					motor[motorLift2] = -100;
				}
			}
		}
		//right arrow, middle goal
		else if(joystick.joy2_TopHat == 2)
		{
			servo[pivotServo] = 180;
			liftAvg = (nMotorEncoder[motorLift] + nMotorEncoder[motorLift2]) / 2
			if(!(liftAvg == -7000))
			{
				if(liftAvg > -7000)
				{
					motor[motorLift] = 100;
					motor[motorLift2] = 100;
				}
				if(liftAvg < -7000)
				{
					motor[motorLift] = -100;
					motor[motorLift2] = -100;
				}
			}
		}
		//bottom right arrow, short goal
		else if(joystick.joy2_TopHat == 3)
		{
			servo[pivotServo] = 180;
			liftAvg = (nMotorEncoder[motorLift] + nMotorEncoder[motorLift2]) / 2
			if(!(liftAvg == -3400))
			{
				if(liftAvg > -3400)
				{
					motor[motorLift] = 100;
					motor[motorLift2] = 100;
				}
				if(liftAvg < -3400)
				{
					motor[motorLift] = -100;
					motor[motorLift2] = -100;
				}
			}
		}
		*/
		else
		{
			motor[motorLift] = 0;
			//motor[motorLift2] = 0;
		}
		//Y - latch closed
		if(joy2Btn(4) == 1)
		{
			servo[latchServo] = 64;
		}
		//B - latch open
		else if (joy2Btn(3) == 1)
		{
			servo[latchServo] = 126;
		}
		//X
		if(joy2Btn(1) == 1)
		{
			servo[pivotServo] = 0;
		}
		//A
		else if(joy2Btn(2) == 1)
		{
			servo[pivotServo] = 255;
		}
		//TOP ARROW
		else if(joystick.joy2_TopHat == 0)
		{
			servo[pivotServo] = 180;
		}
		//OPEN, B
		if(joy1Btn(3) == 1)
		{
			servo[grabberRight] = 140; //140
			servo[grabberLeft] = 120; //120
			wait1Msec(50);
		}
		//CLOSE, Y
		else if(joy1Btn(4) == 1)
		{
			servo[grabberRight] = 200; //255
			servo[grabberLeft] = 55; //0
			wait1Msec(50);
		}
	}
}
task main()
{
	waitForStart();   // wait for start of tele-op phase
	servo[wireLifter] = 55;
	nMotorEncoder[motorLift] = 0;
	//nMotorEncoder[motorLift2] = 0;
	wait1Msec(5);
	startTask(tankDrive);
	startTask(manipulation);
	while(true)
	{
		wait1Msec(5);
	}
}
