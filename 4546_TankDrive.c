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

		//HALF SPEED MODE
		while(joy1Btn(5) == 1)
		{
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
		//

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
		}
		//RT
		else if(joy2Btn(7) == 1)
		{
			motor[motorLift] = -100;
		}

		//for precise buckets
		else if(joystick.joy2_TopHat == 6)
		{
			nMotorEncoderTarget[motorLift] = -7000;
			while(joystick.joy2_TopHat == 6 && nMotorRunState[motorB] != runStateIdle)
			{
				motor[motorLift] = -100;
			}
			motor[motorLift] = 0;
		}
		else if(joystick.joy2_TopHat == 2)
		{
			nMotorEncoderTarget[motorLift] = -12000;
			while(joystick.joy2_TopHat == 2 && nMotorRunState[motorB] != runStateIdle)
			{
				motor[motorLift] = -100;
			}
			motor[motorLift] = 0;
		}

		else
		{
			motor[motorLift] = 0;
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
  wait1Msec(5);
  startTask(tankDrive);
  startTask(manipulation);
  while(true)
  {
  	wait1Msec(5);
  }
}
