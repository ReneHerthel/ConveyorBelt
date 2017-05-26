//
// Created by Silt on 07.05.2017.
//

#ifndef CONVEYORBELT_SERIALRECEIVER_H
#define CONVEYORBELT_SERIALRECEIVER_H

#include <string>
#include <fcntl.h>

#ifndef WINDOWS
#include <termios.h>
#endif

using namespace std;

class SerialReceiver {
public:
    SerialReceiver(char* path);
    ~SerialReceiver();

    char* receive();
    char checksum(char* buff, uint16_t size);
    int readFromSerial(char* buff, uint32_t size);

    void operator()();

    void reset();

    int fail();
private:
    int in;
    int err; /*!<Err from IO */
};


#endif //CONVEYORBELT_SERIALRECEIVER_H
