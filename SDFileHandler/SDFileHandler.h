//----------------------------------------------------------
// About: SDFileHandler Class
// The standard SD File handling code is _borked_ on Arduino.
// This is an effort to get around that problem - these
// problems actually!
//
// FILE_WRITE - opens the file in APPEND mode, not WRITE. That
// is configured deliberately in the source. This "library"
// gets around that and FILE_WRITE will open at the start of
// the file. FILE_APPEND will replicate the existing
// FILE_WRITE behaviour.
//
// write() - only ever writes a single byte to
// the SD Card when used to write, say, an int or a float
// etc. It works perfectly when passed an array and a size.
//
// This class ensures that a <write> with a single
// parameter will indeed write the full length of the data.
//
//
// *Norman Dunbar*
//
// *31st August 2020.*
//----------------------------------------------------------

#include <stdint.h>
#include "WString.h"
#include <SPI.h>
#include <SD.h>


//----------------------------------------------------------
// Fix the Arduino SD library, it's borked!
//
// FILE_READ is ok and remains unchanged.
//
// FILE_WRITE is actually a FILE_APPEND. It's renamed below
// to FILE_APPEND.
//
// FILE_WRITE will now open at the start of the file.
//----------------------------------------------------------
#ifdef ARDUINO
    #ifdef FILE_WRITE
        #undef FILE_WRITE
        #define FILE_WRITE (O_READ | O_WRITE | O_CREAT)
        #define FILE_APPEND ((FILE_WRITE) | O_APPEND)
    #endif // FILE_WRITE
#endif // ARDUINO


//----------------------------------------------------------
// Yes, I *could* have inherited from File, but I chose not
// to. If I need the underlying code, I can call it through
// getHandle(). :o)
//----------------------------------------------------------
// Class: SDFileHandler
// This class wraps an existing Arduino File class and
// provides proper handling of binary data. The class allows
// data types, excluding 'String' because nobody in their
// right minds would use those in a sketch! (_Joke_!)
class SDFileHandler {

public:
    // Constructor: SDFileHandler
    // The constructor assumes that the SD Card system has
    // already been initialised and that no files are open.
    //
    // Parameters:
    //
    //  fileName - the file name which will be opened.
    //  openMode - the mode in which the file will be opened.
    //             The default is FILE_READ for reading only.
    //
    // Open Modes:
    //      FILE_READ - open the file for reading only. The
    //      file must already exist.
    //      FILE_WRITE - opens the file at the start and
    //      overwrites anything already there. The file will
    //      be created if it does not exist.
    //      FILE_APPEND - opens the file for writing. Existing
    //      contents remain untouched and new data is added at the end.
    //
    // If a file is to be opened for reading, it must exist on
    // the SD Card. If the file is being opened for writing,
    // in either of the two modes, it will be created if it
    // doesn't already exist.
    SDFileHandler(const char *fileName,
                  uint8_t openMode = FILE_READ);

    // Constructor: SDFileHandler
    // This constructor takes the same parameters as above,
    // but the filename is an Arduino String in this case.
    SDFileHandler(String fileName,
                  uint8_t openMode = FILE_READ);


    // Function: ~SDFileHandler
    // Closes down any opened files before the object goes
    // out of scope.
    ~SDFileHandler();


    // Function: reOpen
    // Given an open file, close it, then reopen it in
    // the specified mode.
    //
    // Parameter:
    //
    //  openMode - is the new mode in which the file should
    //  be re-opened.
    //
    // Open Modes:
    //      FILE_READ - open the file for reading only. The
    //      file must already exist.
    //      FILE_WRITE - opens the file at the start and
    //      overwrites anything already there. The file will
    //      be created if it does not exist.
    //      FILE_APPEND - opens the file for writing. Existing
    //      contents remain untouched and new data is added at the end.
    //
    // If a file is to be opened for reading, it must exist on
    // the SD Card. If the file is being opened for writing,
    // in either of the two modes, it will be created if it
    // doesn't already exist.
    void reOpen(uint8_t openMode);


    // Function: close
    // Close a file. There are no parameters as the file
    // handle held in <theFile> will be closed.
    void close();

    // If the File handle is not NULL, return true if
    // the file is open, else false.
    operator bool();


    // Function: getHandle
    // Return a handle to the underlying File which is stored
    // internally in <theFile>. The returned handle can be
    // used to call underlying File functions such as
    // *position* and *seek* etc.
    File getHandle() { return theFile; };

    // Function: write
    // Various write functions to correct the borked stuff in
    // the Arduino File implementation. The write function is
    // overloaded to allow the following data types to be
    // written to a file:
    //
    //  byte - 1 byte.
    //  short - 2 bytes little endian.
    //  int - 2 bytes little endian.
    //  long - 4 bytes little endian.
    //  float - 4 bytes.
    //  char * - all the bytes in the string, plus the zero
    //  byte at the end.
    //
    // Returns:
    // All write functions return the number of bytes written.
    //
    // See Also:
    //
    //  <writeData>
    size_t write(byte data);
    size_t write(short data);
    size_t write(int data);
    size_t write(long data);
    size_t write(float data);
    size_t write(char *data);
    size_t write(uint8_t *data, uint32_t dataLength);

    // Function: writeData
    // Write arbitrary data to the SD Card file. The data
    // written is preceeded by a long (4 bytes) word
    // containing the size of the following data. There is no
    // terminator byte.
    //
    // Parameters:
    //
    //  data - A pointer to the start of the data to be
    //  written.
    //  dataLength - the size of the data to be written.
    //
    // Returns:
    // The number of bytes written, plus 4, is returned.
    //
    // See Also:
    //
    //  <write>
    size_t SDFileHandler::writeData(uint8_t *data, uint32_t dataLength);

    // Function: readByte
    // Returns one byte from the SD Card file.
    byte readByte();

    // Function: readShort
    // Returns a pair of bytes, into a short variable, from
    // the SD Card file.
    short readShort();

    // Function: readInt
    // Returns a pair of bytes, into an int variable, from
    // the SD Card file.
    int readInt();

    // Function: readLong
    // Returns 4 bytes, into a long variable, from the SD
    // Card file.
    long readLong();

    // Function: readFloat
    // Returns 4 bytes, into a float variable, from the SD
    // Card file.
    float readFloat();

    // Function: readData
    // Returns a number of bytes, into an existing buffer,
    // from the SD Card file.
    //
    // Parameters:
    //
    //  buffer - the address of the buffer where the data
    // will be written to. It must be large enough to hold
    // the data being read plus, if necessary, a terminator.
    // bufferLength - the number of bytes to be read into the buffer.
    uint32_t readData(uint8_t *buffer, uint32_t bufferLength);

private:
    // Variable: theFile
    // This *private* variable holds onto the underlying File
    // handle. It is used internally and cannot be accessed
    // except by calling <getHandle>.
    File theFile;

    // Variable: theFileName
    // This *private* variable holds the filename that the
    // file was originally opened with. It will be in 8.3
    // format. It is only held for use by the <reOpen>
    // function, so that a file can, if necessary, be opened
    // for writing then re-opened for reading immediately
    // afterwards.
    char *theFileName;
};
