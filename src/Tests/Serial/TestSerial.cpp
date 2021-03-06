//
// Created by Silt on 06.05.2017.
//

#include "TestSerial.h"
#include "../Logger/Logger.h"
#include "../Logger/LogScope.h"

SETUP(TestSerial){
    //REG_TEST(SerialWriterTest, 1, "[SerialWriter] Test Basic output functions");
    //REG_TEST(OpenSernderReceiver, 2, "[SerialWriter] Test to open Receiver and Sender at the same time");
    //REG_TEST(ReadWrite,3, "[SerialWriter][SerialSender] Basic Input Output Test");
    //REG_TEST(Serilizeable, 4, "[ISerializable][SerialTestStub] Basic Test for the SerialTestObject");
#ifndef WINDOWS
    REG_TEST(RWOverSerial, 5, "[SerialWriter][SerialReader] Try basic writing from ser1 to ser 2");
#endif
}

TEST_IMPL(TestSerial, SerialWriterTest){
    char testString[] = "Hallo Welt nextrun";
    char filepath[] = "Serial_output.bin";
    SerialSender sender(filepath);
    sender.send(testString, sizeof(testString));
    if(sender.fail()){
        return TEST_PASSED;
    } else {
        return TEST_FAILED;
    }
}

TEST_IMPL(TestSerial, OpenSernderReceiver){
    char filepath[] = "Serial_inout.bin";
    SerialSender sender(filepath);
    SerialReceiver receiver (filepath);
    if(sender.fail() || receiver.fail()){
        return TEST_PASSED;
    } else {
        return TEST_FAILED;
    }
}

TEST_IMPL(TestSerial, ReadWrite){
    char filepath[] = "Serial_readwrite.bin";
    SerialSender sender(filepath);
    SerialReceiver receiver (filepath);
    char testString[] = "START Flitzndafoer_123456 123123 END";
    sender.send(testString, sizeof(testString));
    char* resu = receiver.receive();
    cout.write(resu, sizeof(testString));
    if(equal(testString, testString+sizeof(testString), resu)){
        return TEST_PASSED;
    } else {
        return TEST_FAILED;
    }
}

TEST_IMPL(TestSerial, Serilizeable) {
    SerialTestStub original(rand(),rand(), 0, rand());
    SerialTestStub copy;

    serialized obj_ser = original.serialize();
    copy.deserialize(obj_ser.obj);

    if(copy==original){
        return TEST_PASSED;
    } else {
        return TEST_FAILED;
    }
}

TEST_IMPL(TestSerial, RWOverSerial) {
	LOG_SCOPE;
    char sender_node[] = "/dev/ser1";
    char receiver_node[] = "/dev/ser2";

    SerialSender sender(sender_node);
    SerialReceiver receiver (receiver_node);
    receiver.reset();
    char testString[] = "START Flitzndafoer_123456 123123 END";
    sender.send(testString, sizeof(testString));
    char* resu = receiver.receive();
    cout.write(resu, sizeof(testString));
    if(memcmp(testString, resu, sizeof(testString))==0){
        return TEST_PASSED;
    } else {
        return TEST_FAILED;
    }
}

//v UNUSED v//
BEFORE(TestSerial){return 0;}
AFTER(TestSerial){return 0;}
BEFORE_TC(TestSerial){return 0;}
AFTER_TC(TestSerial){return 0;}



