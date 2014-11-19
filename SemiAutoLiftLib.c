#ifdef TEST_MOTOR
int _LiftA=motorA;
int _LiftB=motorA;
long TopLiftLimit =  390;
long FloorHeight [5] = {0, 90, 180, 270, 360};
int LiftEncGap = 2;
#else
#define _LiftA LiftA
#define _LiftB LiftB
long TopLiftLimit =  29965;
long FloorHeight [5] = {0, 6085, 14425, 22360, 29780};
int LiftEncGap = 55; // +/- 2mm accuracy
#endif

bool FourBarDeployed=false;
int DesiredFloor = -1;
const int MaxAutoLiftSpeed=85;
const int MinAutoLiftSpeed=15;
const int ManualLiftSpeed=50;
const int AutoDeployEncTop=3000;
const int AutoDeployEncBottom=2500;


void SetLiftSpeed(int MotorSpeed)
{
	motor[_LiftA] = -MotorSpeed;
	motor[_LiftB] = -MotorSpeed;
}

int GetLiftSpeed()
{
	return -motor[_LiftA];
}

long GetLiftEnc()
{
	return -nMotorEncoder[_LiftA];
}

void ClearLiftEnc()
{
	nMotorEncoder[_LiftA] = 0;
}

void SetFourBar(bool Deploy)
{
		if (Deploy)
		{
			servo[FourBarLink]=-90;
		}
		else
		{
				servo[FourBarLink]=185;
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
				servo[servo1]=-80;
		}
}

task TowMechTeleOP()
{
	bool TowUp = false;
	while(true)
	{
		if(RB_Button_wasPressed(ButtonState, 4))// toggle towing upon press of Y
		{
			TowUp = !TowUp;
		}

		if (TowUp)
		{
			servo[Tow]=90;
		}
		else
		{
			servo[Tow]=0;
		}
	}
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

		if(RB_Button_wasPressed(ButtonState, 13))//return to ground upon right trigger press
		{
			DesiredFloor = 0;
		}

		if(RB_Button_isHeld(ButtonState, 5))//adjust up upon press of LB
		{
			DesiredFloor = -1;// dissable any auto-floor movement
			SetLiftSpeed(ManualLiftSpeed);
		}
		else if(RB_Button_isHeld(ButtonState, 14))//adjust down upon left trigger press
		{
			DesiredFloor = -1;// dissable any auto-floor movement
			SetLiftSpeed(-ManualLiftSpeed);
		}
		else
		{
			if(DesiredFloor<0)//no floor, stop
			{
				SetLiftSpeed(0);
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

		if (RB_Button_isHeld(ButtonState, 2))// toggle four bar state using button B
		{
			SetFourBar(!FourBarDeployed);
		}
		else
		{
			SetFourBar(FourBarDeployed);
		}
		// ball release code
		SetScoreOpen(RB_Button_isHeld(ButtonState, 1));//button A

		wait1Msec(10);
	}
}
