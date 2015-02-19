#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorI2CCustom)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFlipper,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorLift,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C1_1,    pivotServo,           tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    latchServo,           tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    grabberRight,         tServoStandard)
#pragma config(Servo,  srvo_S4_C1_6,    grabberLeft,          tServoStandard)
#include "JoystickDriver.c"
#include "hitechnic-gyro.h";
task baseDriver()
{
	float gyro = 0.0;
	while(true)
	{
		//IF HALF SPEED MODE ISNT ON, GO NORMAL
		if(!(joy1Btn(5) == 1))
		{
			if(abs(joystick.joy1_y1) >= 15)
			{
				motor[motorFL] = joystick.joy1_y1 * 0.7;
				motor[motorBL] = joystick.joy1_y1 * 0.7;
			}
			else
			{
				motor[motorFL] = 0;
				motor[motorBL] = 0;
			}
			if(abs(joystick.joy1_y2) >= 15)
			{
				motor[motorFR] = joystick.joy1_y2 * 0.7;
				motor[motorBR] = joystick.joy1_y2 * 0.7;
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
			if(abs(joystick.joy1_y1) >= 15)
			{
				motor[motorFL] = joystick.joy1_y1 * 0.35;
				motor[motorBL] = joystick.joy1_y1 * 0.35;
			}
			else
			{
				motor[motorFL] = 0;
				motor[motorBL] = 0;
			}
			if(abs(joystick.joy1_y2) >= 15)
			{
				motor[motorFR] = joystick.joy1_y2 * 0.35;
				motor[motorBR] = joystick.joy1_y2 * 0.35;
			}
			else
			{
				motor[motorFR] = 0;
				motor[motorBR] = 0;
			}
		}
		while(joy1Btn(5))
		{
			motor[motorFL] = -100;
			motor[motorBL] = -100;
			motor[motorFR] = 100;
			motor[motorBR] = 100;
		}
		while(joy1Btn(6))
		{
			motor[motorFL] = 100;
			motor[motorBL] = 100;
			motor[motorFR] = -100;
			motor[motorBR] = -100;
		}
		//FORWARDS GYRO STABILIZATION FOR TELE OP
		if(joy1Btn(2) == 1)
		{
			gyro = 0;
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
			wait1Msec(50);
			HTGYROstartCal(gyroSensor);
			wait1Msec(50);
			while(joy1Btn(2) == 1)
			{
				gyro += HTGYROreadRot(gyroSensor) * (10/1000.0);
				if(gyro > 1)
				{
					motor[motorFL] = 25;
					motor[motorBL] = 25;
					motor[motorFR] = 100;
					motor[motorBR] = 100;
				}
				else if(gyro < -1)
				{
					motor[motorFL] = 100;
					motor[motorBL] = 100;
					motor[motorFR] = 25;
					motor[motorBR] = 25;
				}
				else
				{
					motor[motorFL] = 100;
					motor[motorBL] = 100;
					motor[motorFR] = 100;
					motor[motorBR] = 100;
				}
				wait1Msec(10);
			}
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
		}
		//BACKWARDS GYRO STABILIZATION FOR TELE OP
		if(joy1Btn(1) == 1)
		{
			gyro = 0;
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
			wait1Msec(50);
			HTGYROstartCal(gyroSensor);
			wait1Msec(50);
			while(joy1Btn(1) == 1)
			{
				gyro += HTGYROreadRot(gyroSensor) * (10/1000.0);
				if(gyro > 1)
				{
					motor[motorFL] = -100;
					motor[motorBL] = -100;
					motor[motorFR] = -25;
					motor[motorBR] = -25;
				}
				else if(gyro < -1)
				{
					motor[motorFL] = -25;
					motor[motorBL] = -25;
					motor[motorFR] = -100;
					motor[motorBR] = -100;
				}
				else
				{
					motor[motorFL] = -100;
					motor[motorBL] = -100;
					motor[motorFR] = -100;
					motor[motorBR] = -100;
				}
				wait1Msec(10);
			}
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
		}
	}
}

task servos()
{
	while(true)
	{
		//X, BUCKET IS UP
		if(joy2Btn(1) == 1)
		{
			servo[pivotServo] = 0;
		}
		//A, BUCKET IS DOWN
		if(joy2Btn(2) == 1)
		{
			servo[pivotServo] = 255;
		}
		//B, LATCH IS OPEN
		if (joy2Btn(3) == 1)
		{
			servo[latchServo] = 126;
		}
		//Y, LATCH IS CLOSED
		if(joy2Btn(4) == 1)
		{
			servo[latchServo] = 64;
		}
		//FALSE GRABBERS, B
		if(joy1Btn(3) == 1)
		{
			servo[grabberRight] = 245;
			servo[grabberLeft] = 10;
		}
		//TRUE GRABBERS, Y
		if(joy1Btn(4) == 1)
		{
			servo[grabberRight] = 145;
			servo[grabberLeft] = 125;
		}
	}
}

task lift()
{
	while(true)
	{
		getJoystickSettings(joystick);
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
	}
}

task flippers()
{
	while(true)
	{
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
			motor[motorFlipper] = -50;
		}
		else
		{
			motor[motorFlipper] = 0;
		}
	}
}

void initializeRobot()
{
  servo[pivotServo] = 255;
	servo[grabberRight] = 245;
	servo[grabberLeft] = 10;
	servo[latchServo] = 64;
	nMotorEncoder[motorLift] = 0;
	wait1Msec(200);
}

task main()
{
	waitForStart();
	initializeRobot();
	startTask(lift);
	startTask(baseDriver);
	startTask(flippers);
	startTask(servos);
	while(true){}
}
