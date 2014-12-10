int HZb = 950;

void DOT()
{

	playTone(HZb,7);
	playTone(0,7);
	sleep(140);
}
void DASH()
{
	playTone(HZb,21);
	playTone(0,7);
	sleep(280);
}
void CSPACE()
{
	playTone(0,21);
	sleep(210);
}
task main()
{
	nVolume = 4;
	//int HZa = 4700;
	//int HZb = 0;
	//int HZc = 5300;
	//950, 3650, 4300, 4700, 5300, 7150, 8000, 12000 max
		while(true)
	{
		DOT();
		DOT();
		DOT();
		CSPACE();
		DASH();
		DASH();
		DASH();
		CSPACE();
		DOT();
		DASH();
		DOT();
		playTone(0,70);
		sleep(700);
	}
}
