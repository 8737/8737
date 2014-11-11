#define MAX_SPEED 75 // speed limit to protect the motors

/*top drive motors
void DriveStop();
void DriveBackForward(int speed); // defines forward function positive is forward negative
positive is left turn negative is right turn
void DriveTurn(int speed);
moves side to side positive is right negative is left speed
void DriveStrafe(int speed);*/

/*
DriveStrafe - goes sideways while facing forward
reverse front left and back left
going forward
front right +
front left +
back right +
back left +

rotate
front right +
front left -
back right +
back left -
 negative numbers turn left positive turn right
to combine add inputs for each motor and scale down in half

*/

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
	motor[FrontLeft]=-speed;
	motor[BackLeft]=-speed;
	motor[BackRight]=speed;
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

int map(int input, int in_min, int in_max, int out_min, int out_max)
{
  return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

task Lift()
{
	nMotorEncoder[LiftA] = 0;
	getJoystickSettings(joystick);
	int J1_Z1 = 0;
	while (true)
	{

		J1_Z1 = joystick.joy1_y2;
		if (J1_Z1>=10 && nMotorEncoder[LiftA]<=32000)
		{
			motor[LiftA]=-J1_Z1;
			motor[LiftB]=-J1_Z1;
			wait1Msec(100);
		}
		else if (J1_Z1 <= -10 && SensorValue(S4) == 0)//&&nMotorEncoder[LiftA]>0)
		{
			motor[LiftA]=-J1_Z1;
			motor[LiftB]=-J1_Z1;
		}
			/*if(SensorValue(Light<=20)
			{
				motor[LiftA]=J1_Z1;
				motor[LiftB]=J1_Z1;
				wait1Msec(100);
			}
			else
			{
				motor[LiftA]=0;
				motor[LiftB]=0;
				wait1Msec(100);
			}*/
		else if(SensorValue(S4) == 1)
		{
			nMotorEncoder[LiftA] = 0;
			motor[LiftA]=0;
			motor[LiftB]=0;
		}
		else
		{
			motor[LiftA]=0;
			motor[LiftB]=0;
		}
	}
}

task Drive()
{
	int J1_X2 = 0;
	int J1_Y1 = 0;
	int J1_X1 = 0;
	int threshold = 10;
	while(true)                            // Infinite loop:
  {
  	getJoystickSettings(joystick);
		int x = joystick.joy1_x1; // Strafe left/right
		int y = joystick.joy1_y1; // move forward/back
		int r = joystick.joy1_x2; // rotate in place

		// this changes the motor speed from linear to logarithmic
		x = x * abs(x) / 160;
		y = y * abs(y) / 160;
		r = r * abs(r) / 160;

		//motor value & power using x,y, and r to allow the robot to move in any combinations of directions.
		int FL = (-1 * y) + (-1 * x) + (-1 * r);
		int FR = ( 1 * y) + (-1 * x) + (-1 * r);
		int BR = ( 1 * y) + ( 1 * x) + (-1 * r);
		int BL = (-1 * y) + ( 1 * x) + (-1 * r);

		motor[FrontLeft] = FL;
		motor[FrontRight] = FR;
		motor[BackRight] = BR;
		motor[BackLeft] = BL;

		//displays motor values to the nxt display
		nxtDisplayBigTextLine(0,"%d",FL);
		nxtDisplayBigTextLine(2,"%d",FR);
		nxtDisplayBigTextLine(4,"%d",BR);
		nxtDisplayBigTextLine(6,"%d",BL);
	}
}
task ScoreOpenClose()
{
	while(true){
		getJoystickSettings(joystick);
		if (joy1Btn(1)==1)
		{
			servo[servo1]=90;
		}
		else
		{
				servo[servo1]=-80;
		}
	}
}

task Forebar()
{
	while(true){
		getJoystickSettings(joystick);
		if (joy1Btn(2)==1)
		{
			servo[forebarlink]=-90;
		}
		else
		{
				servo[forebarlink]=150;
		}
	}
}
//int Continue =0
task TowMech()
{
	servo[Tow]=90;
	while(true)
	{
		if (joy1Btn(3)==1)
		{
			servo[Tow]=0;
		}
		else if (joy1Btn(4)==1)
		{
			servo[Tow]=90;
		}
	}
	/*while(true){
		if (joy1Btn(3)==1)
		{
			servo[Tow]=0;
			wait1Msec(500);
			Continue=0;
			while(Continue=0)
			{
				if(joy1Btn(3)==1)
				{
					servo[Tow]=90;
					Continue=1;
				}
			}
		}
	}*/
}
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Task  - compares the requested speed of each motor to the current speed    */
/*          and increments or decrements to reduce the difference as nexessary */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

/*task MotorSlewRateTask()
{
    int motorIndex;
    int motorTmp;

    // Initialize stuff
    for(motorIndex=0;motorIndex<MOTOR_NUM;motorIndex++)
        {
        motorReq[motorIndex] = 0;
        motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
        }

    // run task until stopped
    while( true )
        {
        // run loop for every motor
        for( motorIndex=0; motorIndex<MOTOR_NUM; motorIndex++)
            {
            // So we don't keep accessing the internal storage
            motorTmp = motor[ motorIndex ];

            // Do we need to change the motor value ?
            if( motorTmp != motorReq[motorIndex] )
                {
                // increasing motor value
                if( motorReq[motorIndex] > motorTmp )
                    {
                    motorTmp += motorSlew[motorIndex];
                    // limit
                    if( motorTmp > motorReq[motorIndex] )
                        motorTmp = motorReq[motorIndex];
                    }

                // decreasing motor value
                if( motorReq[motorIndex] < motorTmp )
                    {
                    motorTmp -= motorSlew[motorIndex];
                    // limit
                    if( motorTmp < motorReq[motorIndex] )
                        motorTmp = motorReq[motorIndex];
                    }

                // finally set motor
                motor[motorIndex] = motorTmp;
                }
            }

        // Wait approx the speed of motor update over the spi bus
        wait1Msec( MOTOR_TASK_DELAY );
        }
}*/
