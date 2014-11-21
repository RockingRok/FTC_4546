#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     irSensor,       sensorI2CCustom)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorLift,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorFlipper,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    pivotServo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    grabberLeft,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    grabberRight,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    latchServo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "library.h"
#include "4546_AutoChooser.h"
#include "JoystickDriver.c"

// since the gearing of the motors is weird, one full wheel spin is now approx. 187 for the encoder value!

task main()
{
	//PG = Parking Goal
	//userInput();
	waitForStart();
	grabber(false);
	adjustLift(500);
	moveTo(-20, -1000, 1000);
	arcTurn(40, 10); //5-25 degrees, turns for us so we don't have to line it up
	moveTo(-45, -730, 3000); // move backwards
	arcTurn(40, -10); //move back to needed position
	moveTo(-45, -3000, 5000);
	moveTo(-20, -500, 1000); //moves forward slower to not let goal roll away

	wait1Msec(10);
	grabber(true); //grabs the goal
	wait1Msec(10);

	moveTo(45, 3000, 5000); // moves back to park
	rotTurn(50, 90);
	rotTurn(50, 90);
	arcTurn(40, -10);
	moveTo(45, 730, 3000);
	arcTurn(40, 10);
	moveTo(20, 500, 500);

	grabber(false);

}
