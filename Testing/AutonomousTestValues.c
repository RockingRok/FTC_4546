#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensorR,      sensorI2CCustom)
#pragma config(Sensor, S3,     irSensorL,      sensorI2CCustom)
#pragma config(Sensor, S4,     SENSOR_GYRO,    sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorFlipper,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorLift,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

#include "hitechnic-gyro.h";
#include "hitechnic-irseeker-v2.h"

float gyro = 0;
int rightIR = 0;
int leftIR = 0;
int frEncoder = 0;
int flEncoder = 0;

task main()
{
	wait1Msec(500);
	HTGYROstartCal(SENSOR_GYRO);
	wait1Msec(500);
	while(true)
	{
		gyro = HTGYROreadRot(SENSOR_GYRO);
		rightIR = HTIRS2readACDir(irSensorR);
		leftIR = HTIRS2readACDir(irSensorL);
		frEncoder = nMotorEncoder[motorFR];
		flEncoder = nMotorEncoder[motorFL];
	}
}
