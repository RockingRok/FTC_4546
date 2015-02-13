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
	//move off ramp all the way to the medium goal
	move(-50, -9999, 2700);
	//grab it
	grabber(true);
	//turn to the left
	rotTurn(80, -90);
	//move slightly back
	move(-50, -500, 2000);
	//drop the ball
	autonomousLift(3500);
	//turn to the correct angle to push the goal
	rotTurn(80, -45);
	//release the goal
	grabber(false);
	//turn to face the small goal
	rotTurn(80, 90); //value used to be 135
	//approach the small goal
	move(50, 700, 2000);
	//small ball arm here
	//turn 180 and grab the goal
	//rotTurn(80, 180); dont need this since the grabbers are already facing the small goal
	grabber(true);
	//move to the parking zone, one goal in tow and one being pushed
	rotTurn(80, 45); //value used to be 225
	move(-50, -5000, 5000);
	//rotTurn(80, 45);
	//move(50, 2000, 3000);
}
