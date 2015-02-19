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
task main()
{
	string activeMotor;
	string printSelected;
	int selectedMotor = 0;
	bool selected = false;
	string motors[6] =
	{
		"motorLift",
		"motorFlipper",
		"motorFL",
		"motorFR",
		"motorBL",
		"motorBR"
  };

 	eraseDisplay();
  while(true)
  {
  	wait1Msec(500);
  	while(!selected){
  		eraseDisplay();
	 		//1 = right, 2 = left, 3 = center, 0 = gray center
		  nxtDisplayTextLine(1, "Select a motor");
		  nxtDisplayTextLine(3, "Selected motor:");
		  nxtDisplayTextLine(4, motors[selectedMotor]);
		  if(nNxtButtonPressed == 1)
		  {
		  	selectedMotor++;
		  	if(selectedMotor == 6)
		  	{
		  		selectedMotor = 0;
		  	}
		  }
		  if(nNxtButtonPressed == 2)
		  {
		  	selectedMotor--;
		  	if(selectedMotor == -1)
		  	{
		  		selectedMotor = 5;
		  	}
		  }
		  if(nNxtButtonPressed == 3)
		  {
		  	selected = true;
		  }
		  wait10Msec(30);
		}
		activeMotor = motors[selectedMotor];
		eraseDisplay();
		while(selected)
	  {
	  	nxtDisplayTextLine(1, "ctrl the slctd mtr.");
		  nxtDisplayTextLine(3, "press left = backward");
		  nxtDisplayTextLine(4, "press right = forward");
		  nxtDisplayTextLine(5, "press center = rtrn to sel");
	  	if(nNxtButtonPressed == 1)
	  	{
	  		if(activeMotor == "motorLift")
	  		{
	  			motor[motorLift] = 100;
	  			motor[motorLift2] = 100;
	  		}
	  		if(activeMotor == "motorFlipper")
	  		{
	  			motor[motorFlipper] = 50;
	  		}
	  		if(activeMotor == "motorFL")
	  		{
	  			motor[motorFL] = 50;
	  		}
	  		if(activeMotor == "motorFR")
	  		{
	  			motor[motorFR] = 50;
	  		}
	  		if(activeMotor == "motorBL")
	  		{
	  			motor[motorBL] = 50;
	  		}
	  		if(activeMotor == "motorBR")
	  		{
	  			motor[motorBR] = 50;
	  		}
	  	}
	  	else if(nNxtButtonPressed == 2){
	  		if(activeMotor == "motorLift")
	  		{
	  			motor[motorLift] = -100;
	  			motor[motorLift2] = -100;
	  		}
	  		if(activeMotor == "motorFlipper")
	  		{
	  			motor[motorFlipper] = -50;
	  		}
	  		if(activeMotor == "motorFL")
	  		{
	  			motor[motorFL] = -50;
	  		}
	  		if(activeMotor == "motorFR")
	  		{
	  			motor[motorFR] = -50;
	  		}
	  		if(activeMotor == "motorBL")
	  		{
	  			motor[motorBL] = -50;
	  		}
	  		if(activeMotor == "motorBR")
	  		{
	  			motor[motorBR] = -50;
	  		}
	  	}
	  	else if(nNxtButtonPressed == 3){
	  		if(activeMotor == "motorLift")
	  		{
	  			motor[motorLift] = 0;
	  			motor[motorLift2] = 0;
	  		}
	  		if(activeMotor == "motorFlipper")
	  		{
	  			motor[motorFlipper] = 0;
	  		}
	  		if(activeMotor == "motorFL")
	  		{
	  			motor[motorFL] = 0;
	  		}
	  		if(activeMotor == "motorFR")
	  		{
	  			motor[motorFR] = 0;
	  		}
	  		if(activeMotor == "motorBL")
	  		{
	  			motor[motorBL] = 0;
	  		}
	  		if(activeMotor == "motorBR")
	  		{
	  			motor[motorBR] = 0;
	  		}
	  		selected = false;
	  	}
	  	else{
	  		if(activeMotor == "motorLift")
	  		{
	  			motor[motorLift] = 0;
	  			motor[motorLift2] = 0;
	  		}
	  		if(activeMotor == "motorFlipper")
	  		{
	  			motor[motorFlipper] = 0;
	  		}
	  		if(activeMotor == "motorFL")
	  		{
	  			motor[motorFL] = 0;
	  		}
	  		if(activeMotor == "motorFR")
	  		{
	  			motor[motorFR] = 0;
	  		}
	  		if(activeMotor == "motorBL")
	  		{
	  			motor[motorBL] = 0;
	  		}
	  		if(activeMotor == "motorBR")
	  		{
	  			motor[motorBR] = 0;
	  		}
	    }
	  }
	}
}