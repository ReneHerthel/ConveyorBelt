//
// Created by Silt on 25.05.2017.
//

#include "SerialProtocollTest.h"
#include "SerialTestStub.h"
#include "../../SerialPort/TopLevelProto/SerialProtocoll.h"

SETUP(SerialProtocollTest){
    REG_TEST(WrapObject, 1, "[SerialProtocol][SerialTestStub]Test to frame and deframe an object");
}

TEST_IMPL(SerialProtocollTest, WrapObject){
    SerialTestStub testStub(10,20,0,30); //just some numbers
    SerialProtocoll proto(SENDER);

    serialized ser;
    ser = proto.wrapInFrame(TRANSM_OUT, (uint32_t)&testStub);

    pulse tmp = proto.convToPulse((char *) ser.obj, ser.size);
    SerialTestStub resu = *((SerialTestStub*)tmp.value);
    if(resu == testStub){
        return PASSED;
    } else {
        return FAILED;
    }

}

//TEST_IMPL(SerialProtocollTest, TestSimpleMessages){}


//v UNUSED v//
BEFORE(SerialProtocollTest){return 0;}
AFTER(SerialProtocollTest){return 0;}
BEFORE_TC(SerialProtocollTest){return 0;}
AFTER_TC(SerialProtocollTest){return 0;}