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
 * @brief      Test Header of the PulseMessageWrapper.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef TESTPULSEMESSAGEWRAPPER_H_
#define TESTPULSEMESSAGEWRAPPER_H_

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

class TestPulseMessageWrapper : public TestCase
{
public:
    /*
     * @brief Constructor.
     */
	  TestPulseMessageWrapper(int id, std::string brief) : TestCase(id, brief) { };

protected:
	  /*
	   * @brief The pulse message which is carried around.
	   */
    int testPulseMessage_ = 42;

    /*
     * @brief Test if the pulse message is send and received.
     */
    TEST(test1);

    TEST(test2);

    // Must have.
    TEST_CASE_METHODS
};

#endif /* TESTPULSEMESSAGEWRAPPER_H_ */
/** @} */
