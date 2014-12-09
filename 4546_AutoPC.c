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
#include "library.h"
#include "JoystickDriver.c"
task main()
{
	//PC = Parking Center
	waitForStart();
	adjustLift(500);
	move(40, 700, 3000);
	wait1Msec(50);
	if(getPositionPark() == 1)
	{
		rotTurn(70, 90);
		move(50, 300, 1000);
		rotTurn(70, -100);
		move(60, 800, 1500);
	}
	else if(getPositionPark() == 2)
	{
		rotTurn(100, 45);
		move(50, 800, 2000);
		rotTurn(100, -90);
		move(50, 300, 2000);
		rotTurn(100, -90);
		move(50, 500, 1000);
	}
	else if(getPositionPark() == 3)
	{
		rotTurn(100, 45);
		move(50, 800, 2000);
		rotTurn(100, -90);
		rotTurn(100, -45);
		move(60, 1000, 3000);
	}
}
