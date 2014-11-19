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

/**
 * Return absolute value of an integer value.
 * Result is input if input >= 0 else -input
 */
int RB_abs(int in)
{
	return (in < 0 ? -in : in);
}

/**
 * Return sign of input value (-1,0,1).
 * Result is -1 if input is negative, 1 input positive else 0
 */
int RB_sgn(int in)
{
	return (in < 0 ? -1 : (in > 0 ? 1 : 0));
}

/**
 * Constrain input values to be in range of in_min to in_max.
 * Result is will be unformly between out_min and out_max for inputs between in_min and in_max.
 */
int RB_constrain(int in, int in_min, int in_max)
{
	return (in < in_min ? in_min : (in > in_max ? in_max : in));
}

/**
 * Map input values from in_min to in_max into out_min to out_max uniformly
 * Does not constrain output to be within output range, but guarantees
 * range for specified input range.
 * Result is will be unformly between out_min and out_max for inputs between in_min and in_max.
 */
int RB_map(int in, int in_min, int in_max, int out_min,int out_max)
{
	long m = in - in_min; // Use long to avoid overflow on multiply
  // If ouput range larger than input then need to add 1 to ranges to avoid only 1 value mapping to out_max
	if (out_max-out_min < in_max-in_min)
	{
		m = m * (out_max-out_min+1) / (in_max-in_min+1);
	}
	else
	{
		m = m * (out_max-out_min) / (in_max-in_min);
	}
	return (int)(m + out_min);
}
#endif
