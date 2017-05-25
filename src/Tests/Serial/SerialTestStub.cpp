//
// Created by Silt on 14.05.2017.
//

#include "SerialTestStub.h"

serialized SerialTestStub::serialize() {
    serialized ser;
    ser.size = sizeof(value1, value2, zero, value3);

    ser.obj = new obj{value1,value2,zero, value3};

    return ser;
}

bool SerialTestStub::deserialize(void *ser) {
    obj* tmp = (obj*)ser;
    this->value1 = tmp->value1;
    this->value2 = tmp->value2;
    this->zero = tmp->zero;
    this->value3 = tmp->value3;

    return true;
}

SerialTestStub::SerialTestStub(uint8_t value1, uint16_t value2, uint32_t zero, uint64_t value3) : value1(value1),
                                                                                                  value2(value2),
                                                                                                  zero(zero),
                                                                                                  value3(value3) {}

bool SerialTestStub::operator==(SerialTestStub const &rhs) {
    return ( value1 == rhs.value1   &&
             value2 == rhs.value2   &&
             zero   == rhs.zero     &&
             value3 == rhs.value3);
}

SerialTestStub::SerialTestStub() {}
