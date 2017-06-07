/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    main controller
 * @{
 *
 * @brief      Header declaration of the main controller.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef SRC_MAINCONTROLLER_MAINCONTROLLER_H_
#define SRC_MAINCONTROLLER_MAINCONTROLLER_H_

#include "IPulseMessageReceiver.h"
#include "PulseMessageReceiverService.h"

class MainController {
public:
    /*
     * @brief The constructor.
     */
    MainController();

    /*
     * @brief The destructor.
     */
    ~MainController();

    /*
     * @brief This methods waits for messages to handle them between other components.
     */
    void messageInterpreter();

private:
    /*
     * @brief A reference to the pulse message receiver.
     */
    rcv::PulseMessageReceiverService * m_receiver;

    /*
     * @brief A thread, which receives and interprets the incoming pulse messages.
     */
    std::thread m_messageInterpreter;

    /*
     * @brief A flag, which could be used to end the message interpreter thread.
     */
    bool m_messageInterpreterIsRunning;

    /*
     * @brief The own channel ID of the MainController to receive messages.
     */
    int m_chid;

    /* TODO: Add a reference to:
     *       EmbeddedRecorder,
     *       ErrorHandling,
     *       E.T.C.
     */
};

#endif /* SRC_MAINCONTROLLER_MAINCONTROLLER_H_ */
/** @} */
