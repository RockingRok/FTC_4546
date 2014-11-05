//http://www.robotc.net/wiki/NXT_Functions_Display
int userInput()
{
	//this will return which program to run
	int choice = 0;
	//this will choose which starting position we will assume
	//0 = not chosen
	//1 = ramp
	//2 = park
	int startingPosition = 0;
	//will choose autonomous delay
	//value here decides what they delay is
	//0 = not chosen
	//1 = 5 seconds
	//2 = 10 seconds
	int autodelay = 0;
	//decides which goal we go for
	//0 = not chosen
	//1 = center
	//2 = goals
	int goal = 0;
	eraseDisplay();

	while(startingPosition == 0)
	{
		nxtDisplayTextLine(1, "CHOOSE START");
		nxtDisplayTextLine(2, "PRESS RIGHT");
		nxtDisplayTextLine(3, "FOR RAMP");
		nxtDisplayTextLine(5, "PRESS LEFT");
		nxtDisplayTextLine(6, "FOR PARK");
		//1 = right, 2 = left, 3 = center, 0 = gray center
		if(nNxtButtonPressed == 1)
		{
			startingPosition = 1;
		}
		if(nNxtButtonPressed == 2)
		{
			startingPosition = 2;
		}
	}
	eraseDisplay();

	wait1Msec(1000);

	while(autodelay == 0)
	{
		nxtDisplayTextLine(1, "CHOOSE DELAY");
		nxtDisplayTextLine(2, "PRESS RIGHT");
		nxtDisplayTextLine(3, "FOR 5 seconds");
		nxtDisplayTextLine(5, "PRESS LEFT");
		nxtDisplayTextLine(6, "FOR 10 seconds");
		//1 = right, 2 = left, 3 = center, 0 = gray center
		if(nNxtButtonPressed == 1)
		{
			autodelay = 5;
		}
		if(nNxtButtonPressed == 2)
		{
			autodelay = 10;
		}
	}
	eraseDisplay();

	wait1Msec(1000);

	while(goal == 0)
	{
		nxtDisplayTextLine(1, "CHOOSE GOAL");
		nxtDisplayTextLine(2, "PRESS RIGHT");
		nxtDisplayTextLine(3, "FOR CENTER");
		nxtDisplayTextLine(5, "PRESS LEFT");
		nxtDisplayTextLine(6, "FOR GOALS");
		//1 = right, 2 = left, 3 = center, 0 = gray center
		if(nNxtButtonPressed == 1)
		{
			goal = 1;
		}
		if(nNxtButtonPressed == 2)
		{
			goal = 2;
		}
	}
	eraseDisplay();

	wait1Msec(1000);
	nxtDisplayTextLine(1, "Current Settings");
	if(startingPosition == 1)
	{
		nxtDisplayTextLine(2, "GOAL: ");
	}
	if(startingPosition == 2)
	{

	}

	return choice;
}
