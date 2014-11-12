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
	//waitForStart();
	grabber(false);
	moveTo(-50, -5000);
	moveTo(-35, -500);
	lifter(-10000);
	grabber(true);
	moveTo(25, 4500);
	arcTurn(25, 90);
	arcTurn(25, 90);

	/*
	moveTo(-25, -1600);
	grabber(true);
	moveTo(25, 1600);
	arcTurn(25, 180);
	lifter(999, 3000);
	grabber(false);
	arcTurn(25, 180);
	moveTo(-50, -1500);
	grabber(true);
	moveTo(50, 1500);
	arcTurn(25, 180);
	grabber(false);
	arcTurn(25, 180);
	moveTo(-50, -1500);
	grabber(true);
	moveTo(50, 1500);
	arcTurn(25, 180);
	grabber(false);
	*/

}