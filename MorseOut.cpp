/* Author: Glen Oakley
 */

#include "Arduino.h"
#include "MorseOut.h"
#include <stdlib.h>
#include <string.h>


const char* MORSE_KEY[] = 
{"", /*NUL*/
"-.-.-",
"-.-.-",
"...-.-",
"...-.-",
"-.-",
"...-.",
"", /*BEL*/
"", /*BS*/
"", /*TAB*/
"", /*LF*/
"", /*VT*/
"", /*FF*/
"", /*CR*/
"", /*SO*/
"", /*SI*/
"", /*DLE*/
"", /*DC1*/
"", /*DC2*/
"", /*DC3*/
"", /*DC4*/
"........",
".-...",
"...-.-",
"", /*CAN*/
"...-.-",
"", /*ESC*/
"", /*FS*/
"", /*GS*/
"", /*RS*/
"", /*US*/
"", /* */
"", /*!*/
".-.-.-",
".-..-.",
"", /*#*/
"", /*$*/
"", /*%*/
"", /*&*/
".----.",
"-.--.",
"-.--.-",
"-..-",
".-.-.",
"--..--",
"-....-",
".-.-.-",
"-..-.",
"-----",
".----",
"..---",
"...--",
"....-",
".....",
"-....",
"--...",
"---..",
"----.",
"---...",
"", /*;*/
"", /*<*/
"-...-",
"", /*>*/
"..--..",
".--.-.",
".-",
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
"--..",
"-.--.",
"-..-.",
"-.--.-",
"", /*^*/
"", /*_*/
".----.",
".-",
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
"--..",
"-.--.",
"", /*|*/
"-.--.-",
"", /*~*/
""}; /*DEL*/


MorseOut::MorseOut(byte pin, unsigned int freq)
{
  _pin = pin;
  _freq = freq;
  _bufferCapacity = 16;
  _messageBuffer = (char*)malloc(16*sizeof(char));
  _bufferSize = 0;
  _bufferPointer = 0;
  _doFlush = false;
}

bool MorseOut::pushData(char d)
{
  char passon[2] = { d, '\0' };
  return pushData(passon);
}
bool MorseOut::pushData(char* d)
{
  unsigned int length = strlen(d);
  if (length + _bufferSize > _bufferCapacity) {
    char* realloced = NULL;
    if (realloced = (char*)realloc(_messageBuffer, 
	                               _bufferCapacity*2*sizeof(char))) {
	  _messageBuffer = realloced;
	  _bufferCapacity *= 2;
	  unsigned int i;
	  for (i = 0; i < _bufferPointer; i++) {
	    _messageBuffer[i+_bufferSize] = _messageBuffer[i];
	  }
	} else {
	  return false;
	}
  unsigned int insert = _bufferPointer+_bufferSize;
  for (unsigned int i = 0; i < length; i++) {
    insert = (insert+1)%_bufferCapacity;
	_messageBuffer[insert] = d[i];
  }
  _bufferSize += length;
  return true;
  }
}
bool MorseOut::pushData(String d)
{
  char passon[d.length()+1];
  d.toCharArray(passon, d.length()+1);
  return pushData(passon);
}

bool MorseOut::isIdle() { return (_bufferSize == 0); }

void MorseOut::flush() { _doFlush = true; }

void MorseOut::update()
{
  if (!_bufferSize)
    return;
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
