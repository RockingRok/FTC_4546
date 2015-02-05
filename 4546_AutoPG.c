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
	//PG = Parking Goal
	waitForStart();
	grabber(false);
	servo[pivotServo] = 255;
	servo[latchServo] = 64;
	adjustLiftUp(200);
	move(-40, -1000, 3000);
	rotTurn(80, 30); //5-25 degrees, turns for us so we don't have to line it up
	move(-45, -3000, 5000); // move backwards
	rotTurn(80, -25); //move back to needed position
	move(-35, -2500, 5000);
	grabber(true); //grabs the goal
	rotTurn(100, 4);
	move(50, 4100, 6000); // moves back to park
	wait1Msec(300);
	rotTurn(70, -90);
	rotTurn(70, -80);
	move(-45, -5000, 2000);
	autonomousLift(5000);
	grabber(false);
}
