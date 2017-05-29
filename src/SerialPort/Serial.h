//
// Created by Silt on 26.05.2017.
//

#ifndef CONVEYORBELT_SERIAL_H
#define CONVEYORBELT_SERIAL_H


#include "SerialReceiver.h"
#include "SerialSender.h"
#include "TopLevelProto/ITopLvlProtocoll.h"
#include "TopLevelProto/SerialProtocoll.h"
#include "IPulseMessageReceiver.h"
#include "PulseMessageReceiverService.h"
#include "IPulseMessageSender.h"
#include "PulseMessageSenderService.h"
class Serial {
public:
    /**
     * Create a new Endpoint for a Serial Communication
     * @param rec The Object containing the thread that will be reading from the device node
     * @param sender The Object containing the thread that will be writing to the device node
     * @param proto The Protocol used to transmit messages
     * @param channel_in Wait for cmd on this channel
     * @param channel_out Send received data on this channel
     */
    Serial(SerialReceiver &rec, SerialSender &sender, ITopLvlProtocoll &proto, int channel_in, int channel_out);

    /**
     * The Serial thread
     */
    void run();



private:
    SerialReceiver& rec;             /// Object holding the thread to receive data from device node
    SerialSender& sender;            /// Used to send data to device note
    ITopLvlProtocoll& proto;         /// Protocol used with Serial communication
    IPulseMessageReceiver *ch_in;    /// Incoming cmd; incoming data from receiver
    IPulseMessageSender *ch_out;      /// Outgoing data
};


#endif //CONVEYORBELT_SERIAL_H
