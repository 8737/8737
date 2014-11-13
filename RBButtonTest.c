// Library to assist checking of a Button Press, Release
// Use by periodically calling RB_Button_addState with joystick.joy1_Buttons
#include "RBButtonLib.h"
#include "JoystickDriver.c"


RB_Button_State s;

task main()
{
   disableDiagnosticsDisplay();
   eraseDisplay();
   RB_Button_Init(s);
   int cnt=0;
   while (true) {
     getJoystickSettings(joystick);
     RB_Button_addState(s, joystick.joy1_Buttons);
     // Low Level Debug
     //nxtScrollText("2=%d 1=%d p=%d r=%d", s.old2, s.old1, s.pressed, s.released);
     //wait1Msec(2000);
     if (++cnt > 100) {
       cnt = 0;
       // High Level Debug
       nxtScrollText("h:%d%d%d p:%d%d%d r:%d%d%d",
         RB_Button_isHeld(s,1), RB_Button_isHeld(s,2), RB_Button_isHeld(s,3),
         RB_Button_wasPressed(s,1), RB_Button_wasPressed(s,2), RB_Button_wasPressed(s,3),
         RB_Button_wasReleased(s,1), RB_Button_wasReleased(s,2), RB_Button_wasReleased(s,3)
         );
     }
     wait1Msec(20);  // Don't spin too hard
  }
}
