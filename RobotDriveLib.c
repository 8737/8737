#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-sensormux.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-gyro.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\lego-ultrasound.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-irseeker-v2.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\lego-touch.h"

#define DRIVE_FORWARD 0
#define DRIVE_BACK 1
#define STRAFE_RIGHT 2
#define STRAFE_LEFT 3
#define ROTATE_RIGHT 4
#define ROTATE_LEFT 5
#define CONTROL_LIFT 6
#define SCORE_SERVO 7
#define SCORE_SERVO_OPEN 90
#define SCORE_SERVO_CLOSE 0
#define FOREBAR_LINK 8
#define FOREBAR_LINK_OUT 0
#define FOREBAR_LINK_IN 120
#define TOW_SERVO 9
#define TOW_SERVO_OUT 90
#define TOW_SERVO_IN 0

#define LIFT30CM 1
#define LIFT60CM 2
#define LIFT90CM 3
#define LIFT120CM 4
#define LIFTDOWN 0

#define CENTER_GOAL_P1 1
#define CENTER_GOAL_P2 2
#define CENTER_GOAL_P3 3

#define LEFT -1
#define RIGHT 1
#define MAX_SPEED 75 // speed limit to protect the motors
#define NONE 0
#define IR_THRESHOLD 3
#define US_CG_MAX_THRESHOLD 150
#define US_CG_MIN_THRESHOLD 100
const tMUXSensor HTGYRO = msensor_S3_1;
const tMUXSensor LEGOUS = msensor_S3_3;

tHTIRS2 irSeeker;//msensor_S3_2

void DriveStop()//stop function
{
	motor[FrontRight]=0;
	motor[BackLeft]=0;
	motor[FrontLeft]=0;
	motor[BackRight]=0;
}
void DriveBackForward(int speed)// defines forward function positive is forward negative
{
	motor[FrontRight]=speed;
	motor[FrontLeft]=-speed;
	motor[BackRight]=speed;
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
	motor[FrontRight]=-speed;
	motor[FrontLeft]=-speed;
	motor[BackRight]=speed;
	motor[BackLeft]=speed;
}
void Lift(int speed)
{
	writeDebugStreamLine("LIFTING");
	motor[LiftA]=speed;
	motor[LiftB]=speed;
}
void Lift30cm()// 8000 encoder difference between each height
{
	writeDebugStreamLine("LIFT30CM");
	while(nMotorEncoder[LiftA] > -6800)
	{
		Lift(-75);
	}
	Lift(0);
}
void Lift60cm()
{
	writeDebugStreamLine("LIFT60CM");
	while(nMotorEncoder[LiftA] > -14800)
	{
		Lift(-75);
	}
	Lift(0);
}
void Lift90cm()
{
	writeDebugStreamLine("LIFT90CM");
	while(nMotorEncoder[LiftA] > -22800)
	{
		Lift(-75);
	}
	Lift(0);
}
void Lift120cm()
{
	writeDebugStreamLine("LIFT120CM");
	while(nMotorEncoder[LiftA] > -30800)
	{
		Lift(-75);
	}
	Lift(0);
}
void LiftDown()
{
	writeDebugStreamLine("LIFTDOWN");
	while(nMotorEncoder[LiftA] < 0)
	{
		Lift(75);
	}
	Lift(0);
}
void InchDrive(int Action, int DriveXin)
{
	writeDebugStreamLine("STARTING INCHDRIVE");
	if(DriveXin < 0) return;
	int MotorRunTime = 0;

	int Brake1 = 8;
	float Brake1MS = 88.75;

	int Brake2 = 17;
	float Brake2MS = 68.89;

	int Brake3 = 25;
	float Brake3MS = 66.51;

	float Brake4MS = 66.51;


	//average	8, 17, 25
	//MsPerInch	88.75, 68.89, 66.51

	if(DriveXin >= Brake1)
	{
		writeDebugStreamLine("BREAK1");
		if (DriveXin >= Brake2)
		{
			writeDebugStreamLine("BREAK2");
			if(DriveXin >= Brake3)
			{
				writeDebugStreamLine("BREAK3");
				MotorRunTime = Brake1 * Brake1MS;
				DriveXin -= Brake1;
				MotorRunTime += (Brake2 - Brake1) * Brake2MS;
				DriveXin -= (Brake2-Brake1);
				MotorRunTime += (Brake3 - Brake2) * Brake3MS;
				DriveXin -= (Brake3 - Brake2);
				MotorRunTime += DriveXin * Brake4MS;
			}
			else
			{
				MotorRunTime = Brake1 * Brake1MS;
				DriveXin -= Brake1;
				MotorRunTime += (Brake2 - Brake1) * Brake2MS;
				DriveXin -= (Brake2-Brake1);
				MotorRunTime += DriveXin * Brake3MS;
			}
		}
		else
		{
			MotorRunTime = Brake1 * Brake1MS;
			DriveXin -= Brake1;
			MotorRunTime += DriveXin * Brake2MS;
		}
	}
	else
	{
		MotorRunTime = DriveXin * Brake1MS;
	}
	writeDebugStreamLine("RUNNING MOTORS");
	switch (Action)
	{
	case DRIVE_FORWARD:
		DriveBackForward(25);
		break;
	case DRIVE_BACK:
		DriveBackForward(-25);
		break;
	case STRAFE_RIGHT:
		DriveStrafe(25);
		break;
	case STRAFE_LEFT:
		DriveStrafe(-25);
		break;

	default:
		break;
	}
	displayTextLine(6,"Delay %d ms",MotorRunTime);
	writeDebugStreamLine("Delay %d ms",MotorRunTime);

	sleep(MotorRunTime);
	DriveStop();
	writeDebugStreamLine("FINISHED INCHDRIVE");

}
void gTurn(int Action, int Degrees)
{
	writeDebugStreamLine("STARTING GTURN");
	float heading = 0;// current heading of gyro
	time1[T1] = 0;
	int offset = 13;
	float gRot = HTGYROreadRot(HTGYRO);
	if(Degrees > 45) Degrees -= offset;
	while (abs(heading) < abs(Degrees))// while current heading is < targetHeading
	{
		gRot = HTGYROreadRot(HTGYRO);// get current rate of rotation
		float interval = (float)1000 / (float)time1[T1];
		writeDebugStreamLine ("gRot:%f ",gRot);
		writeDebugStreamLine ("heading:%f ",heading);
		writeDebugStreamLine ("interval:%f ",interval);
		writeDebugStreamLine ("Degrees:%d ",Degrees);
		time1[T1] = 0;// set timer1 to 0

		if(gRot > 0.6 || gRot < -0.6)// threshold
		{
			heading += gRot / interval;// sets heading to heading + gyroSensor.rotation / 100
		}
		displayTextLine(6, "heading:%f",heading);
		switch (Action)
		{
		case ROTATE_RIGHT:
			DriveTurn(25);
			break;
		case ROTATE_LEFT:
			DriveTurn(-25);
			break;

		default:
			break;
		}
		sleep(50);
	}
	DriveStop();
}
int cGPFinder() // center goal position finder
{
	writeDebugStreamLine("STARTING CGP FINDER");
	int cGPosition = 0;
	writeDebugStreamLine("READING US");
	int uSCDist = USreadDist(LEGOUS);
	readSensor(&irSeeker);
	writeDebugStreamLine("ir: %d",irSeeker.acValues[2] );
	writeDebugStreamLine("uSCDist: %d",uSCDist );

	if(irSeeker.acValues[2] <= IR_THRESHOLD && uSCDist < US_CG_MAX_THRESHOLD)
	{
		writeDebugStreamLine("CGP = 1");
		cGPosition = 1;
	}
	else if(irSeeker.acValues[2] > IR_THRESHOLD && uSCDist >= US_CG_MAX_THRESHOLD)
	{
		writeDebugStreamLine("CGP = 2");
		cGPosition = 2;
	}
	else if(irSeeker.acValues[2] > IR_THRESHOLD && uSCDist < US_CG_MAX_THRESHOLD)
	{
		writeDebugStreamLine("CGP = 3");
		cGPosition = 3;
	}
	// if IR = 0 and US is = ~140 cm the cGPosition = 1
	// if IR = S3 and US is > 150 cm the cGPosition = 2
	// if IR = S3 and US is = ~130 cm the cGPosition = 3
	// IR threshold = 2
	// US max range = ~150 cm
	writeDebugStreamLine("FINISHED CGP FINDER");
	return cGPosition;
}
float conversion(float x)
{
  return (x*2.540000);
}
int uSDrive(int rTimeMS, int speed, int uSDistIn)
{
	writeDebugStreamLine("STARTING USDRIVE");
	time1[T2] = 0;
	int uSDistCm = conversion(uSDistIn);
	int uSCDist = USreadDist(LEGOUS);
	writeDebugStreamLine("RUNNING MOTORS");
	while((time1[T2] < rTimeMS) && ( uSCDist >= uSDistCm ))
	{
	DriveStrafe(speed);
	uSCDist = USreadDist(LEGOUS);
	}
	DriveStrafe(0);
	writeDebugStreamLine("FINISHED USDRIVE");
	return uSCDist;
}
 void AutonomousAction(int Action, int LiftAction, int Degrees,int Distance)
{
	writeDebugStreamLine("STARTING AUTONOMOUSACTION");
	writeDebugStreamLine("Action: %d",Action);
	writeDebugStreamLine("LiftAction %d",LiftAction);
	writeDebugStreamLine("Degrees: %d",Degrees);
	writeDebugStreamLine("Distance: %d",Distance);
	switch(Action)
	{
	case DRIVE_FORWARD:
	case DRIVE_BACK:
	case STRAFE_RIGHT:
	case STRAFE_LEFT:
		writeDebugStreamLine("Driving");
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		InchDrive(Action,Distance);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		break;
	case ROTATE_RIGHT:
	case ROTATE_LEFT:
		writeDebugStreamLine("Turning");
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		gTurn(Action,Degrees);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		break;
	case CONTROL_LIFT:
		writeDebugStreamLine("Lifting");
		sleep(1500);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		switch(LiftAction)
		{
		case LIFT30CM:
			Lift30cm();
			break;
		case LIFT60CM:
			Lift60cm();
			break;
		case LIFT90CM:
			Lift90cm();
			break;
		case LIFT120CM:
			Lift120cm();
			break;
		case LIFTDOWN:
			LiftDown();
			break;
		default:
			break;
		}
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
	case SCORE_SERVO:
		writeDebugStreamLine("SCORE SERVO");
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		servo[up] = Degrees;
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
	case FOREBAR_LINK:
		writeDebugStreamLine("FOREBAR LINK");
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		servo[forebarlink] = Degrees;
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
	case TOW_SERVO:
		writeDebugStreamLine("TOW SERVO");
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		servo[Tow] = Degrees;
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
		while(bSoundActive) sleep(1);
		playSound(soundBlip);
	default:
		break;
	}
}
void initializeRobot()
{
	writeDebugStreamLine("INITALISING");
	if (HTSMUXreadPowerStatus(HTSMUX))
	{
		displayTextLine(0, "SMUX Batt: bad");
		while(true)
		{
			playSound(soundLowBuzz);
		}
	}
	else
	{
		displayTextLine(0, "SMUX Batt: good");
	}
	displayTextLine(0,"Initialising...");
	writeDebugStreamLine("SETTING SERVOS TO DOWN POSITION");
	nMotorEncoder[LiftA] = 0;
	servo[up] = SCORE_SERVO_CLOSE;
	servo[forebarlink] = FOREBAR_LINK_IN;
	servo[Tow] = TOW_SERVO_IN;
	sleep(1500);
	writeDebugStreamLine("CALIBRATING AND INITALISING SENSORS");
	initSensor(&irSeeker, msensor_S3_2);
	HTGYROstartCal(HTGYRO);
	writeDebugStreamLine("FINISHED INITALISING");
	return;
}
