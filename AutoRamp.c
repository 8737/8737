#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S4,     LiftDownTouch,  sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     LiftA,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     LiftB,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     FrontRight,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     BackRight,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    up,                   tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    forebarlink,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    Tow,                  tServoStandard)
#include "AutoLib.c"
task main()
{

	servo[forebarlink]=150;
	servo[Tow]=0;
	servo[servo1]=-80;
	startTask(Lift);
	startTask(Forebar);
	wait1Msec(500);
	motor[FrontRight]=65;
	motor[BackRight]=65;
	wait1Msec(200);
	motor[FrontLeft]=-50;
	motor[BackLeft]=-50;
	wait1Msec(3400);
	DriveStop();
	wait1Msec(800);

	motor[FrontRight]=50;
	motor[BackRight]=50;
	wait1Msec(60);
	motor[FrontLeft]=-50;
	motor[BackLeft]=-50;
	wait1Msec(900);
	DriveStop();

	wait1Msec(1000);
	servo[servo1]=90;
	wait1Msec(3100);
	servo[servo1]=-80;

	motor[FrontRight]=-50;
	motor[BackRight]=-50;
	wait1Msec(90);
	motor[FrontLeft]=50;
	motor[BackLeft]=50;
	wait1Msec(900);
	DriveStop();

	motor[FrontRight]=50;
	motor[FrontLeft]=50;
	motor[BackRight]=50;
	motor[BackLeft]=50;
	wait1Msec(700);
	DriveStop();

	servo[Tow]=90;
	motor[FrontRight]=-50;
	motor[FrontLeft]=-50;
	motor[BackRight]=50;
	motor[BackLeft]=50;
	wait1Msec(1000);
	DriveStop();
	servo[Tow]=0;
	wait1Msec(1000);

	motor[FrontRight]=50;
	motor[BackRight]=-50;
	wait1Msec(90);
	motor[FrontLeft]=50;
	motor[BackLeft]=-50;
	wait1Msec(800);

	// TODO: adjust angle to avoid ramp and center goal
	motor[FrontRight]=-50;
	motor[FrontLeft]=-50;
	wait1Msec(430);

	// TODO: adjust time to get to parking zone
	motor[FrontRight]=50;
	motor[FrontLeft]=50;
	wait1Msec(5600);

	// time is 700-(previous turn time) to 90 degree itself
	motor[FrontRight]=-50;
	motor[FrontLeft]=-50;
	wait1Msec(400);

	// TODO: adjust time to ensure the rolling goal is in parking zone
	motor[FrontRight]=50;
	motor[FrontLeft]=50;
	wait1Msec(700);
	DriveStop();
}
