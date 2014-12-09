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
	//RC = Ramp Center
	waitForStart();
	adjustLift(500);
	move(25, 1500, 2200);
	rotTurn(50, -90);
	move(50, 1200, 1200);
	if(getPositionRamp() == 1)
	{
		rotTurn(50, -90);
		move(50, 500, 600);
		rotTurn(50, 100);
		move(60, 500, 1000);
	}
	else if(getPositionRamp() == 2)
	{
		rotTurn(50, -10);
		move(60, 1000, 2000);
	}
	else if(getPositionRamp() == 3)
	{
		rotTurn(50, -45);
		move(50, 730, 1000);
		rotTurn(50, 90);
		rotTurn(50, 45);
		move(60, 1000, 2000);
	}
}
