long TopLiftLimit =  15151;
long FloorHeight [5] = {0, 2100, 6400, 10300, 14350};
int LiftEncGap = 55; // +/- 2mm accuracy
const int LiftEncPerCM = 245;

bool KickStandDown = false;
bool ForceScoreOpen=false;
bool ForceForebarHigh=false;
bool FourBarDeployed=false;
int DesiredFloor = -1;
const int MaxAutoLiftSpeed=85;
const int MinAutoLiftSpeed=15;
const int ManualLiftSpeed=50;
const int AutoDeployEncTop=1650;
const int AutoDeployEncBottom=1550;

int CaptureState = -1;

void SetLiftSpeed(int MotorSpeed)
{
	motor[LiftA] = -MotorSpeed;
	motor[LiftB] = -MotorSpeed;
}

int GetLiftSpeed()
{
	return -motor[LiftA];
}

long GetLiftEnc()
{
	return -nMotorEncoder[LiftA];
}

void ClearLiftEnc()
{
	nMotorEncoder[LiftA] = 0;
}

void SetFourBar(bool Deploy)
{
	if (! ForceForebarHigh)
	{
		if (Deploy)
		{
			servo[FourBarLink]=0;
		}
		else
		{
			servo[FourBarLink]=255;
		}
	}
	else
	{
		if (Deploy)
		{
			servo[FourBarLink]=0;
		}
		else
		{
			servo[FourBarLink]=300;
		}
	}
}

void SetScoreOpen(bool Drop)
{
	if (Drop)
	{
		servo[BallRelease]=90;
	}
	else
	{
		servo[BallRelease]=-80;
	}
}

task TowMechTeleOP()
{
	while(true)
	{
		if(RB_Button_wasPressed(ButtonState, 4))// switch towing upon press of Y
		{
			servo[Tow]=90;
		}
		if(RB_Button_wasPressed(ButtonState, 1))// switch towing down press of 1
		{
			servo[Tow]=0;
		}
		wait1Msec(10);
	}
}

task KickStandTeleOP()
{
	while(true)
	{
		if(RB_Button_wasPressed(ButtonState, 9))// toggle on button "BACK"
		{
			KickStandDown = !KickStandDown;
		}
		if (KickStandDown)
		{
			servo[KickStand]=70;
		}
		else
		{
			servo[KickStand]=180;
		}
		wait1Msec(10);
	}
}

void SemiAutoBallCapture(long Enc)
{
	switch (CaptureState)
	{
	case 1: //time to go down to 1 inch to grab ball
		SetLiftSpeed(-MaxAutoLiftSpeed);
		if (Enc < 3*LiftEncPerCM) // ~1"
		{
			clearTimer(T2);
			CaptureState++;
		}
		else break;

	case 2: // at one inch, time to allow passage to ball
		SetLiftSpeed(0);
		SetScoreOpen(true);
		if (time1[T2] > 500) // half second
		{
			CaptureState++;
		}
		else break;

	case 3: //drop to ground
		SetLiftSpeed(-MaxAutoLiftSpeed/2);
		if (Enc <= 0)
		{
			clearTimer(T2);
			CaptureState++;
		}
		else break;

	case 4: // wait, lock
		SetScoreOpen(false);
		if (time1[T2] > 250) // 1/4 second
		{
			CaptureState++;
		}
		else break;

	case 5 ://go up
		SetLiftSpeed(MaxAutoLiftSpeed);
		if (Enc > 9*LiftEncPerCM) // ~3.5in
		{
			SetLiftSpeed(0);
			CaptureState = -1; // done
		}
		break;

	default: // nothing
	} // case
}

int GetFloorBellow(long Encoder, int Slop)
{
	int CalculatedFloor = 0;
	while (CalculatedFloor < 4 && Encoder >= (FloorHeight[CalculatedFloor + 1] - Slop))
	{
		CalculatedFloor++;
	}
	return CalculatedFloor;
}

task LiftTeleOP()
{
	while(true)
	{
		if (SensorValue[LiftDownTouch])
		{
			ClearLiftEnc();
		}

		long Enc = GetLiftEnc();
		//writeDebugStreamLine("Enc: %d", Enc);
		if(RB_Button_wasPressed(ButtonState, 6))// next floor upon press of RB
		{
			CaptureState = -1;//shut off auto ball capture
			if(DesiredFloor<0)//not moving
			{
				// Chaged a hard coded 2 (2 degrees on old encoder) to 4 MinGaps so ~1/4"
				DesiredFloor = GetFloorBellow(Enc, LiftEncGap*8) +1;
			}
			else
			{
				DesiredFloor++;
			}

			if(DesiredFloor>4)//limit top floor
			{
				DesiredFloor=4;
			}
		}

		if(RB_Button_wasPressed(ButtonState, 8))//return to ground upon right trigger press
		{
			CaptureState = -1;//shut off auto ball capture
			DesiredFloor = 0;
		}

		if(RB_Button_isHeld(ButtonState, 5))//adjust up upon press of LB
		{
			CaptureState = -1;//shut off auto ball capture
			DesiredFloor = -1;// dissable any auto-floor movement
			SetLiftSpeed(ManualLiftSpeed);
		}
		else if(RB_Button_isHeld(ButtonState, 7))//adjust down upon left trigger press
		{
			CaptureState = -1;//shut off auto ball capture
			DesiredFloor = -1;// dissable any auto-floor movement
			SetLiftSpeed(-ManualLiftSpeed);
		}
		else
		{
			if(DesiredFloor<0)//no floor, stop
			{
				if (CaptureState < 0) // no auto capture
				{
					SetLiftSpeed(0);
				}
			}
			else // go to desired floor
			{
				long delta = FloorHeight[DesiredFloor] - Enc;
				long ADelta = RB_abs(delta);
				if(ADelta<=LiftEncGap)
				{
					SetLiftSpeed(0);
				}
				else if(ADelta <= (LiftEncGap * 20))
				{
					SetLiftSpeed(RB_sgn(delta) * MinAutoLiftSpeed);
				}
				else
				{
					SetLiftSpeed(RB_sgn(delta) * MaxAutoLiftSpeed);
				}
			}
		}
		if (Enc>TopLiftLimit && GetLiftSpeed()>0) //if slides too high and going up
		{
			SetLiftSpeed(0);
			CaptureState = -1;//shut off auto ball capture
			DesiredFloor = -1;//stops auto program
		}
		if (SensorValue[LiftDownTouch] && GetLiftSpeed()<0)//if bottom button is pressed and lifts are going down
		{
			SetLiftSpeed(0);
		}
		//four bar linkage AutoDeploy and manual
		if (Enc>AutoDeployEncTop)
		{
			FourBarDeployed = true;
		}
		else if (Enc<AutoDeployEncBottom)
		{
			FourBarDeployed = false;
		}

		if (RB_Button_isHeld(ButtonState, 3))// toggle four bar state using button B
		{
			SetFourBar(!FourBarDeployed);
		}
		else
		{
			SetFourBar(FourBarDeployed);
		}

		if (RB_Button_wasPressed(ButtonState, 10))//button START
		{
			DesiredFloor = -1;//stops auto floor program
			if (Enc > 8*LiftEncPerCM) // ~3"
			{
				CaptureState = 1; // Capture
			}
			else
			{
				CaptureState = 5; // Reset to 3.5"
			}
		}

		// ball release code
		if (CaptureState>0) // in auto capture
		{
			SemiAutoBallCapture(Enc);
		}
		else
		{
			SetScoreOpen(RB_Button_isHeld(ButtonState, 2) || ForceScoreOpen);//button A
		}

		wait1Msec(10);
	}//while loop end
}
