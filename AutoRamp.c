#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S4,     LiftDownTouch,  sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     FrontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     BackRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     LiftA,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     LiftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    up,                   tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    forebarlink,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    Tow,                  tServoStandard)
#include "AutoLib.c"
task main()
{
	servo[Tow]=90;
	servo[servo1]=-80;
	wait1Msec(10000)
	StartTask(Lift);
	startTask(Forebar)
	wait1Msec(500)
	motor[FrontRight]=50;
	motor[BackRight]=50;
	wait1Msec(90)
	motor[FrontLeft]=-50;
	motor[BackLeft]=-50;
	wait1Msec(3000);
	DriveStop()
	wait1Msec(1200);

	motor[FrontRight]=50;
	motor[BackRight]=50;
	wait1Msec(60)
	motor[FrontLeft]=-50;
	motor[BackLeft]=-50;
	wait1Msec(700);
	DriveStop();

	wait1Msec(1500);
	servo[servo1]=90;
	wait1Msec(4000);
	servo[servo1]=-80;

	motor[FrontRight]=-25;
	motor[BackRight]=-25;
	wait1Msec(90)
	motor[FrontLeft]=25;
	motor[BackLeft]=25;
	wait1Msec(800);
	DriveStop();

	motor[FrontRight]=50;
	motor[FrontLeft]=50;
	motor[BackRight]=50;
	motor[BackLeft]=50;
	wait1Msec(750);
	DriveStop();

	motor[FrontRight]=-50;
	motor[FrontLeft]=-50;
	motor[BackRight]=50;
	motor[BackLeft]=50;
	wait1Msec(1200);
	DriveStop();
	servo[Tow]=0;
	wait1Msec(1000)

	motor[FrontRight]=50;
	motor[BackRight]=-50;
	wait1Msec(90)
	motor[FrontLeft]=50;
	motor[BackLeft]=-50;
	wait1Msec(3000);
	DriveStop()
	wait1Msec(1200);
}
