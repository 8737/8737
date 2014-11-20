const int JoystickMin = 8;
const int JoystickMax = 125;
const int DriveMotorMin = 10;
const int DriveMotorMax = 90;



int CBMap(int OrigAxis)
{
	int Axis = RB_abs(OrigAxis);
	float Convertion = ((float) (DriveMotorMax - DriveMotorMin)) / (JoystickMax - JoystickMin);
	int MappedAxis = Convertion * (Axis-JoystickMin) + DriveMotorMin / 2;
	MappedAxis = RB_constrain(MappedAxis, DriveMotorMin, DriveMotorMax);
	if (Axis<JoystickMin)
	{
		MappedAxis = 0;
	}
	return (MappedAxis * RB_sgn(OrigAxis));
}

task CBDrive()
{
	while(true)
	{
		int x = CBMap(joystick.joy1_x1); // Strafe left/right
		int y = CBMap(joystick.joy1_y1); // move forward/back
		int r = CBMap(joystick.joy1_x2)*3/4; // rotate in place

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
