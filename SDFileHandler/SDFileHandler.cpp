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


#include "SDFileHandler.h"

    // Constructors. Assumes that the SD Card system has been 
    // initialised and that no files are open.    
    SDFileHandler::SDFileHandler(const char *fileName, 
                                 uint8_t openMode = FILE_READ) {
        size_t nameLength = strlen(fileName);
        
        theFileName = (char *)malloc(nameLength + 1);
        if (theFileName) {
            strncpy(theFileName, fileName, nameLength);
            theFileName[nameLength] = '\0';
        }
        
        theFile = SD.open(fileName, openMode);
    }
   
    SDFileHandler::SDFileHandler(String fileName, 
                                 uint8_t openMode = FILE_READ) {
        SDFileHandler(fileName.c_str(), openMode);
    }


    // Destructor - close the file if open.
    SDFileHandler::~SDFileHandler() {
        if (theFile) {
            theFile.close();
        }

        if (theFileName)
            free(theFileName);
    }

    // Close a file.
    void SDFileHandler::close() {
        theFile.close();
    }
    
    
    // Close an open file, then reopen it in the new mode.
    void SDFileHandler::reOpen(uint8_t openMode) {
        close();
        theFile = SD.open(theFileName, openMode);
    }


    // Various write functions to correct the borked stuff.
    size_t SDFileHandler::write(byte data) {
        return theFile.write(data);        
    }
    
    size_t SDFileHandler::write(short data) {
        return theFile.write((uint8_t *)&data, sizeof(short));
    }
    
    size_t SDFileHandler::write(int data) {
        return theFile.write((uint8_t *)&data, sizeof(int));
    }
    
    size_t SDFileHandler::write(long data) {
        return theFile.write((uint8_t *)&data, sizeof(long));
    }
    
    size_t SDFileHandler::write(float data) {
        return theFile.write((uint8_t *)&data, sizeof(float));
    }
    
    size_t SDFileHandler::write(char *data) {
        return theFile.write((uint8_t *)data, strlen(data));
    }
    
    size_t SDFileHandler::write(uint8_t *data, uint32_t dataLength) {
        return theFile.write(data, dataLength);
    }

    size_t SDFileHandler::writeData(uint8_t *data, uint32_t dataLength) {
        size_t temp;
        temp = theFile.write((uint8_t *)&dataLength, sizeof(long));
        // Should return 4 + length of string.
        return temp + theFile.write(data, dataLength);
    }
    
    

    // Bool operator.
    SDFileHandler::operator bool() {
        if (theFile) return true;
        return false;
    }


    // Various read functions.
    byte SDFileHandler::readByte() {
        return theFile.read();
    }
    
    short SDFileHandler::readShort() {
        short data;
        theFile.read((uint8_t *)&data, sizeof(short));
        return data;
    }
    
    int SDFileHandler::readInt() {
        int data;
        theFile.read((uint8_t *)&data, sizeof(int));
        return data;
    }
    
    long SDFileHandler::readLong() {
        long data;
        theFile.read((uint8_t *)&data, sizeof(long));
        return data;
    }
    
    float SDFileHandler::readFloat() {
        float data;
        theFile.read((uint8_t *)&data, sizeof(float));
        return data;
    }
    
    uint32_t SDFileHandler::readData(uint8_t *buffer, uint32_t bufferLength) {
        return theFile.read(buffer, bufferLength);
    }
    
    


/*
//----------------------------------------------------------
// Open the test file on the card, returns handle on success
// or NULL on failure. 
// 
// WARNING: Calling with mode = FILE_WRITE will actually
//          open at the end. For this reason, I'm setting 
//          the position to the start after opening. Reading
//          the file opens at the start anyway.
//
// NOTE: Only one file can be open at any time.
//----------------------------------------------------------
File openFile(const char *fileName);
File openFile(const String fileName);
File openFile(const char *fileName, uint8_t mode) {
    File theFile;
    Serial.print("\nOpening file: ");
    Serial.print(fileName);
    Serial.print(" ...");
    theFile = SD.open(fileName, mode);
    if (theFile) {
        Serial.println("opened successfully.");
    } else {
        Serial.println("failed to open.");
        return theFile;
    }

    // File is open, where are we?
    Serial.print("File position is currently: ");
    Serial.println(theFile.position());

    // If the mode is FILE_WRITE, reset to the start.
    // No longer required with the above fix. Was appending.
    if (mode == FILE_WRITE) {
        theFile.seek(0);
        Serial.print("File position is now: ");
        Serial.println(theFile.position());
    }
    
    return theFile;    
}


//----------------------------------------------------------
// Close the test file on the card.
//----------------------------------------------------------
void closeFile(const File fileHandle) {
    Serial.print("Closing file...");
    fileHandle.close();
    Serial.println("closed");
}


//----------------------------------------------------------
// This should (!) read a single byte from the SD card file.
//----------------------------------------------------------
void readByte(File dataFile, byte *data) {
    dataFile.read((uint8_t *)data, sizeof(byte));
}


//----------------------------------------------------------
// This should (!) read a single int from the SD card file.
//----------------------------------------------------------
void readInt(File dataFile, int *data) {
    dataFile.read((uint8_t *)data, sizeof(int));
}

//----------------------------------------------------------
// Setup. Does everything here.
//----------------------------------------------------------
void setup() {
    Serial.begin(9600);

    // Initialise the SD card system.
    if (!cardInit(CARD_SELECT_PIN)) {
        while (1) ;
    }

    // Open our test file.
    File myFile = openFile(FILE_NAME, FILE_WRITE);
    if (!myFile) {
        while (1) ;
    }

    // Test data.
    byte Fred = 0xA5;
    int Wilma = 12345;
    uint32_t sizeWritten = 0;


    // Write a byte and an int.
    sizeWritten = myFile.write(Fred);
    Serial.print("Writing byte: Size written = ");
    Serial.println(sizeWritten);
    
    sizeWritten = myFile.write((uint8_t *)&Wilma, sizeof(int));
    Serial.print("Writing int: Size written = ");
    Serial.println(sizeWritten);

    // Close, re-open for reading.
    closeFile(myFile);
    myFile = openFile(FILE_NAME, FILE_READ);
    if (!myFile) {
        while (1) ;
    }

    // Read back one byte and one int.
    Fred = Wilma = 0;

    readByte(myFile, &Fred);
    Serial.print("Fred = 0x");
    Serial.println(Fred, HEX);

    readInt(myFile, &Wilma);
    Serial.print("Wilma (signed int)   = ");
    Serial.println(Wilma, DEC);
    Serial.print("Wilma (unsigned int) = ");
    Serial.println((unsigned)Wilma, DEC);

    // All done, shutdown.
    closeFile(myFile);
    
}


void loop() {
    // There's nothing to see here! Move along!
}

*/
