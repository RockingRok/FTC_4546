#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorFlipper,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    pivotServo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    grabberLeft,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    grabberRight,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    latchServo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


task tankDrive()
{
while(true)
{
	getJoystickSettings(joystick);
	short y1 = joystick.joy1_y1;
	short y2 = joystick.joy1_y2;
	//Moving is done forward and backward with one joystick
		if(abs(joystick.joy1_y1) >= 15)
		{
			motor[motorFL] = y1 * .7;
			motor[motorBL] = y1 * .7;
		}
		else
		{
			motor[motorFL] = 0;
			motor[motorBL] = 0;
		}
		if(abs(joystick.joy1_y2) >= 15)
		{
			motor[motorFR] = y2 * .7;
	  	motor[motorBR] = y2 * .7;
		}
	 	else
	 	{
			motor[motorFR] = 0;
			motor[motorBR] = 0;
		}
	}
}

task manipulation()
{
	while(true)
	{
		getJoystickSettings(joystick);
		//LB
		if(joy2Btn(5) == 1)
		{
			motor[motorFlipper] = 100;
		}
		//RB
		else if(joy2Btn(6) == 1)
		{
			motor[motorFlipper] = -100;
		}
		else
		{
			motor[motorFlipper] = 0;
		}
		//LT
		if(joy2Btn(8) == 1)
		{
			motor[motorLift] = 100;
		}
		//RT
		else if(joy2Btn(7) == 1)
		{
			motor[motorLift] = -100;
		}
		else
		{
			motor[motorLift] = 0;
		}
		//proposed new lift
		/*
		if(joy2Btn(8) == 1)
		{
			motor[motorLift] = 100;
			servo[pivotServo] = 180;
		}
		//RT
		else if(joy2Btn(7) == 1)
		{
			motor[motorLift] = -100;
			servo[pivotServo] = 180; // possible 220 value, have to test
		}
		else
		{
			motor[motorLift] = 0;
		}
		*/
		//Y - latch closed
		if(joy2Btn(4) == 1)
		{
			servo[latchServo] = 64;
		}
		//B - latch open
		else if (joy2Btn(3) == 1)
		{
			servo[latchServo] = 126;
		}
		//X
		if(joy2Btn(1) == 1)
		{
			servo[pivotServo] = 0;
		}
		//A
		else if(joy2Btn(2) == 1)
		{
			servo[pivotServo] = 255;
		}
		//TOP ARROW
		else if(joystick.joy2_TopHat == 0)
		{
			servo[pivotServo] = 180;
		}
		//OPEN, B
		if(joy1Btn(3) == 1)
		{
			servo[grabberRight] = 140; //140
			servo[grabberLeft] = 120; //120
			wait1Msec(500);
		}
		//CLOSE, Y
		else if(joy1Btn(4) == 1)
		{
			servo[grabberRight] = 200; //255
			servo[grabberLeft] = 55; //0
			wait1Msec(500);
		}
	}
}
task main()
{
  waitForStart();   // wait for start of tele-op phase
  startTask(tankDrive);
  startTask(manipulation);
  while(true)
  {
  	wait1Msec(5);
  }
}
