//
// Created by Silt on 07.05.2017.
//

#include "SerialReceiver.h"

SerialReceiver::SerialReceiver(string path) {
    instream.open(path, ofstream::in | ofstream::binary);
}

SerialReceiver::~SerialReceiver() {
    instream.close();
}

bool SerialReceiver::fail() {
    return instream.fail();
}
