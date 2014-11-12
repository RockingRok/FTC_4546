/*=================================================================
											New Movement Method
in this method, the variable trueHeading now means intended
heading, rather than what the measure is in degrees. it will
theoretically help the robot function better.
=================================================================*/
#include "hitechnic-gyro.h";
#include "hitechnic-irseeker-v2.h"



void newMove(int encoderValue, int power, int time = 5000)
{
	HTGYROstartCal(gyroSensor); //calibrates the gyro to set its current position to "default"
	float heading = 0; //what our gyro will read
	float trueHeading = HTGYROreadrot(gyroSensor); //what it truly is in our case


	wait1Msec(500); //wait for the gyro to complete its calibration
	clearTimer(T1); //clear the nxt timer so we can use it

	if(encoderValue > 0) //if the encoder value is positive, we are going forward
	{
		nMotorEncoder[motorFR] = 0; //motor encoder reset to 0 before going forward
		nMotorEncoder[motorFL] = 0; //motor encoder reset to 0 before going forward
		//this is where the magic happens, while we are not reaching our distance yet and we still have time
		while((getEncoderAverage(-nMotorEncoder[motorFR], -nMotorEncoder[motorFL]) < encoderValue) && (time1[T1] < time))
		{
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			//trueHeading += heading * (2/100); //converts the current rotation value to the true degree

			//if the robot is not +1/-1 its forward heading
			if(!(heading == trueHeading))
			{
				if(trueHeading + 5 < heading) //if the robot drifted to the right
				{
					setMotors(power/4, power); //sets the motors to adjust
				}

				if(trueHeading > heading + 5) //if the robot drifted to the left
				{
					setMotors(power, power/4); //sets the motors to adjust
				}
			}
			else //if the robot did not drift
			{
				setMotors(power, power); //sets the motors to simply go forward
			}
			wait1Msec(20); // gyro can check its rotation value every 20 ms
		}
	}

	if(encoderValue < 0)
	{
		nMotorEncoder[motorFR] = 0; //motor encoder reset to 0 before going forward
		nMotorEncoder[motorFL] = 0; //motor encoder reset to 0 before going forward
		while((getEncoderAverage(-nMotorEncoder[motorFR], -nMotorEncoder[motorFL]) > encoderValue) && (time1[T1] < time))
		{
			heading = HTGYROreadRot(gyroSensor); //get the current rotation degree
			//trueHeading += heading * (20/1000); //converts the current rotation value to the true degrees

			if(!(heading == trueHeading))
			{
				if(trueHeading < heading) //if the robot drifted to the left
				{
					setMotors(-power, -power/4);
				}

				if(trueHeading > heading) //if the robot drifted to the right
				{
					setMotors(-power/4, -power);
				}
			}
			else //if the robot did not drift
			{
				setMotors(-power, -power);
			}
			wait1Msec(20); // gyro can check its rotation value every 20 ms
		}
	}

	stopMotors();
}
