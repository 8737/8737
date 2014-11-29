#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     Touch,          sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     LiftA,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LiftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     FrontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     BackRight,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    up,                   tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    forebarlink,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    Tow,                  tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "RobotDriveLib.c"


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will automatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	initializeRobot();

//motor[FrontLeft] = 50;
//	sleep(2000);
//	motor[FrontLeft] = 0;
	//waitForStart(); // Wait for the beginning of autonomous phase.
	AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_OUT,NONE,NONE);
	sleep(200);
	int cGPosition = cGPFinder();
	writeDebugStreamLine("cGPosition: %d",cGPosition);
	switch(cGPosition)
	{
		case CENTER_GOAL_P1: // goal position 1
			displayBigTextLine(1,"CENTER_GOAL_P1");

			AutonomousAction(STRAFE_LEFT,NONE,NONE,25);// AutonomousAction(Action,LiftAction,Degrees,Distance)
			AutonomousAction(ROTATE_RIGHT,NONE,90,NONE);
			uSDrive(6000,50,16);
			// once at centrer goal structure:
			InchDrive (DRIVE_BACK,3);
			AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_IN,NONE,NONE);
			AutonomousAction(CONTROL_LIFT,LIFT120CM,NONE,NONE);
			InchDrive (DRIVE_FORWARD,3);
			AutonomousAction(SCORE_SERVO,NONE,SCORE_SERVO_OPEN,NONE);
			AutonomousAction(SCORE_SERVO,NONE,SCORE_SERVO_CLOSE,NONE);
			InchDrive (DRIVE_BACK,3);
			AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_IN,NONE,NONE);
			AutonomousAction(CONTROL_LIFT,LIFTDOWN,NONE,NONE);
			AutonomousAction(STRAFE_RIGHT,NONE,NONE,9);
			AutonomousAction(ROTATE_LEFT,NONE,90,NONE);
			 AutonomousAction(STRAFE_RIGHT,NONE,NONE,60);
			break;
		case CENTER_GOAL_P2: //goal position 2
			//displayBigTextLine(1,"CENTER_GOAL_P2");
			 //AutonomousAction(ROTATE_RIGHT,NONE, 45, NONE);
			 //AutonomousAction(DRIVE_FORWARD,NONE,NONE,24);
			// uSDrive(6000,50,36);
			// AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_IN,NONE,NONE);
			// AutonomousAction(CONTROL_LIFT,LIFT120CM,NONE,NONE);
			// AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_OUT,NONE,NONE);
			// AutonomousAction(SCORE_SERVO,NONE,SCORE_SERVO_OPEN,NONE);
			// AutonomousAction(SCORE_SERVO,NONE,SCORE_SERVO_CLOSE,NONE);
			// AutonomousAction(CONTROL_LIFT,LIFTDOWN,NONE,NONE);
			// AutonomousAction(STRAFE_LEFT,NONE,NONE,36);
			// AutonomousAction(DRIVE_FORWARD,NONE,NONE,48);
			break;
		case CENTER_GOAL_P3:// goal position 3
			//displayBigTextLine(1,"CENTER_GOAL_P3");
			// AutonomousAction(STRAFE_RIGHT,NONE,NONE,24);
			// AutonomousAction(DRIVE_FORWARD,NONE,NONE,24);
			// uSDrive(6000,50,36);
			// AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_IN,NONE,NONE);
			// AutonomousAction(CONTROL_LIFT,LIFT120CM,NONE,NONE);
			// AutonomousAction(FOREBAR_LINK,FOREBAR_LINK_OUT,NONE,NONE);
			// AutonomousAction(SCORE_SERVO,NONE,SCORE_SERVO_OPEN,NONE);
			// AutonomousAction(SCORE_SERVO,NONE,SCORE_SERVO_CLOSE,NONE);
			// AutonomousAction(CONTROL_LIFT,LIFTDOWN,NONE,NONE);
			// AutonomousAction(STRAFE_LEFT,NONE,NONE,36);
			// AutonomousAction(DRIVE_FORWARD,NONE,NONE,60);
			break;
	}
	// void AutonomousAction(int Action, int LiftAction, int Degrees,int Distance)
	// #define DRIVE_FORWARD 0
	// #define DRIVE_BACK 1
	// #define STRAFE_RIGHT 2
	// #define STRAFE_LEFT 3
	// #define ROTATE_RIGHT 4
	// #define ROTATE_LEFT 5
	// #define CONTROL_LIFT 6
	// #define SCORE_SERVO 7
	// #define FOREBAR_LINK 8
	// #define TOW_SERVO 9

	// #define MAX_SPEED 75 // speed limit to protect the motors
	// #define LIFT30CM 1
	// #define LIFT60CM 2
	// #define LIFT90CM 3
	// #define LIFT120CM 4
	// #define LIFTDOWN 0
	while (true)
	{}
}