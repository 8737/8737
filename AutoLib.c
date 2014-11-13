#define MAX_SPEED 75
void DriveStop()//stop function
{
	motor[FrontRight]=0;
	motor[FrontLeft]=0;
	motor[BackRight]=0;
	motor[BackLeft]=0;
}

void DriveBackForward(int speed)// defines forward function positive is forward negative
{
	speed=(speed>MAX_SPEED ? MAX_SPEED : (speed<-MAX_SPEED ? -MAX_SPEED : speed));// limits the speed to 75% and -75% to protect motors
	motor[FrontRight]=speed;
	motor[BackRight]=speed;
	wait1Msec(87)
	motor[FrontLeft]=-speed;
	motor[BackLeft]=-speed;
}

void DriveTurn(int speed)// positive is left turn negative is right turn
{
	motor[FrontRight]=-speed;
	motor[FrontLeft]=-speed;
	motor[BackRight]=-speed;
	motor[BackLeft]=-speed;
}

void DriveStrafe(int speed)//moves side to side positive is right negative is left
{
	speed=(speed>MAX_SPEED ? MAX_SPEED : (speed<-MAX_SPEED ? -MAX_SPEED : speed));// limits the speed to 75% and -75% to protect motors
	motor[FrontRight]=-speed;
	motor[FrontLeft]=-speed;
	motor[BackRight]=speed;
	motor[BackLeft]=speed;
}

void DriveAll(int Forward, int Strafe, int Turn)
{
	// limits the speed to 75% and -75% to protect motors
	Forward=(Forward>MAX_SPEED ? MAX_SPEED : (Forward<-MAX_SPEED ? -MAX_SPEED : Forward));
	Strafe=(Strafe>MAX_SPEED ? MAX_SPEED : (Strafe<-MAX_SPEED ? -MAX_SPEED : Strafe));
	Turn=(Turn>MAX_SPEED ? MAX_SPEED : (Turn<-MAX_SPEED ? -MAX_SPEED : Turn));

	int divisor=0;
	if (Forward!=0)
	{
		divisor+=3;
	}
	if (Strafe!=0)
	{
		divisor+=3;
	}
	if (Turn!=0)
	{
		divisor+=1;
	}

	//gives weight(importance) to forward and strafe because of issues
	motor[FrontRight]=((Forward-Strafe)*3+Turn)/divisor;
	motor[FrontLeft]=((Forward+Strafe)*3-Turn)/divisor;
	motor[BackRight]=((Forward+Strafe)*3+Turn)/divisor;
	motor[BackLeft]=((Forward-Strafe)*3-Turn)/divisor;
}
void ScoreOpenCloseFunc()
{
	int delay=1000;
	servo[servo1]=85;
	wait1Msec(delay);
	servo[servo1]=-80;
	wait1Msec(delay);
}

void ScoreCollect()
{
	servo[servo1]=64;
	servo[servo1]=-64;
}

/*void Lift(int x)
{
	motor[LiftA]=75;
	motor[LiftB]=75;
	wait1Msec((x/30)*3100);
	DriveStop();
}*/

void TestDrive()
{
	int delay=2000;
	int speed=25;
	DriveBackForward(speed);
	DriveBackForward(-speed);
	wait1Msec(delay);
	wait1Msec(delay);
	DriveStop();

	wait1Msec(delay);
	DriveTurn(speed);
	wait1Msec(delay);
	DriveTurn(-speed);
	wait1Msec(delay);
	DriveStop();

	wait1Msec(delay);
	DriveStrafe(speed);
	wait1Msec(delay);
	DriveStrafe(speed);
	wait1Msec(delay);
	DriveStop();
}

task Lift()
{
	//wait1Msec(1500)
	motor[LiftA]=-90;
	motor[LiftB]=-90;
	wait1Msec(5000);
	motor[LiftA]=0;
	motor[LiftB]=0;
}

task Forebar()
{
	servo[forebarlink]=-90;
	wait1Msec(9500)
	servo[forebarlink]=150;
}
