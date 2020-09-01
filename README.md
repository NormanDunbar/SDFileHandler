# SDFileHandler
Better SD Card File handler for Arduino.

*More docs to follow, sorry, but check out the example for details of how to use this.*


Briefly, the Arduino's implementation of the SD Card File class is *borked* in that:

* `FILE_WRITE` is actually a file APPEND.
* None of the `write()` functions are overloaded, so you can write 1 byte, or you an write an array of bytes. You cannot call `myFile.write(anInt);` and get all (both) bytes of an `int` variable written, you get only the first one. (Note: This is not writing ASCII data to the file, it's writing internal format to the file.)


The code here makes life easier to write various types of data to the SD card in the internal format. The various `print()` functions do work fine.


1st September 2020.
