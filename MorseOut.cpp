/* Author: Glen Oakley
 */

#include "Arduino.h"
#include "MorseOut.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


const char* MORSE_KEY[] = 
  {"", /****NUL****/
   "-.-.-",
   "-.-.-",
   "...-.-",
   "...-.-",
   "-.-",
   "...-.",
   "", /****BEL****/
   "", /****BS****/
   "", /****TAB****/
   "", /****LF****/
   "", /****VT****/
   "", /****FF****/
   "", /****CR****/
   "", /****SO****/
   "", /****SI****/
   "", /****DLE****/
   "", /****DC1****/
   "", /****DC2****/
   "", /****DC3****/
   "", /****DC4****/
   "........",
   ".-...",
   "...-.-",
   "", /****CAN****/
   "...-.-",
   "", /****ESC****/
   "", /****FS****/
   "", /****GS****/
   "", /****RS****/
   "", /****US****/
   "", /**** ****/
   "", /****!****/
   ".-.-.-",
   ".-..-.",
   "", /****#****/
   "", /****$****/
   "", /****%****/
   "", /****&****/
   ".----.",
   "-.--.",
   "-.--.-",
   "-..-",
   ".-.-.",
   "--..--",
   "-....-",
   ".-.-.-",
   "-..-.",
   "-----",/*0*/
   ".----",
   "..---",
   "...--",
   "....-",
   ".....",
   "-....",
   "--...",
   "---..",
   "----.",/*9*/
   "---...",
   "", /****;****/
   "", /****<****/
   "-...-",
   "", /****>****/
   "..--..",
   ".--.-.",
   ".-",/*A*/
   "-...",
   "-.-.",
   "-..",
   ".",
   "..-.",
   "--.",
   "....",
   "..",
   ".---",
   "-.-",
   ".-..",
   "--",
   "-.",
   "---",
   ".--.",
   "--.-",
   ".-.",
   "...",
   "-",
   "..-",
   "...-",
   ".--",
   "-..-",
   "-.--",
   "--..",/*Z*/
   "-.--.",
   "-..-.",
   "-.--.-",
   "", /****^****/
   "", /****_****/
   ".----.",
   ".-",/*a*/
   "-...",
   "-.-.",
   "-..",
   ".",
   "..-.",
   "--.",
   "....",
   "..",
   ".---",
   "-.-",
   ".-..",
   "--",
   "-.",
   "---",
   ".--.",
   "--.-",
   ".-.",
   "...",
   "-",
   "..-",
   "...-",
   ".--",
   "-..-",
   "-.--",
   "--..",/*z*/
   "-.--.",
   "", /****|****/
   "-.--.-",
   "", /****~****/
   ""}; /****DEL****/


MorseOut::MorseOut(byte pin, unsigned int freq)
{
  _pin = pin;
  _freq = freq;
  _bufferCapacity = 16;
  _messageBuffer = (char*)malloc(16*sizeof(char));
  for (unsigned int i = 0; i < 16; i++)
    _messageBuffer[i] = 0;
  _bufferSize = 0;
  _bufferPointer = 0;
}
MorseOut::~MorseOut()
{
  free(_messageBuffer);
}

bool MorseOut::pushData(char d)
{
  char passon[2] = { d, '\0' };
  return pushData(passon);
}
bool MorseOut::pushData(char* d)
{
  unsigned int length = strlen(d);
  // check for potential buffer overflow
  if (length + _bufferSize > _bufferCapacity) {
    // the potential for buffer overflow needs to be handled
    // attempt to increase the size of the buffer
    char* realloced = (char*)realloc(_messageBuffer, 
				     _bufferCapacity*2*sizeof(char));
    // handle the success/failure of the buffer resize
    if (realloced) {
      for (unsigned int i = _bufferCapacity; i < _bufferCapacity*2; i++)
	_messageBuffer[i] = 0;
      // shift the data already in the buffer to its new position
      _messageBuffer = realloced;
      _bufferCapacity *= 2;
      for (unsigned int i = 0; i < _bufferPointer; i++) {
	_messageBuffer[i+_bufferSize] = _messageBuffer[i];
	_messageBuffer[i] = 0;
      }
    } else {
      // the buffer is unable to hold the new data
      return false;
    }
  }
  unsigned int insert = _bufferPointer+_bufferSize;
  for (unsigned int i = 0; i < length; i++) {
    // check for unhandled characters, which are ignored
    if (!strlen(MORSE_KEY[d[i]]))
      continue;
    // store the new data in the buffer
    insert = (insert+1)%_bufferCapacity;
    _messageBuffer[insert] = d[i];
  }
  _bufferSize += length;
  return true;
}
bool MorseOut::pushData(String d)
{
  char passon[d.length()+1];
  d.toCharArray(passon, d.length()+1);
  return pushData(passon);
}

bool MorseOut::isIdle()
{
  return (_messageBuffer[_bufferPointer] == 0)?true:false;
}

void MorseOut::flush()
{
  for (unsigned int i = _bufferPointer; _bufferSize != 0; _bufferSize--) {
    _messageBuffer[i] = 0;
    _bufferPointer = (_bufferPointer+1)%_bufferCapacity;
  }
  _bufferPointer = 0;
}

void MorseOut::update()
{
  if (isIdle())
    return;
  static int start_time_char = -1;
}

/*
  void MorseOut::update()
  {
  // don't update if it's not even displaying anything!
  if (!isDisplaying)
  return;
  unsigned long currentTime = millis();
  while ((currentTime-letterStartTime) > getDuration(message[letterIndex]))
  {
  if (message[letterIndex] == '\0')
  {
  if (!isLooping)
  {
  stop();
  }
  else
  {
  letterIndex = 0;
  letterStartTime += getDuration('\0');
  }
  }
  else
  {
  letterStartTime += getDuration(message[letterIndex++]);
  }
  }
  setLight(message[letterIndex], currentTime-letterStartTime);
  }
*/
