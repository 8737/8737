task Lift()
{
	nMotorEncoder[LiftA] = 0;
	int J1_Z1 = 0;
	while (true)
	{

		J1_Z1 = joystick.joy1_y2;
		if (J1_Z1>=10 && nMotorEncoder[LiftA]<=30800)
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
	while(true)
  {
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
		displayBigTextLine(0,"%d",FL);
		displayBigTextLine(2,"%d",FR);
		displayBigTextLine(4,"%d",BR);
		displayBigTextLine(6,"%d",BL);
	}
}
task ScoreOpenClose()
{
	while(true){
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
