//
// Created by Silt on 06.05.2017.
//

#include "TestSerial.h"

SETUP(TestSerial){
    REG_TEST(SerialWriterTest, 1, "[SerialWriter] Test Basic output functions");
    REG_TEST(OpenSernderReceiver, 2, "[SerialWriter] Test to open Receiver and Sender at the same time");
    REG_TEST(ReadWrite,3, "[SerialWriter][SerialSender] Basic Input Output Test");
}

TEST_IMPL(TestSerial, SerialWriterTest){
    char testString[] = "Hallo Welt";
    SerialSender sender("Serial_output.bin");
    sender.send(testString, 10);
    return FAILED;
}

TEST_IMPL(TestSerial, OpenSernderReceiver){
    SerialSender sender("Serial_inout.bin");
    SerialReceiver receiver ("Serial_inout.bin");
    if(sender.fail() || receiver.fail()){
        return FAILED;
    } else {
        return PASSED;
    }
}

TEST_IMPL(TestSerial, ReadWrite){
    SerialSender sender("Serial_readwrite.bin");
    SerialReceiver receiver ("Serial_readwrite.bin");
    char testString[] = "Whatwhathwhat!";
    sender.send(testString, sizeof(testString));
    //delete &sender;
    char* resu = receiver.receive();
    cout.write(resu, sizeof(testString));
}

//v UNUSED v//
BEFORE(TestSerial){return 0;}
AFTER(TestSerial){return 0;}
BEFORE_TC(TestSerial){return 0;}
AFTER_TC(TestSerial){return 0;}

