#ifndef INCLUDE_RBButtonLib
#define INCLUDE_RBButtonLib
// Library to assist checking of a Button Press, Release
// Use by periodically calling RB_Button_addState with joystick.joy1_Buttons
//
// Written by Ron Barber   ron_123@yahoo.com   11/11/2014

#pragma systemFile            // eliminates warning for "unreferenced" functions in RobotC

/**
 * Structure to hold a Button State, declare one for a Button Suite (like joy1_Buttons)
 * This holds two past button states to reliably detect transitions of state like press/release.
 */
struct RB_Button_State {
  short old1, old2; // Keep last and previous states
  short pressed, released; // Capture a Press or Release until read
};

/**
 * Reset the Button State, must be called at start of task or Init function.
 */
void RB_Button_Init(RB_Button_State& s)
{
  s.old1 = s.old2 = s.pressed = s.released = 0;
}

/**
 * Adds a Button State to the history and updates transitions.
 * Example: RB_Button_addState(s, joystick.joy1_Buttons);
 * Inputs: RB_Button_State
 */
void RB_Button_addState(RB_Button_State& s, short newState)
{
  // Check if a button is just now transitioning to a 1 from a 0,0.
  short pressedNow = (newState & ~s.old1 & ~s.old2);
  // Check if a button is now a 0 and previosly a 0 but oldest was a 1.
  short releasedNow = (~newState & ~s.old1 & s.old2);
  hogCPU();// Deal with possile concurreny issues
  // Check if a button is just now transitioning to a 1 from a 0,0.
  s.pressed  |= pressedNow;
  // Check if a button is now a 0 and previosly a 0 but oldest was a 1.
  s.released |= releasedNow;
  // Push state into history
  s.old2 = s.old1;
  s.old1 = newState;
  releaseCPU();
}

/**
 * Check Button State has been pressed since last testing of pressed.
 * This is true when first pressed down and does not trigger again unless
 * released and pressed again.
 * Inputs: RB_Button_State & Button # to test 1 to 16
 * Result true if pressed else false
 */
bool RB_Button_isHeld(const RB_Button_State& s, byte button)
{
  const short mask = (1 << (button-1));
  return (0 != (s.old1 & mask));
}

/**
 * Check Button State has been pressed since last testing of pressed.
 * This is true when first pressed down and does not trigger again unless
 * released and pressed again.
 * Inputs: RB_Button_State & Button # to test 1 to 16
 * Result true if pressed else false
 */
bool RB_Button_wasPressed(RB_Button_State& s, byte button)
{
  const short mask = (1 << (button-1));
  const short temp = s.pressed;
  hogCPU(); // Deal with possile concurreny issues
  s.pressed &= ~mask; // Clear Pressed flag, if set
  releaseCPU();
  return (0 != (temp & mask));
}

/**
 * Check Button State has been released since last testing of released.
 * This is true when finally released and does not trigger again unless
 * pressed and released again.
 * Inputs: RB_Button_State & Button # to test 1 to 16
 * Result true if released else false
 */
bool RB_Button_wasReleased(RB_Button_State& s, byte button)
{
  const short mask = (1 << (button-1));
  const short temp = s.released;
  hogCPU(); // Deal with possile concurreny issues
  s.released &= ~mask; // Clear Pressed flag, if set
  releaseCPU();
  return (0 != (temp & mask));
}
#endif
