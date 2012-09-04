Arduino Morse
=============

A Morse Code library for the Arduino microcontroller.

To use the library, simply go to "Downloads -> Download as zip" and unzip it into the library directory of the Arduino software (the structure of the repository is formatted like a custom Arduino library).

Features
--------

The "MorseOut" object can output Morse Code using [International Morse Code](http://www.itu.int/rec/R-REC-M.1677-1-200910-I/) letters, numerals, and timings.  The pin designated as the Morse Pin will be pulled high to signal a dot/dash.  A MorseOut object muse have its 'update' method called in the Arduino run loop; otherwise, it will not update the output of the code.  While running, the Morse signal can be stopped gracefully or immediately.  See "MorseOut.h" for a detailed API description.

An example, "SOS", has been provided with the library.