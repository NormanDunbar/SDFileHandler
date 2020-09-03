# SDFileHandler
Better SD Card File handler for Arduino.


This library was written because, in my opinion, the Arduino's implementation of the SD Card File class is *borked* in that:

* `FILE_WRITE` is actually a file APPEND. WTH? If I open a file for writing in any language, it starts at the beginning and overwrites existing data. If I wanted to append data, that's the mode I would use to open the file.

* None of the `write()` functions are overloaded, so you can write 1 byte, or you an write an array of bytes. You cannot call `myFile.write(anInt);` and get all (both) bytes of an `int` variable written, you get only the first one. (Note: This is not writing ASCII data to the file, it's writing internal format to the file.)

The library makes life easier to write various types of data to the SD card in the internal format. The various `print()` functions available in the IDE do already work fine -- if all you want is plain text in your files.

## Installation to the Arduino IDE
* Go to the releases area for the library. It's at https://github.com/NormanDunbar/SDFileHandler/releases/latest.
* Download as a zip file to somewhere safe.
* Open the Arduino IDE.
* Click Sketch->Include Library->Add .ZIP Library.
* Navigate to the location where yo saved the zip file.
* Select the `SDFileHandler-n.n.n.zip` file, `n.n.n` is the version, and OK.

After a brief pause the library will be added.

## Examples

Three examples have been added to your IDE. You will find them under File->Examples->SDFileHandler. They are:

* **Writing** - creates a file named `WRITE.TXT` on the SD card, and writes a `byte`, a `short`, an `int`, a `long`, a `float` and a C string (`char *`) to the file. The Serial Monitor displays the number of bytes written.

* **Reading** - opens the file `WRITE.TXT` on the SD card, reads all the above data back into various appropriately typed variables, and displays each one on the Serial Monitor.

* **Writing_and_Reading** - Combines both of the above sketches into one. The file for this test is called, `TEST.TXT`.


## Documentation
Documentation has been created with NaturalDocs (https://www.naturaldocs.org/) and can be found in the `NaturalDocs/HTML` directory if you clone or download the GitHub repository.

For normal users, read on...

### `SDFileHandler Class`
The standard SD File handling code is slightly *borked* on Arduino.  This is an effort to get around that problem -- these problems actually!

* FILE_WRITE	opens the file in APPEND mode, not WRITE. That is configured deliberately in the source. 

* The `write()` function only ever writes *a single byte* to the SD Card when used to write, say, an int or a float etc. It obviously works perfectly when passed an array and a size.

This class ensures that a `write()` with a single parameter will indeed write the full length of the data, and, that it can be read back.



#### FUNCTIONS

**Constructors**

```
SDFileHandler(const char *fileName,
              uint8_t openMode = FILE_READ
)

SDFileHandler(String fileName,
              uint8_t openMode = FILE_READ
)

```
There are two constructors. Both  assume that the SD Card system has already been initialised and that no files are open.

The filename can be passed as either a normal C string, or `char *`, or as an Arduino `String`.

The filename must be in the old MS-DOS style of 8 characters, maximum, a dot and a three character extension. This is known as "8.3" format.

The mode in which the file will be opened defaults to  FILE_READ for reading only.

##### Open Modes

**FILE_READ** - opens the file for reading only. The file must already exist.

**FILE_WRITE** - opens the file at the *beginning* and *overwrites* anything already there when written to. The file will be created if it does not exist.

**FILE_APPEND** - opens the file for writing at the *end*. Existing contents remain untouched and new data is added at the end.


**Note** If a file is to be opened for reading, it must exist on the SD Card. If the file is being opened for writing, in either of the two modes, it will be created if it doesn't already exist.

**reOpen()**

```
void reOpen(uint8_t openMode)
```

Given an open file, close it, then reopen it in the specified mode.


**close()**

```
void close()
```

Close a file. There are no parameters as the file handle held in internally will be closed.


**getHandle()**

```
File getHandle()
```

Returns a handle to the underlying `File` which is stored internally. The returned handle can be used to call underlying `File` functions such as `position()` and `seek()` etc.


**write()**

```
size_t write(	byte data)
size_t write(	short data)
size_t write(	int data)
size_t write(	long data)
size_t write(	float data)
size_t write(	char *data)
```

Various write functions to correct the borked stuff in the Arduino File implementation. The write function is overloaded to allow the appropriate data types to be written to a file.

Returns the number of bytes written.

**Note**    In the case of a `char *` being written, the terminating zero byte is also written, and included in the count returned.

For example:

```
char *testData = "Hello World!";
...
return mySDFile.write(testData);
```

Will return 12+1 or 13 bytes in total written. 

If a string, written in this manner, is to be read back, it needs to be read one byte at a time, into a buffer *known to be large enough*.

If it is not possible to know the size of the buffer before hand, use `writeData()` and `readData()`.


**writeData()**

```
size_t writeData(uint8_t *data, uint32_t dataLength)
```
Write arbitrary data to the SD Card file. The data written is preceded by a `long` (4 bytes) detailing the size of the following data. There is no terminator byte.

Returns the number of bytes written, plus 4.


**readByte()**
```
byte readByte()
```

Returns one byte from the SD Card file.

**readShort()**
```
short readShort()
```

Returns a pair of bytes, into a short variable, from the SD Card file.

**readInt()**
```
int readInt()
```

Returns a pair of bytes, into an int variable, from the SD Card file.

**readLong()**
```
long readLong()
```

Returns 4 bytes, into a long variable, from the SD Card file.

**readFloat()**
```
float readFloat()
```

Returns 4 bytes, into a float variable, from the SD Card file.

**readData()**
```
uint32_t readData(uint8_t *buffer, uint32_t bufferLength)
```

Returns a number of bytes, into a buffer, *which must be large enough*, from the SD Card file.


