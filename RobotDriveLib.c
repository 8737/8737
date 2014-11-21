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
#define US_CG_THRESHOLD 150
// TASK: figure out min-max open-close degrees
// Create struct to hold sensor data
// #ifdef __HTSMUX_SUPPORT__
const tMUXSensor HTGYRO = msensor_S3_1;
tHTGYRO gyroSensor;
const tMUXSensor LEGOUS = msensor_S3_3;
// const tMUXSensor LEGOTOUCH = msensor_S3_4;
// #else
// tSensors LEGOUS = S2;

// #endif
//tSensors LEGOUS = S2;

tHTIRS2 irSeeker;
//tHTGYRO gyroSensor;

int Action;
int LiftAction;
int Degrees;
int Distance;

void initializeRobot()
{
	#ifdef __HTSMUX_SUPPORT__
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
	#endif
	displayTextLine(0,"Initialising...");
	nMotorEncoder[LiftA] = 0;
	servo[up] = SCORE_SERVO_CLOSE;
	servo[forebarlink] = FOREBAR_LINK_IN;
	servo[Tow] = TOW_SERVO_IN;
	//#ifdef __HTSMUX_SUPPORT__
	initSensor(&irSeeker, msensor_S3_2);
	initSensor(&gyroSensor, msensor_S3_3);
	//#else
	//initSensor(&irSeeker, S1);
	//initSensor(&gyroSensor, S4);
	//#endif
	//initSensor(&irSeeker, S1);
	//initSensor(&gyroSensor, S4);
	//sensorCalibrate(&gyroSensor);
	sleep(1500);
	//sensorCalibrate(&gyroSensor);
	//HTGYROstartCal(gyroSensor);
	// initSensor(&gyroSensor, S1);
	return;
}
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
	motor[LiftA]=speed;
	motor[LiftB]=speed;
}
void Lift30cm()// 8000 encoder difference between each height
{
	while(nMotorEncoder[LiftA] > -6800)
	{
		Lift(-25);
	}
	Lift(0);
}
void Lift60cm()
{
	while(nMotorEncoder[LiftA] > -14800)
	{
		Lift(-25);
	}
	Lift(0);
}
void Lift90cm()
{
	while(nMotorEncoder[LiftA] > -22800)
	{
		Lift(-25);
	}
	Lift(0);
}
void Lift120cm()
{
	while(nMotorEncoder[LiftA] > -30800)
	{
		Lift(-25);
	}
	Lift(0);
}
void LiftDown()
{
	while(nMotorEncoder[LiftA] < 0)
	{
		Lift(25);
	}
	Lift(0);
}
void InchDrive(int Action, int DriveXin)
{
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
		if (DriveXin >= Brake2)
		{
			if(DriveXin >= Brake3)
			{
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
	DriveBackForward(0);

}
void gTurn(int Action, int Degrees)
{
	float heading = 0;// current heading of gyro
	time1[T1] = 0;
	int offset = 13;
	float gRot = HTGYROreadRot(HTGYRO);
	sensorCalibrate(&gyroSensor);
	if(Degrees > 45) Degrees -= offset;
	while (abs(heading) < abs(Degrees))// while current heading is < targetHeading
	{
		gRot = HTGYROreadRot(HTGYRO);// get current rate of rotation
		// readSensor(&gyroSensor);
		float interval = (float)1000 / (float)time1[T1];
		writeDebugStreamLine ("gRot:%f ",gRot);
		// writeDebugStreamLine ("gRot:%f ",gyroSensor.rotation);
		writeDebugStreamLine ("heading:%f ",heading);
		writeDebugStreamLine ("interval:%f ",interval);
		writeDebugStreamLine ("Degrees:%d ",Degrees);
		time1[T1] = 0;// set timer1 to 0

		//if(gRot > 0.6 || gRot < -0.6)// threshold
		if(gyroSensor.rotation > 0.6 || gyroSensor.rotation < -0.6)// threshold
		{
			// heading += gyroSensor.rotation / interval;// sets heading to heading + gyroSensor.rotation / 100
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
	DriveTurn(0);
}
int cGPFinder() // center goal position finder
{
	int cGPosition = 0;
	int uSCDist = USreadDist(LEGOUS);
	readSensor(&irSeeker);
	writeDebugStreamLine("ir: %d",irSeeker.acValues[2] );
	writeDebugStreamLine("uSCDist: %d",uSCDist );

	if(irSeeker.acValues[2] <= IR_THRESHOLD && uSCDist < US_CG_THRESHOLD)
	{
		cGPosition = 1;
	}
	else if(irSeeker.acValues[2] > IR_THRESHOLD && uSCDist >= US_CG_THRESHOLD)
	{
		cGPosition = 2;
	}
	else if(irSeeker.acValues[2] > IR_THRESHOLD && uSCDist < US_CG_THRESHOLD)
	{
		cGPosition = 3;
	}
	// if IR = 0 and US is = ~140 cm the cGPosition = 1
	// if IR = S3 and US is > 150 cm the cGPosition = 2
	// if IR = S3 and US is = ~130 cm the cGPosition = 3
	// IR threshold = 2
	// US max range = 150 cm
	return cGPosition;
}
float conversion(float x)
{
  return (x*2.540000);
}
int uSDrive(int rTimeMS, int speed, int uSDistIn)
{
	time1[T2] = 0;
	int uSDistCm = conversion(uSDistIn);
	int uSCDist = USreadDist(LEGOUS);

	while((time1[T2] < rTimeMS) && ( uSCDist >= uSDistCm ))
	{
	DriveStrafe(speed);
	uSCDist = USreadDist(LEGOUS);
	}
	DriveStrafe(0);
	return uSCDist;
}
 void AutonomousAction(int Action, int LiftAction, int Degrees,int Distance)
{
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
		displayTextLine(5,"Driving");
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
		displayTextLine(5,"Turning");
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
		displayTextLine(5,"Lifting");
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
	writeDebugStreamLine("ScoreOpenClose: %d",ServoValue[up]);
	writeDebugStreamLine("forebarlink: %d",ServoValue[forebarlink]);
	writeDebugStreamLine("Tow: %d",ServoValue[Tow]);
}
//autonomous function
//it takes two variables
// First is Action
// Second is distance/degrees/LiftAction
//task AutomousTask ()
//{
//switch(Action)
//	{
//	// case DRIVE_FORWARD:
//	// case DRIVE_BACK:
//	// case STRAFE_RIGHT:
//	// case STRAFE_LEFT:
//		// displayTextLine(5,"Driving");
//		// playSound(soundBlip);
//		// while(bSoundActive) sleep(1);
//		// playSound(soundBlip);
//		// while(bSoundActive) sleep(1);
//		// InchDrive(Action,Distance);
//		// playSound(soundBlip);
//		// while(bSoundActive) sleep(1);
//		// playSound(soundBlip);
//		// while(bSoundActive) sleep(1);
//		// break;
//	// case ROTATE_RIGHT:
//	// case ROTATE_LEFT:
//		// displayTextLine(5,"Turning");
//		// playSound(soundBlip);
//		// while(bSoundActive) sleep(1);
//		// playSound(soundBlip);
//		// while(bSoundActive) sleep(1);
//		// gTurn(Action,Degrees);
//		// playSound(soundBlip);
//		// while(bSoundActive) sleep(1);
//		// playSound(soundBlip);
//		// while(bSoundActive) sleep(1);
//		// break;
//	case CONTROL_LIFT:
//		displayTextLine(5,"Lifting");
//		sleep(1500);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		switch(LiftAction)
//		{
//		case LIFT30CM:
//			Lift30cm();
//			break;
//		case LIFT60CM:
//			Lift60cm();
//			break;
//		case LIFT90CM:
//			Lift90cm();
//			break;
//		case LIFT120CM:
//			Lift120cm();
//			break;
//		case LIFTDOWN:
//			LiftDown();
//			break;
//		default:
//			break;
//		}
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//	case SCORE_SERVO:
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		servo[up] = Degrees;
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//	case FOREBAR_LINK:
//	while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		servo[forebarlink] = Degrees;
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//	case TOW_SERVO:
//	while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		servo[Tow] = Degrees;
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//		while(bSoundActive) sleep(1);
//		playSound(soundBlip);
//	default:
//		break;
//	}
//	writeDebugStreamLine("ScoreOpenClose: %d",ServoValue[up]);
//	writeDebugStreamLine("forebarlink: %d",ServoValue[forebarlink]);
//	writeDebugStreamLine("Tow: %d",ServoValue[Tow]);
//}
//void AutonomousActionAuto()
//{
	//AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_IN,NONE,NONE);
	//AutonomousAction(CONTROL_LIFT,LIFT120CM,NONE,NONE);

	// Action = CONTROL_LIFT;
	// LiftAction = LIFT120CM;
	// Distance = NONE;
	// Degrees = NONE;
	// startTask(AutomousTask);

	// AutonomousAction(DRIVE_BACK,NONE,NONE,3);
	//InchDrive (DRIVE_BACK,3);

	//AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_OUT,NONE,NONE);
	// AutonomousAction(DRIVE_FORWARD,NONE,NONE,3);
	//InchDrive (DRIVE_FORWARD,3);
	//AutonomousAction(SCORE_SERVO,NONE,SCORE_SERVO_OPEN,NONE);
	//AutonomousAction(SCORE_SERVO,NONE,SCORE_SERVO_CLOSE,NONE);
	//AutonomousAction(DRIVE_BACK,NONE,NONE,3);
	//AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_IN,NONE,NONE);
	//InchDrive (DRIVE_BACK,3);
	//AutonomousAction(CONTROL_LIFT,LIFTDOWN,NONE,NONE);
	//AutonomousAction(STRAFE_RIGHT,NONE,NONE,30);
	//AutonomousAction(ROTATE_LEFT,NONE,90,NONE);
	//AutonomousAction(STRAFE_RIGHT,NONE,NONE,60);
//}q
