//
// Created by Silt on 14.05.2017.
//

#ifndef CONVEYORBELT_SERIALTESTSTUB_H
#define CONVEYORBELT_SERIALTESTSTUB_H


#include "../../SerialPort/ISerializable.h"

class SerialTestStub : public ISerializable{
public:
    SerialTestStub(uint8_t value1, uint16_t value2, uint32_t zero, uint64_t value3);

    serialized serialize() override;

    template<class T> T deserialize(serialized ser) override;

    bool operator==(SerialTestStub const& rhs);

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
