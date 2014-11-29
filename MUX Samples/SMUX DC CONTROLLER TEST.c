#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom9V)
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
#pragma DebuggerWindows("joystickGame")
#pragma DebuggerWindows("debugStream")
/**
* hitechnic-irseeker-v2.h provides an API for the HiTechnic IR Seeker V2.  This program
* demonstrates how to use that API.
*
* Changelog:
* - 0.1: Initial release
*
* Credits:
* - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
*
* License: You may use this code as you wish, provided you give credit where it's due.
*
* THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

* Xander Soldaat (xander_at_botbench.com)
* Dick Swan
* Gus Jansson
* 04 October 2012
* version 0.1
*/
#include "JoystickDriver.c"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-sensormux.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-gyro.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\lego-ultrasound.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\hitechnic-irseeker-v2.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rd Party Driver Library\include\lego-touch.h"

const tMUXSensor HTGYRO = msensor_S3_1;
const tMUXSensor LEGOUS = msensor_S3_3;
// const tMUXSensor LEGOTOUCH = msensor_S3_4;

tHTIRS2 irSeeker;

// main task
void Lift(int speed)
{
	motor[LiftA]=speed;
	motor[LiftB]=speed;
}

task main ()
{
	displayCenteredTextLine(0, "SMUS & TETRIX");
	displayCenteredBigTextLine(1, "Test");

	Lift(20);
	sleep(500);
	Lift(0);
	if (HTSMUXreadPowerStatus(HTSMUX))
	{
		displayTextLine(2, "SMUX Batt: bad");
		while(true)
		{
			playSound(soundLowBuzz);
		}
	}
	else
	{
		displayTextLine(2, "SMUX Batt: good");
	}
	HTGYROstartCal(HTGYRO);
	Lift(20);
	sleep(500);
	Lift(0);
	writeDebugStreamLine("Zeroing servos");
	//code from "initializeRobot"
	nMotorEncoder[LiftA] = 0;
	servo[up] = 0;
	servo[forebarlink] = 0;
	servo[Tow] = 0;
	Lift(20);
	sleep(500);
	Lift(0);
	writeDebugStreamLine("Initialising Sensors");
	// this where the motor controllers typically fail
	initSensor(&irSeeker, msensor_S3_2);
	Lift(20);
	sleep(500);
	Lift(0);
	while(true)
	{
		readSensor(&irSeeker);
		displayTextLine(3, "D:%4d:%4d:3%d", irSeeker.dcDirection, irSeeker.acDirection, irSeeker.enhDirection);
		displayTextLine(4, "0:%4d:%4d:%3d", irSeeker.dcValues[2], irSeeker.acValues[2], irSeeker.enhStrength);
		displayTextLine(5, "Gyro:%4d", HTGYROreadRot(HTGYRO));
		displayTextLine(6, "Dist:%3d cm", USreadDist(LEGOUS));
		sleep(500);
		Lift(20);
		sleep(1500);
		Lift(0);
	}
}