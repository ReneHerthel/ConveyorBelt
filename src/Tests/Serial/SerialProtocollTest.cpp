//
// Created by Silt on 25.05.2017.
//

#include "SerialProtocollTest.h"
#include "SerialTestStub.h"
#include "../../SerialPort/TopLevelProto/SerialProtocoll.h"
#include "../../SerialPort/TopLevelProto/ITopLvlProtocoll.h"

SETUP(SerialProtocollTest){
    REG_TEST(WrapObject, 1, "[SerialProtocol][SerialTestStub]Test to frame and deframe an object");
    REG_TEST(TestSimpleMessages, 2, "[SerialProtocol] Passing the simple messages");
}

TEST_IMPL(SerialProtocollTest, WrapObject){
    SerialTestStub testStub(10,20,0,30); //just some numbers
    SerialProtocoll proto(SENDER); //does not matter if sender or receiver

    serialized ser;
    ser = proto.wrapInFrame(TRANSM_OUT, (uint32_t)&testStub);

    pulse tmp = proto.convToPulse((char *) ser.obj);
    SerialTestStub resu = *((SerialTestStub*)tmp.value);
    if(resu == testStub){
        return TEST_PASSED;
    } else {
        return TEST_FAILED;
    }

}

TEST_IMPL(SerialProtocollTest, TestSimpleMessages){
    msg list[] = {ACCEPT, STOP, RESUME, INVALID, RECEIVED};
    void *buff;
    SerialProtocoll proto(SENDER); //does not really matter if sender or receiver for this test
    for(int i = 0; i < (sizeof(list) / sizeof(list[0])); i++){
        msg resu;
        buff = proto.wrapInFrame(SER_IN, list[i]).obj;
        resu = (msg) proto.convToPulse(buff).value;
        if(resu != list[i]){
            return TEST_FAILED;
        }
    }
    return TEST_PASSED;
}


//v UNUSED v//
BEFORE(SerialProtocollTest){return 0;}
AFTER(SerialProtocollTest){return 0;}
BEFORE_TC(SerialProtocollTest){return 0;}
AFTER_TC(SerialProtocollTest){return 0;}