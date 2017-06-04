//
// Created by Silt on 07.05.2017.
//

#ifndef CONVEYORBELT_SERIALRECEIVER_H
#define CONVEYORBELT_SERIALRECEIVER_H

#include <string>
#include <fcntl.h>
#include <stdint.h>

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

    /**
     * Used to create a thread for receiving data
     * @param chid  channel used to communicate with Serial
     */
    void operator()(int chid, char* path);

    void reset();

    int fail();
private:
    int in;
    int err; /*!<Err from IO */
};


#endif //CONVEYORBELT_SERIALRECEIVER_H