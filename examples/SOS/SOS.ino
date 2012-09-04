#include <MorseOut.h>

MorseOut m;

void setup()
{
  // set up a Morse object on default pin 13 with default frequency 200ms,
  //     the pin will automatically be set to OUTPUT mode
  m = MorseOut();
  // associate Morse 'm' with the string "SOS"
  m.setString("SOS");
  // start displaying the message once, and loop it (true) (default is false)
  m.start(true);
}

void loop()
{
  // update the Morse object 'm'
  m.update();
  // after 20 seconds, stop displaying the message AFTER this iteration
  //     of the message is complete (use .stop() to instantly stop).
  if (millis() > 20000)
    m.gracefulStop();
}
