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

void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	return;
}
task main()
{
	initializeRobot();
	while(true){
		if(nNxtButtonPressed == 2){
			motor[motorFL] = 50;
			motor[motorBL] = 50;
			motor[motorFR] = 50;
			motor[motorBR] = 50;
			wait10Msec(50);
			while (!(nNxtButtonPressed == 2)){}
			stopMotors();
			wait10Msec(50);
		}
		if(nNxtButtonPressed == 3){
			motor[motorFlipper] = -50;
			wait10Msec(50);
			while (!(nNxtButtonPressed == 3)){}
			motor[motorFlipper] = 0;
			wait10Msec(50);
		}
		if(nNxtButtonPressed == 1){
			//this code should put the lift at or near its max height and then flip the bucket out.
			wait1Msec(1000);
			servo[latchServo] = 64;
			wait1Msec(1500);
			nMotorEncoder[motorLift] = 0;
			wait1Msec(100);
			clearTimer(T1);
			servo[pivotServo] = 255;
			servo[latchServo] = 64;
			while((nMotorEncoder[motorLift] > -4800) && time1[T1] < 3000)
			{
				motor[motorLift] = -100;
				motor[motorLift2] = -100;
			}
			motor[motorLift] = 0;
			motor[motorLift2] = 0;
			while(!(nNxtButtonPressed == 1)){}
			servo[pivotServo] = 24;
			wait1Msec(1000);
			servo[latchServo] = 126;
			wait1Msec(1000);
			servo[pivotServo] = 255;
			servo[latchServo] = 64;
			wait1Msec(1000);
			while(!(nNxtButtonPressed == 1)){}
			wait1Msec(1000);
			clearTimer(T1);
			while((nMotorEncoder[motorLift] < -1000) && time1[T1] < 3000)
			{
				motor[motorLift] = 100;
				motor[motorLift2] = 100;
			}
			motor[motorLift] = 0;
			motor[motorLift2] = 0;


			/*
			servo[wireLifter] = 55;
			liftUp(-5000);
			wait10Msec(500);
			servo[pivotServo] = 0;
			wait10Msec(100);
			while (!(nNxtButtonPressed == 3)){}
			//code to flip down the bucket and retract the lift.
			servo[pivotServo] = 240;
			wait10Msec(10);
			liftDown(-5000);
			*/
		}
	}
}
