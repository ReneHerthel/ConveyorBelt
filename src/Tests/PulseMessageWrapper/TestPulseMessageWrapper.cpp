/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    wrapper
 * @{
 *
 * @brief      Test Function of the PulseMessageWrapper.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#include "TestPulseMessageWrapper.h"

#include "IPulseMessageReceiver.h"

#include "ThreadClient.h"
#include "ThreadServer.h"

#include <sys/neutrino.h>
#include <chrono>
#include <iostream>


SETUP(TestPulseMessageWrapper) {
    REG_TEST(test1, 1, "Send and receive a pulse message");
    return 1;
}

BEFORE_TC(TestPulseMessageWrapper) {
    // Empty.
	return 1;
}

AFTER_TC(TestPulseMessageWrapper) {
	// Empty.
	return 1;
}

BEFORE(TestPulseMessageWrapper) {
	// Empty.
	return 1;
}

AFTER(TestPulseMessageWrapper) {
    // Empty.
	return 1;
}

TEST_IMPL(TestPulseMessageWrapper, test1) {
    std::cout << "[TestPulseMessageWrapper] test 1" << std::endl;

    std::cout << "[TestPulseMessageWrapper] Start" << std::endl;

    // We need to create a new channel to give it to the both threads.
    int chid = ChannelCreate_r(0);

    if (chid < 0) {
        std::cout << "[TestPulseMessageWrapper] Channel creation failed" << std::endl;
    }

    ThreadServer* server = new ThreadServer(chid);

    std::cout << "[TestPulseMessageWrapper] Server created" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    ThreadClient* client = new ThreadClient(chid, 1);

    std::cout << "[TestPulseMessageWrapper] Client created" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "[TestPulseMessageWrapper] Done" << std::endl;

    rcv::msg_t structWithValues = server->receivePulseMessage();

    // You can also read structWithValues.code.
    if (structWithValues.value == 42 && structWithValues.code == 3) {
        return TEST_PASSED;
    }

    return TEST_FAILED; // not implemented yet.
}

TEST_IMPL(TestPulseMessageWrapper, test2) {
  std::cout << "[TestPulseMessageWrapper] test 1" << std::endl;

  std::cout << "[TestPulseMessageWrapper] Start" << std::endl;

  // We need to create a new channel to give it to the both threads.
  int chid = ChannelCreate_r(0);

  if (chid < 0) {
      std::cout << "[TestPulseMessageWrapper] Channel creation failed" << std::endl;
  }

  ThreadServer* server = new ThreadServer(chid);

  std::cout << "[TestPulseMessageWrapper] Server created" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  ThreadClient* client = new ThreadClient(chid, 2);

  std::cout << "[TestPulseMessageWrapper] Client created" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "[TestPulseMessageWrapper] Done" << std::endl;

  rcv_msg_t structWithValues = server->receivePulseMessage();

  // You can also read structWithValues.code
  if (structWithValues.value == 55 && structWithValues.code == 4) {
      return TEST_PASSED;
  }

  return TEST_FAILED; // not implemented yet.
}

/** @} */
