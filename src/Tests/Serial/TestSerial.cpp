//
// Created by Silt on 06.05.2017.
//

#include "TestSerial.h"

SETUP(TestSerial){
    REG_TEST(SerialWriterTest, 1, "[SerialWriter] Test Basic output functions");
}

TEST_IMPL(TestSerial, SerialWriterTest){
    char testString[] = "Hallo Welt";
    SerialSender sender("Serial_output.txt");
    sender.send(testString, 10);
    return FAILED;
}

//v UNUSED v//
BEFORE(TestSerial){return 0;}
AFTER(TestSerial){return 0;}
BEFORE_TC(TestSerial){return 0;}
AFTER_TC(TestSerial){return 0;}

