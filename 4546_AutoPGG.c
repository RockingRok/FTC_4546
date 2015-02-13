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
#include "library.h"
#include "JoystickDriver.c"
task main()
{
	waitForStart();
	initialize();
	//move slightly forward
	move(-50, -1000, 2000);
	//turn right 45 degrees
	rotTurn(80, 45);
	//align with the second to right column
	move(-50, -1000, 2000);
	//turn staright, facing the small goal
	rotTurn(80, -45);
	//drive to the square before the small goal
	move(-50, -2000, 5000);
	//turn to face the large goal
	rotTurn(80, 45);
	//move up to the large goal
	move(-50, -1000, 2000);
	//grab the goal
	grabber(true);
	//drop the large ball in the large goal
	autonomousLift(5000);
	//move back to the square in front of the small goal
	move(50, 1000, 2000);
	//turn to face the small goal
	rotTurn(80, 135);
	//release the large goal, now behind the robot opposite the small goal
	grabber(false);

	//drop the small ball in the small goal
	//insert method to flip out the servo holding the small ball here


	//turn around, move back, and grab the small goal
	rotTurn(80, 180);
	move(-50, -1000, 5000);
	grabber(true);

	//TO DO: add code to push the goal back


	/*move(-50, -1000, 5000);
	rotTurn(80, -135);
	move(50, 1000, 2000);
	rotTurn(80, -45);
	move(50, 1000, 2000);
	autonomousLift(2500);*/
}
