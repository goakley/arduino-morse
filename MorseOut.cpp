/* Author: Glen Oakley
 */

#include "Arduino.h"
#include "MorseOut.h"

/*
void MorseOut::outputLetter(char c)
{
  switch(c) {
  case 'a': case 'A': dot();dash();break;
  case 'b': case 'B': dash();dot();dot();dot();break;
  case 'c': case 'C': dash();dot();dash();dot();break;
  case 'd': case 'D': dash();dot();dot();break;
  case 'e': case 'E': dot();break;
  case 'f': case 'F': dot();dot();dash();dot();break;
  case 'g': case 'G': dash();dash();dot();break;
  case 'h': case 'H': dot();dot();dot();dot();break;
  case 'i': case 'I': dot();dot();break;
  case 'j': case 'J': dot();dash();dash();dash();break;
  case 'k': case 'K': dash();dot();dash();break;
  case 'l': case 'L': dot();dash();dot();dot();break;
  case 'm': case 'M': dash();dash();break;
  case 'n': case 'N': dash();dot();break;
  case 'o': case 'O': dash();dash();dash();break;
  case 'p': case 'P': dot();dash();dash();dot();break;
  case 'q': case 'Q': dash();dash();dot();dash();break;
  case 'r': case 'R': dot();dash();dot();break;
  case 's': case 'S': dot();dot();dot();break;
  case 't': case 'T': dash();break;
  case 'u': case 'U': dot();dot();dash();break;
  case 'v': case 'V': dot();dot();dot();dash();break;
  case 'w': case 'W': dot();dash();dash();break;
  case 'x': case 'X': dash();dot();dot();dash();break;
  case 'y': case 'Y': dash();dot();dash();dash();break;
  case 'z': case 'Z': dash();dash();dot();dot();break;
  case '1': dot();dash();dash();dash();dash();break;
  case '2': dot();dot();dash();dash();dash();break;
  case '3': dot();dot();dot();dash();dash();break;
  case '4': dot();dot();dot();dot();dash();break;
  case '5': dot();dot();dot();dot();dot();break;
  case '6': dash();dot();dot();dot();dot();break;
  case '7': dash();dash();dot();dot();dot();break;
  case '8': dash();dash();dash();dot();dot();break;
  case '9': dash();dash();dash();dash();dot();break;
  case '0': dash();dash();dash();dash();dash();break;
  default: delay(_freq);
  }
  delay(_freq*3);
}
*/

MorseOut::MorseOut(byte pin, unsigned int freq)
{
  isDisplaying = false;
  setMorsePin(pin);
  setFrequency(freq);
  isLooping = false;
  message = NULL;
  letterIndex = 0;
  letterStartTime = 0;
}

bool MorseOut::setMorsePin(byte pin)
{
  if (isDisplaying)
    return false;
  pinMode(pin, OUTPUT);
  _pin = pin;
  return true;
}
bool MorseOut::setFrequency(unsigned int freq)
{
  if (isDisplaying)
    return false;
  _freq = freq;
  return true;
}


bool MorseOut::setString(char* str)
{
  if (isDisplaying)
    return false;
  message = str;
  return true;
}
bool MorseOut::setString(String &str)
{
  if (isDisplaying)
    return false;
  message = new char[str.length()+1];
  int i;
  for (i = 0; i < str.length(); i++)
    message[i] = str.charAt(i);
  message[str.length()] = '\0';
  return true;
}

bool MorseOut::start(bool loop)
{
  if (isDisplaying)
    return false;
  isLooping = loop;
  isDisplaying = true;
  letterIndex = 0;
  letterStartTime = millis();
  update();
  return true;
}

bool MorseOut::stop()
{
  if (!isDisplaying)
    return false;
  digitalWrite(_pin, LOW);
  isDisplaying = false;
  return true;
}

void MorseOut::gracefulStop()
{
  isLooping = false;
}

bool MorseOut::isDone() { return isDisplaying; }

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

void MorseOut::setLight(char c, unsigned long t)
{
  bool high = false;
  switch(c)
  {
  /*
  case 'a': case 'A':
    if (t < _freq || (t > _freq*2 && t < _freq*5))
	  high = true;
	break;
  case 'b': case 'B':
    if (t < _freq*3 || (t > _freq*4 && t < _freq*5) || (t > _freq*6 && t < _freq*7) || (t > _freq*8 && t < _freq*9))
	  high = true;
	break;
  case 'o': case 'O':
    if (t < _freq*3 || (t > _freq*4 && t < _freq*7) || (t > _freq*8 && t < _freq*11))
	  high = true;
	break;
  case 's': case 'S':
    if (t < _freq || (t > _freq*2 && t < _freq*3) || (t > _freq*4 && t < _freq*5))
	  high = true;
	break;
  */
  case 'a': case 'A':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*5) high = true;
	else high = false;
	break;
  case 'b': case 'B':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else high = false;
	break;
  case 'c': case 'C':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*11) high = true;
	else high = false;
	break;
  case 'd': case 'D':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else high = false;
	break;
  case 'e': case 'E':
    if (t < _freq) high = true;
	else high = false;
	break;
  case 'f': case 'F':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else false;
	break;
  case 'g': case 'G':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else high = false;
	break;
  case 'h': case 'H':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else high = false;
	break;
  case 'i': case 'I':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else high = false;
	break;
  case 'j': case 'J':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*13) high = true;
	else high = false;
	break;
  case 'k': case 'K':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else high = false;
	break;
  case 'l': case 'L':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else false;
	break;
  case 'm': case 'M':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else high = false;
	break;
  case 'n': case 'N':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else high = false;
	break;
  case 'o': case 'O':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*11) high = true;
	else high = false;
	break;
  case 'p': case 'P':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*11) high = true;
	else false;
	break;
  case 'q': case 'Q':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*13) high = true;
	else high = false;
	break;
  case 'r': case 'R':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else false;
	break;
  case 's': case 'S':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else high = false;
	break;
  case 't': case 'T':
    if (t < _freq*3) high = true;
	else high = false;
	break;
  case 'u': case 'U':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else false;
	break;
  case 'v': case 'V':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else high = false;
	break;
  case 'w': case 'W':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else high = false;
	break;
  case 'x': case 'X':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*11) high = true;
	else high = false;
	break;
  case 'y': case 'Y':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*13) high = true;
	else high = false;
	break;
  case 'z': case 'Z':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*11) high = true;
	else high = false;
	break;
  case '1':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*13) high = true;
	else if (t < _freq*14) high = false;
	else if (t < _freq*17) high = true;
	else high = false;
	break;
  case '2':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*11) high = true;
	else if (t < _freq*12) high = false;
	else if (t < _freq*15) high = true;
	else false;
	break;
  case '3':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*13) high = true;
	else high = false;
	break;
  case '4':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*11) high = true;
	else high = false;
	break;
  case '5':
    if (t < _freq) high = true;
	else if (t < _freq*2) high = false;
	else if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else high = false;
	break;
  case '6':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*5) high = true;
	else if (t < _freq*6) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*11) high = true;
	else high = false;
	break;
  case '7':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*9) high = true;
	else if (t < _freq*10) high = false;
	else if (t < _freq*11) high = true;
	else if (t < _freq*12) high = false;
	else if (t < _freq*13) high = true;
	else high = false;
	break;
  case '8':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*11) high = true;
	else if (t < _freq*12) high = false;
	else if (t < _freq*13) high = true;
	else if (t < _freq*14) high = false;
	else if (t < _freq*15) high = true;
	else high = false;
	break;
  case '9':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*11) high = true;
	else if (t < _freq*12) high = false;
	else if (t < _freq*15) high = true;
	else if (t < _freq*16) high = false;
	else if (t < _freq*17) high = true;
	else high = false;
	break;
  case '0':
    if (t < _freq*3) high = true;
	else if (t < _freq*4) high = false;
	else if (t < _freq*7) high = true;
	else if (t < _freq*8) high = false;
	else if (t < _freq*11) high = true;
	else if (t < _freq*12) high = false;
	else if (t < _freq*15) high = true;
	else if (t < _freq*16) high = false;
	else if (t < _freq*19) high = true;
	else high = false;
	break;
  }
  digitalWrite(_pin, (high ? HIGH : LOW));
}

unsigned int MorseOut::getDuration(char c)
{
  switch(c) {
  case 'a': case 'A':
  case 'n': case 'N':
  case 's': case 'S':
    return _freq*8;
  case 'b': case 'B':
  case 'f': case 'F':
  case 'k': case 'K':
  case 'l': case 'L':
  case 'v': case 'V':
  case 'w': case 'W':
  case '5':
    return _freq*12;
  case 'c': case 'C':
  case 'o': case 'O':
  case 'p': case 'P':
  case 'x': case 'X':
  case 'z': case 'Z':
  case '4':
  case '6':
    return _freq*14;
  case 'd': case 'D':
  case 'g': case 'G':
  case 'h': case 'H':
  case 'm': case 'M':
  case 'r': case 'R':
  case 'u': case 'U':
    return _freq*10;
  case 'e': case 'E':
    return _freq*4;
  case 'i': case 'I':
  case 't': case 'T':
    return _freq*6;
  case 'j': case 'J':
  case 'q': case 'Q':
  case 'y': case 'Y':
  case '3':
  case '7':
    return _freq*16;
  case '1':
  case '9':
    return _freq*20;
  case '2':
  case '8':
    return _freq*18;
  case '0':
    return _freq*22;
  // '\0' means end of message
  case '\0': return _freq*10;
  // default assumes space character(s)
  default: return _freq*4;
  }
}
