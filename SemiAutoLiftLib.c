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
long FloorHeight [5] = {0, 6159, 14562, 22466, 29783};
int LiftEncGap = 55; // +/- 2mm accuracy
#endif


int DesiredFloor = -1;
const int MaxAutoLiftSpeed=85;
const int MinAutoLiftSpeed=15;
const int ManualLiftSpeed=50;


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
		if (SensorValue[LiftZeroSensor])
		{
			ClearLiftEnc();
		}

		long Enc = GetLiftEnc();
//		writeDebugStreamLine("Enc: %d", Enc);
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
			  long ADelta = (delta>=0 ? delta : -delta);
				//				writeDebugStreamLine("Enc: %d Delta: %d", Enc, delta);
				if(ADelta<=LiftEncGap)
				{
					SetLiftSpeed(0);
					//					DesiredFloor = -1; //have arrived within MinEnc of target
					//writeDebugStreamLine("Stopped");
				}
				else if(ADelta <= (LiftEncGap * 20))
				{
				SetLiftSpeed(delta>0 ? MinAutoLiftSpeed : -MinAutoLiftSpeed);
				}

				else
				{
				SetLiftSpeed(delta>0 ? MaxAutoLiftSpeed : -MaxAutoLiftSpeed);
				}
			}
		}
		if (Enc>TopLiftLimit && GetLiftSpeed()>0) //if slides too high and going up
		{
			SetLiftSpeed(0);
			DesiredFloor = -1;//stops auto program
		}
		if (SensorValue[LiftZeroSensor] && GetLiftSpeed()<0)//if bottom button is pressed and lifts are going down
		{
			SetLiftSpeed(0);
		}

		wait1Msec(10);
	}
}
