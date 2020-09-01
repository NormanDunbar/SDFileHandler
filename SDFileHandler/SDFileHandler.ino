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

// This is all you need.
#include "SDFileHandler.h"

//----------------------------------------------------------
// File name for testing purposes.
//----------------------------------------------------------
#define FILE_NAME "test.txt"


//----------------------------------------------------------
// Card select pin.
//----------------------------------------------------------
#define CARD_SELECT_PIN 4


//----------------------------------------------------------
// Initialise the SD Card system, returns true on success.
//----------------------------------------------------------
bool cardInit(byte cardSelectPin) {
    Serial.print("Initializing SD card...");

    if (!SD.begin(cardSelectPin)) {
        Serial.println("initialization failed!\n");
        return false;
    }
    
    Serial.println("initialization done.\n");
    return true;
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
// Setup. Does everything here.
//----------------------------------------------------------
void setup() {
    Serial.begin(9600);


    // Initialise the SD card system.
    if (!cardInit(CARD_SELECT_PIN)) {
        while (1) ;
    }

    // Open our test file.
    SDFileHandler h(FILE_NAME, FILE_WRITE);
    


    // Test data.
    byte Fred = 0xA5;
    int Wilma = -12345;
    short Barney = 616;
    long Betty = 1234567890;
    float BamBam = -666.616;
    char *Pebbles = "The Flintstones!";     // 16 bytes.

    uint32_t sizeWritten = 0;


    // Write the test data.
    Serial.println("\nWriting test data....\n");
    sizeWritten = h.write(Fred);
    Serial.print("Writing byte: Size written = ");
    Serial.println(sizeWritten);
    
    sizeWritten = h.write(Wilma);
    Serial.print("Writing int: Size written = ");
    Serial.println(sizeWritten);

    sizeWritten = h.write(Barney);
    Serial.print("Writing short: Size written = ");
    Serial.println(sizeWritten);

    sizeWritten = h.write(Betty);
    Serial.print("Writing long: Size written = ");
    Serial.println(sizeWritten);

    sizeWritten = h.write(BamBam);
    Serial.print("Writing float: Size written = ");
    Serial.println(sizeWritten);

    // Because we might need to know how many bytes to read back...
    sizeWritten = h.writeData(Pebbles, strlen(Pebbles));
    Serial.print("Writing C string: Size written = ");
    Serial.println(sizeWritten);


    
    // Close, then re-open for reading.
   
    h.reOpen(FILE_READ);

    // Read back test data.
    Serial.println("\nClearing the test data....\n");
    Fred = Wilma = Barney = Betty = BamBam = 0;
    memset(Pebbles, 0, strlen(Pebbles));


    Serial.println("\nReading  test data....\n");
    Fred = h.readByte();
    Serial.print("Fred = 0x");
    Serial.println(Fred, HEX);

    Wilma = h.readInt();
    Serial.print("Wilma (signed int)   = ");
    Serial.println(Wilma, DEC);
    Serial.print("Wilma (unsigned int) = ");
    Serial.println((unsigned int)Wilma, DEC);

    Barney = h.readShort();
    Serial.print("Barney (signed short)   = ");
    Serial.println(Barney, DEC);
    Serial.print("Barney (unsigned short) = ");
    Serial.println((unsigned short)Barney, DEC);

    Betty = h.readLong();
    Serial.print("Betty (signed long)   = ");
    Serial.println(Betty, DEC);
    Serial.print("Betty (unsigned long) = ");
    Serial.println((unsigned long)Betty, DEC);

    BamBam = h.readFloat();
    Serial.print("BamBam (signed float)   = ");
    Serial.println(BamBam, DEC);

    long tempSize = h.readLong();
    h.readData(Pebbles, tempSize);
    Serial.print("Pebbles (char *)   = ");
    Serial.println(Pebbles);
    Serial.print("Size of Pebbles = ");
    Serial.println(tempSize, DEC);

    // All done, shutdown.
    h.close();

    Serial.println("Done!");
    
}


void loop() {
    // There's nothing to see here! Move along!
}
