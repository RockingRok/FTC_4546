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
	grabber(false);
	move(-30, -1195, 2000, .5); //-1000
	rotTurn(80, 45);
	move(-30, -1430, 2000, .3); //-1000
	rotTurn(80, -45);
	move(-30, -3520, 5000, .5); //-2500
	move(-30, -500, 2000, .5);
	grabber(true);
	move(40, 3920, 5000, .5);
	rotTurn(100, -165);
	move(-40, -1600, 2500);
	autonomousLift(2500);
}
