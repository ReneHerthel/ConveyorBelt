//
// Created by Silt on 07.05.2017.
//

#ifndef CONVEYORBELT_SERIALRECEIVER_H
#define CONVEYORBELT_SERIALRECEIVER_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class SerialReceiver {
public:
    SerialReceiver(string path);
    ~SerialReceiver();

    char* receive();
    char checksum(char* buff, uint16_t size);

    bool fail();
private:
    ifstream instream;
};


#endif //CONVEYORBELT_SERIALRECEIVER_H
