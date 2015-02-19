#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorI2CCustom)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFlipper,  tmotorTetrix, openLoop, reversed)
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

void initializeRobot()
{
  servo[pivotServo] = 255;
	servo[grabberRight] = 140;
	servo[grabberLeft] = 120;
	servo[latchServo] = 64;
	nMotorEncoder[motorLift2] = 0;
	wait1Msec(200);
	return;
}
task main()
{
	waitForStart();
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
			wait1Msec(300);
			servo[latchServo] = 64;
			wait1Msec(100);
			nMotorEncoder[motorLift2] = 0;
			wait1Msec(100);
			clearTimer(T1);
			servo[pivotServo] = 255;
			servo[latchServo] = 64;
			while((nMotorEncoder[motorLift2] > -4800) && time1[T1] < 3000)
			{
				motor[motorLift] = -100;
				motor[motorLift2] = -100;
			}
			motor[motorLift] = 0;
			motor[motorLift2] = 0;
			while(!(nNxtButtonPressed == 1)){}
			servo[pivotServo] = 0;
			wait1Msec(1000);
			servo[latchServo] = 126;
			wait1Msec(1000);
			while(!(nNxtButtonPressed == 1)){}
			servo[latchServo] = 64;
			servo[pivotServo] = 255;
			wait1Msec(1000);
			clearTimer(T1);
			while((nMotorEncoder[motorLift2] < -1000) && time1[T1] < 3000)
			{
				motor[motorLift] = 100;
				motor[motorLift2] = 100;
			}
			motor[motorLift] = 0;
			motor[motorLift2] = 0;
		}
	}
}
