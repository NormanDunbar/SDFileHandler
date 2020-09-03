//----------------------------------------------------------
// This sketch demonstrates how to write data to a file on
// an SD card in an efficient manner writing the internal
// data type representation. Int data, for example, is
// written as two bytes and not, as "print" would do, in
// ASCII with one character for each digit.
//
// The SD Card reader should be connected as follows:
//
// GND -> Arduino GND.
// VCC -> Arduino 5V. (Unless yours is 3.3V!)
// MOSI -> Arduino D11
// MISO -> Arduino D12
// SCK -> Arduino D13.
// CS -> Arduino D4. (CARD_SELECT_PIN)
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


    // All done, shutdown.
    h.close();

    Serial.println("Done!");

}


void loop() {
    // There's nothing to see here! Move along!
}
