/* MorseOut
 * Used to provide a means of communicating morse code 
 * through a digital output pin.
 *
 * Author: Glen Oakley
 */

#ifndef MORSEOUT_H
#define MORSEOUT_H

#include "Arduino.h"

class MorseOut
{
  private:
    byte _pin;
    unsigned int _freq;
	char* message;
	bool isLooping;
	bool isDisplaying;
	byte letterIndex;
	unsigned long letterStartTime;
	void setLight(char, unsigned long);
	unsigned int getDuration(char);
  public:
    /* Constructor
	 * Creates a new MorseOut object, with the specified 
	 * pin for output and the specified frequency, defined as 
	 * the length that one dot is displayed
	 */
    MorseOut(byte = 13, unsigned int = 200);
	/* setString
	 * Associates the specified character array / string 
	 * with this MorseOut object
	 * Returns false if unsuccessful (currently outputting)
	 */
	bool setString(char*);
	bool setString(String &);
	/* start
	 * Outputs the morse code sequence, loops if specified
	 * Returns false if already outputting
	 */
	bool start(bool = false);
	/* stop
	 * Instantly stops outputting the morse code
	 * Returns false if already stopped
	 */
	bool stop();
	/* gracefulStop
	 * Stops outputting the morse code after the current iteration 
	 * of the code finishes
	 */
	void gracefulStop();
	/* isDone
	 * Returns true if the MorseOut object is currently not 
	 * outputting anything
	 */
	bool isDone();
	/* update
	 * Updates (advances, continues) the output of the morse code 
	 * associated with this MorseOut object
	 */
	void update();
	/* setMorsePin
	 * Sets what pin this MorseOut object outputs to; 
	 * cannot be changed while the object is outputting
	 * Returns true if set successfully
	 */
    bool setMorsePin(byte);
	/* setFrequency
	 * Sets the frequency at which this MorseOut object outputs; 
	 * cannot be changed while the object is outputting
	 * Returns true if set successfully
	 */
    bool setFrequency(unsigned int);
};

#endif
