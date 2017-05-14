//
// Created by Silt on 06.05.2017.
//

#include "TestSerial.h"

SETUP(TestSerial){
    REG_TEST(SerialWriterTest, 1, "[SerialWriter] Test Basic output functions");
    REG_TEST(OpenSernderReceiver, 2, "[SerialWriter] Test to open Receiver and Sender at the same time");
    REG_TEST(ReadWrite,3, "[SerialWriter][SerialSender] Basic Input Output Test");
    REG_TEST(Serilizeable, 4, "[ISerializable][SerialTestStub] Basic Test for the SerialTestObject");
}

TEST_IMPL(TestSerial, SerialWriterTest){
    char testString[] = "Hallo Welt nextrun";
    char filepath[] = "Serial_output.bin";
    SerialSender sender(filepath);
    sender.send(testString, sizeof(testString));
    if(sender.fail()){
        return PASSED;
    } else {
        return FAILED;
    }
}

TEST_IMPL(TestSerial, OpenSernderReceiver){
    char filepath[] = "Serial_inout.bin";
    SerialSender sender(filepath);
    SerialReceiver receiver (filepath);
    if(sender.fail() || receiver.fail()){
        return PASSED;
    } else {
        return FAILED;
    }
}

TEST_IMPL(TestSerial, ReadWrite){
    char filepath[] = "Serial_readwrite.bin";
    SerialSender sender(filepath);
    SerialReceiver receiver (filepath);
    char testString[] = "Flitzndafoer_123456 123123";
    sender.send(testString, sizeof(testString));
    char* resu = receiver.receive();
    cout.write(resu, sizeof(testString));
    if(equal(testString, testString+sizeof(testString), resu)){
        return PASSED;
    } else {
        return FAILED;
    }
}

TEST_IMPL(TestSerial, Serilizeable) {
    SerialTestStub original(rand(),rand(), 0, rand());
    SerialTestStub copy;

    serialized obj_ser = original.serialize();
    copy.deserialize(obj_ser);

    if(copy==original){
        return PASSED;
    } else {
        return FAILED;
    }
}

//v UNUSED v//
BEFORE(TestSerial){return 0;}
AFTER(TestSerial){return 0;}
BEFORE_TC(TestSerial){return 0;}
AFTER_TC(TestSerial){return 0;}



