/*
 * Copyright (C) 2017 Rene Herthel
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file LICENSE in the top level directory for more details.
 */

/**
 * @ingroup    TestEmbeddedRecorderStub
 * @{
 *
 * @brief      The stub object of the EmbeddedRecorder.
 *
 * @author     Rene Herthel <rene.herthel@haw-hamburg.de>
 */

#ifndef TESTEMBEDDEDRECORDERSTUB_H_
#define TESTEMBEDDEDRECORDERSTUB_H_

#include <iostream>

class TestEmbeddedRecorderStub {
public:
	/*
	 * @brief Default constructor.
	 */
	TestEmbeddedRecorderStub();


    /*
     * @brief Default constructor.
     */
	TestEmbeddedRecorderStub(int value);

	/*
	 * @brief Copy constructor.
	 */
	TestEmbeddedRecorderStub(const TestEmbeddedRecorderStub &obj);

	/*
	 * @brief Prints the value of the stub.
	 */
	void print(void) {
        std::cout << "[TestEmbeddedRecorderStub] value: " << m_value << std::endl;
	}

private:
    /*
     * @brief A random value of the stub object.
     */
	int m_value;
};

#endif /* TESTEMBEDDEDRECORDERSTUB_H_ */
/** @} */
