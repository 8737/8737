#define DRIVE_FACTOR 1


void driveX(int speed)
{
	motor(FrontLeft) = speed;
	motor(FrontRight) = speed;
	motor(BackLeft) = speed;
	motor(BackRight) = speed;
}


void FourBarLinkDown()
{
	servo(FourBarLink) = 300;
	wait1Msec(10);
}


void FourBarLinkUp()
{
	servo(FourBarLink) = 0;
	wait1Msec(10);
}


void slideMid()
{
	while(nMotorEncoder(LiftA) > -400)
	{
		motor[LiftA]=50;
		motor[LiftB]=50;
	}
	FourBarLinkUp();
	motor(LiftA) = 0;
	motor(LiftB) = 0;
}


void slideDown()
{
		while(SensorValue(LiftDownTouch)==0)
	{
		motor[LiftA]=-50;
		motor[LiftB]=-50;
	}
	servo(FourBarLink) = 300;
	nMotorEncoder[LiftA] = 0;
	motor[LiftA]=0;
	motor[LiftB]=0;
	wait1Msec(10);
}


void slideUp()
{
	while(nMotorEncoder(LiftA)<30500)
	{
		motor(LiftA) = 40;
		motor(LiftB) = 40;
	}
	motor(LiftA) = 0;
	motor(LiftB) = 0;
	servo[FourBarLink]=0;
}


void setup()
{
	servo[FourBarLink]=300;
	servo[KickStand]=180;
	servo[Tow]=0;
	servo[BallRelease]=-80;
	while(SensorValue(LiftDownTouch)==0)
	{
		motor[LiftA]=-50;
		motor[LiftB]=-50;
	}
	nMotorEncoder[LiftA] = 0;
	motor[LiftA]=0;
	motor[LiftB]=0;
	wait1Msec(1000);
}


//1 foot = ? / 2 feet = ? / 3 feet = ?
void drive(int speed, float time)
{
	motor(FrontLeft) = speed;
	motor(FrontRight) = speed-5;
	motor(BackLeft) = speed;
	motor(BackRight) = speed-5;
	wait1Msec(time*1000);

	motor(FrontLeft) = 0;
	motor(FrontRight) = 0;
	motor(BackLeft) = 0;
	motor(BackRight) = 0;
	wait1Msec(1);
}


//
void straife(int speed, float time)
{
	motor(FrontLeft) = speed;
	motor(FrontRight) = -speed;
	motor(BackLeft) = -speed;
	motor(BackRight) = speed;
	wait1Msec(time*1000);

	motor(FrontLeft) = 0;
	motor(FrontRight) = 0;
	motor(BackLeft) = 0;
	motor(BackRight) = 0;
	wait1Msec(1);
}


//
void turn(int speed, float time)
{
	motor(FrontLeft) = 50*speed;
	motor(FrontRight) = -50*speed;
	motor(BackLeft) = 50*speed;
	motor(BackRight) = -50*speed;
	wait1Msec(time*1000);

	motor(FrontLeft) = 0;
	motor(FrontRight) = 0;
	motor(BackLeft) = 0;
	motor(BackRight) = 0;
	wait1Msec(1);
}


//
void arc(int LeftSpeed, int RightSpeed, float time)
{
	motor(FrontLeft) = LeftSpeed;
	motor(FrontRight) = RightSpeed;
	motor(BackLeft) = LeftSpeed;
	motor(BackRight) = RightSpeed;
	wait1Msec(time*1000);

	motor(FrontLeft) = 0;
	motor(FrontRight) = 0;
	motor(BackLeft) = 0;
	motor(BackRight) = 0;
	wait1Msec(1);
}
