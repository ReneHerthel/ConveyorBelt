//
// Created by Silt on 14.05.2017.
//

#ifndef CONVEYORBELT_SERIALTESTSTUB_H
#define CONVEYORBELT_SERIALTESTSTUB_H


#include "../../SerialPort/ISerializable.h"
#include <stdint.h>
#include <stdio.h>
#include <iostream>

class SerialTestStub : public ISerializable{
public:
    SerialTestStub();

    SerialTestStub(uint8_t value1, uint16_t value2, uint32_t zero, uint64_t value3);

    serialized serialize() override;

    bool deserialize(void *obj) override;

    bool operator==(SerialTestStub const& rhs);

    void print(void){
    	std::cout << " Val1: " << value1 << " Val2: " << value2 << " Zero: " << zero << " Val3: " << value3 << std::endl;
    }

private:
    typedef struct __attribute__ ((packed)) obj_members{
        uint8_t value1;
        uint16_t value2;
        uint32_t zero;
        uint64_t value3;
    } obj;

    uint8_t value1;
    uint16_t value2;
    uint32_t zero;
    uint64_t value3;
};


#endif //CONVEYORBELT_SERIALTESTSTUB_H
