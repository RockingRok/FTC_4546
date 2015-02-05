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
#include "library.h"
#include "JoystickDriver.c"
task main()
{
	//PC = Parking Center
	waitForStart();
	servo[pivotServo] = 255;
	servo[latchServo] = 64;
	adjustLiftUp(200);
	move(40, 1350, 3000);
	wait1Msec(300);
	if(getPositionPark() == 1)
	{
		centerGoal();
		rotTurn(80, 90);
		move(50, 700, 1500);
		rotTurn(80, -90);
		move(60, 2000, 3000);
	}
	else if(getPositionPark() == 2)
	{
		move(-50, -200, 1000);
		rotTurn(70, -45);
		move(50, 1100, 3000);
		rotTurn(70, 90);
		centerGoal();
		rotTurn(80, 90);
		move(50, 700, 1500);
		rotTurn(80, -90);
		move(60, 2000, 3000);
	}
	else if(getPositionPark() == 3)
	{
		rotTurn(100, -45);
		move(50, 2500, 5000);
		rotTurn(100, 115);
		move(50, 500, 1000);
		centerGoal();
		//rotTurn(100, 90);
		//move(50, 700, 1500);
		//rotTurn(100, -90);
		//move(60, 2000, 3000);
		/*
		rotTurn(100, 45);
		move(50, 1500, 2000);
		rotTurn(100, -90);
		rotTurn(100, -45);
		move(60, 2000, 3000);
		*/
	}
}
