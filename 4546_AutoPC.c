#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorI2CCustom)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFlipper,  tmotorTetrix, openLoop)
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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "library.h"
#include "JoystickDriver.c"
task main()
{
	//waitForStart();
	clearTimer(T2);
	initialize();
	//come up to the last intersection before the center goal
	move(40, 1350, 3000);
	wait1Msec(500);
	if(getPositionPark() == 1)
	{
		centerGoal(100, 180); //183
		//while(time1[T2] < 25000){}
		rotTurn(80, 90);
		move(-50, -700, 1500);
		rotTurn(80, -90);
		move(-60, -2000, 3000);
	}
	else if(getPositionPark() == 2)
	{
		move(-50, -200, 1000);
		rotTurn(100, -45); //-39
		wait1Msec(2000);
		move(50, 1100, 3000); //1200
		//rotTurn(100, -90); //-83
		//move(50, 100, 1000);
		centerGoal(100, -90);
		//while(time1[T2] < 25000){}
		rotTurn(80, 90);
		move(-50, -700, 1500);
		rotTurn(80, -90);
		move(-60, -2000, 3000);
	}
	else if(getPositionPark() == 3)
	{
		rotTurn(100, -45);
		move(50, 1836, 3000); //2000
		centerGoal(100, -45);
		//while(time1[T2] < 25000){}
		rotTurn(80, 90);
		move(-50, -700, 1500);
		rotTurn(80, -90);
		move(-60, -2000, 3000);
	}
}