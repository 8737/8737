//#include "C:\Program Files\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-gyro.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-sensormux.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-gyro.h"

#define DRIVE_FORWARD 0
#define DRIVE_BACK 1
#define STRAFE_RIGHT 2
#define STRAFE_LEFT 3
#define ROTATE_RIGHT 4
#define ROTATE_LEFT 5
#define CONTROL_LIFT 6
#define SCORE_SERVO 7

#define SCORE_SERVO_MAX_VALUE 90
#define SCORE_SERVO_MIN_VALUE 0
#define FOREBAR_LINK 8
#define FOREBAR_LINK_MAX_VALUE 120
#define FOREBAR_LINK_MIN_VALUE 0
#define TOW_SERVO 9
#define TOW_SERVO_MAX_VALUE 90
#define TOW_SERVO_MIN_VALUE 0

#define MAX_SPEED 75 // speed limit to protect the motors
#define LIFT30CM 1
#define LIFT60CM 2
#define LIFT90CM 3
#define LIFT120CM 4
#define LIFTDOWN 0
// TASK: figure out min-max open-close degrees
// Create struct to hold sensor data
// tHTGYRO gyroSensor;
const tMUXSensor HTGYRO = msensor_S3_1;

void initializeRobot()
{
	displayTextLine(0,"Initialising...");
	nMotorEncoder[LiftA] = 0;
	servo[up] = 0;
	servo[forebarlink] = 0;
	servo[Tow] = 0;
	// initSensor(&gyroSensor, S4);//gyro sensor port is 4
	// sleep(500);
	// sensorCalibrate(&gyroSensor);
	HTGYROstartCal(HTGYRO);
	sleep(1200);
	return;
}

void DriveStop()//stop function
{
	motor[FrontRight]=0;
	motor[FrontLeft]=0;
	motor[BackRight]=0;
	motor[BackLeft]=0;
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
void Lift30cm()
{
	while(nMotorEncoder[LiftA] > -6450)
	{
		Lift(-25);
	}
	Lift(0);
}
void Lift60cm()
{
	while(nMotorEncoder[LiftA] > -14550)
	{
		Lift(-25);
	}
	Lift(0);
}
void Lift90cm()
{
	while(nMotorEncoder[LiftA] > -23050)
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

void ScoreOpenClose(int Degrees)
{
	servo[up] = Degrees;
}
void ForebarLinkOutIn(int Degrees)
{
	servo[forebarlink] = Degrees;
}
void TowOnOff(int Degrees)
{}
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
	DriveTurn(0);
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
	case FOREBAR_LINK:
		servo[forebarlink] = Degrees;
	case TOW_SERVO:
		servo[Tow] = Degrees;
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
