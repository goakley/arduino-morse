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
  char* _messageBuffer;
  unsigned int _bufferCapacity;
  unsigned int _bufferSize;
  unsigned int _bufferPointer;
 public:
  /* Constructor
   * Creates a new MorseOut object, with the specified 
   * pin for output and the specified frequency, defined as 
   * the length that one dot is displayed
   */
  MorseOut(byte = 13, unsigned int = 200);
  /* Destructor
   */
  ~MorseOut();
  /* pushData
   * Pushes a string of data onto the queue
   * Returns false if there is no room for the specified data
   */
  bool pushData(char);
  bool pushData(char*);
  bool pushData(String);
  /* isIdle
   * Returns true if the queue is empty
   */
  bool isIdle();
  /* flush
   * Clears the buffer after the currently executing character 
   * has completed
   */
  void flush();
  /* update
   * Updates the output
   * This needs to be called regularly
   */
  void update();
};

#endif
