/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    error_handler
 * @{
 *
 * @brief      Test Header of the ErrorHandler.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */
#ifndef TESTERRORHANDLER_H_
#define TESTERRORHANDLER_H_

#include "../TestFramework/TestCase.h"
#include "../TestFramework/TestFramework.h"

class TestErrorHandler : public TestCase
{
public:
	TestErrorHandler(int id, std::string brief) : TestCase(id, brief) { };
protected:
    TEST(test1);
    TEST_CASE_METHODS
};


#endif /* TESTERRORHANDLER_H_ */
/** @} */
