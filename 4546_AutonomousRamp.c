#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     irSensor,       sensorI2CCustom)
#pragma config(Sensor, S4,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorLift,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorFlipper,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "library.h"
//#include "4546_AutoChooser.h"
//int right = 0;
//int left = 0;
	//NEW META! since the gearing of the motors is weird, one full wheel spin is now approx. 187 for the encoder value!
task main()
{
	//userInput();


	//moveOffRamp((12*187)/(4*PI), 25);  // Ramp is ~57 inches
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;

	int deg = 1000;
	int power = 50;
	while((nMotorEncoder[motorFL] < deg))// && time1[T1] < time)
	{
		motor[motorFR] = 100;


		//setMotors(power, power);
	}
	stopMotors();

	//move((15*187)/(4*PI)); //the rest of the way is ~15 inches
	//turn(-1, (4.5*PI*187)/(4*PI)); //turn 90 degrees left
	//moveTo(50, (24*187)/(4*PI));

/*
	//if the ir beacon is directly in front of the robot, move up next to the pole, face it, and move forward to knock it over.
	int centerSetting = getPosition();
	if(centerSetting == 1){
		moveTo(1, (48*187)/(4*PI), 50);
		turn(1, (4.5*PI*187)/(4*PI));
		moveTo(1, (12*187)/(4*PI), 50);
	}
	else if(centerSetting == 2){
		moveTo(1, (48*187)/(4*PI), 50);
	}
	else{};
	//else if(centerSetting == )
	*/
}
