//----------------------------------------------------------
// The standard SD File handling code is borked on Arduino!
// This is an effort to get around that problem - those
// problems actually!
//
// FILE_WRITE opens the file in APPEND mode, not WRITE. That
// is configured deliberately in the source. This "library"
// gets around that and FILE_WRITE will open at the start of
// the file. FILE_APPEND will replicate the existing 
// FILE_WRITE behaviour.
//
// The write() function only ever writes a single byte to
// the SD Card when used to write, say, an int or a float
// etc. It works perfectly when passed an array and a size.
// This library ensures that a write() with a single 
//  parameter will indeed write the full length of the data.
//
//
// Norman Dunbar
// 31st August 2020.
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
class SDFileHandler {

public:
    // Constructors. Assumes that the SD Card system has 
    // been initialised and that no files are open.    
    SDFileHandler(const char *fileName, 
                  uint8_t openMode = FILE_READ);
                  
    SDFileHandler(String fileName, 
                  uint8_t openMode = FILE_READ);


    // Destructor.
    ~SDFileHandler();

    
    // Given an open file, close it, then reopen it in
    // the specified mode.
    void reOpen(uint8_t openMode);

    // Close a file.
    void close();

    // If the File handle is not NULL, return true if
    // the file is open, else false.
    operator bool();
    
    // Return a handle to the underlying File. Used for
    // stuff like position() and so on.
    File getHandle() { return theFile; };

    // Various write functions to correct the borked stuff. 
    // They all return the number of bytes written.   
    size_t write(byte data);
    size_t write(short data);
    size_t write(int data);
    size_t write(long data);
    size_t write(float data);
    size_t write(char *data);
    size_t write(uint8_t *data, uint32_t dataLength);
    size_t SDFileHandler::writeData(uint8_t *data, uint32_t dataLength);
    
    // Matching read functions. 
    byte readByte();
    short readShort();
    int readInt();
    long readLong();
    float readFloat();
    uint32_t readData(uint8_t *buffer, uint32_t bufferLength);

private:
    File theFile;
    char *theFileName;
};
