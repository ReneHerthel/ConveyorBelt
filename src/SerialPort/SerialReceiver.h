//
// Created by Silt on 07.05.2017.
//

#ifndef CONVEYORBELT_SERIALRECEIVER_H
#define CONVEYORBELT_SERIALRECEIVER_H

#define SER_REC_TIMEOUT 50 //5 Sec timeout
#define SER_REC_IN 85 //TODO Make uniform
#define SER_REC_FAIL 86

#include <string>
#include <fcntl.h>
#include <stdint.h>

#ifndef WINDOWS
#include <termios.h>
#endif

using namespace std;

class SerialReceiver {
public:
    SerialReceiver(char* path_);
    ~SerialReceiver();

    /**
     * Receive a msg from Serial
     * Length doesnt need to be transferred, becouse this must be handled by the top lvlv protcoll
     * Frames with lost bytes will be dropped
     * @return the bytes read
     */
    char* receive();

    /**
     * Used to create a thread for receiving data
     * Note that the buffer returned by this via Puilse Msg must be deleted after usage
     * @param chid  channel used to communicate with Serial
     */
    void operator()(int chid);

    /**
     * Reset the serial device (clear buffers)
     */
    void reset();

    /**
     * Kill the thread using the functor
     * ATTENTION: Use join after calling this to assure that the thread is dead
     * NOTE: Obj needs to be passed as reference to the stack
     */
    void kill();

    int fail();
private:
    /**
     * Calc a checksum
     * @param buff The bytes to check
     * @param size size of buff
     * @return checksum byte
     */
    char checksum(char* buff, uint16_t size);

    /**
     * Read from serial
     * @param buff
     * @param size
     * @return Returns -1 if the communication timed out, return 0 at success
     */
    int readFromSerial(char* buff, uint32_t size);

    int in;
    int err; /*!<Err from IO */
    bool running;
    string path;
};


#endif //CONVEYORBELT_SERIALRECEIVER_H
