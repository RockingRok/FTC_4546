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
	int autodelay = 0;
	//decides which goal we go for
	//0 = not chosen
	//1 = center
	//2 = goals
	int goal = 0;
	eraseDisplay();

		while(startingPosition == 0)
		{
			nxtDisplayCenteredBigTextLine(1, "CHOOSE STARTING POSITION");
			nxtDisplayCenteredBigTextLine(2, "PRESS RIGHT FOR RAMP");
			nxtDisplayCenteredBigTextLine(3, "PRESS LEFT FOR PARK");
			//1 = right, 2 = left, 3 = center, 0 = gray center
			if(nNxtButtonPressed == 1)
			{

			}
		}

	return choice;
}
