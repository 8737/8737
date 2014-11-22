void DriveStop()//stop function
{
	motor[FrontRight]=0;
	motor[FrontLeft]=0;
	motor[BackRight]=0;
	motor[BackLeft]=0;
}

task Lift()
{
	//wait1Msec(1500)
	motor[LiftA]=-90;
	motor[LiftB]=-90;
	wait1Msec(4300);
	motor[LiftA]=0;
	motor[LiftB]=0;
}

task Forebar()
{
	servo[forebarlink]=-90;
	wait1Msec(12000);
	servo[forebarlink]=150;
}
