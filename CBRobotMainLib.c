


/*
scaleJoystick
Function to scale a joystick value using a logarithmic like scale with a dead
band at zero.
Most of the adjustment range is used for fine control over low power settings.
The extreme end of the range provide coarse control over high power.
Large dead band around center point.
Above makes it easier to control robot at slow speeds.
Joystick values range from -128 to +127.
Speed/power settings for Tetrix motors range from -100 to +100
The physical range of motion of a joystick is quite small and it is sometimes
hard to control slow speeds. So another capability of this program to apply
a "logarithmic" scale to the joystick settings.
Addapted from RobotC.net forum post by Emilhem
*/

bool FastButton = true;
int CBMap(int Joy1, bool FastMode)
{
	static const int LogScaleFast[17] =
	{
		0,
		7,
		7,
		7,
		7,
		7,
		7,
		8,
		8,
		9,
		10,
		11,
		13,
		15,
		17,
		20,
		20
	};
	static const int LogScaleSlow[17] =
	{

		0,
		12,
		12,
		12,
		12,
		13,
		15,
		18,
		22,
		27,
		34,
		42,
		52,
		64,
		78,
		95,
		95

	};
	int Scaled = Joy1/8;
	if (FastMode && GetLiftEnc() < AutoDeployEncTop)
	{
		if (Scaled >= 0)
			Scaled = LogScaleFast[Scaled];
		else
			Scaled = - LogScaleFast[ - Scaled];
	}
	else
	{
		if (Scaled >= 0)
			Scaled = LogScaleSlow[Scaled];
		else
			Scaled = - LogScaleSlow[ - Scaled];
	}
	return Scaled;
}

task CBDrive()
{
	while(true)
	{
		if (RB_Button_wasPressed(ButtonState,11)||RB_Button_wasPressed(ButtonState,12))
		{
			FastButton = !FastButton;
		}
		int x = CBMap(joystick.joy1_x1, FastButton); // Strafe left/right
		int y = CBMap(joystick.joy1_y1, FastButton); // move forward/back
		int r = CBMap(joystick.joy1_x2, FastButton)*3/4; // rotate in place

		//motor value & power using x,y, and r to allow the robot to move in any combinations of directions.
		int FL = -y - x - r;
		int FR =  y - x - r;
		int BR =  y + x - r;
		int BL = -y + x - r;

		motor[FrontLeft] = FL;
		motor[FrontRight] = FR;
		motor[BackRight] = BR;
		motor[BackLeft] = BL;

		//displays motor values to the nxt display
		displayBigTextLine(0,"%d",FL);
		displayBigTextLine(2,"%d",FR);
		displayBigTextLine(4,"%d",BR);
		displayBigTextLine(6,"%d",BL);
	}
}
