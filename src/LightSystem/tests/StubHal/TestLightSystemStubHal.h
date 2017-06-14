/*
 * TestLightSystemStubHal.h : 
 * 
 * Copyright (c) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 */

#ifndef TESTLIGHTSYSTEMSTUBHAL_H_
#define TESTLIGHTSYSTEMSTUBHAL_H_

#include <iostream>
#include <chrono>
#include <thread>
#include "LightSystemStubHal.h"

class TestLightSystemStubHal {
public:
    int main(int argc, char *argv[]);
    void task();
};

#endif /* TESTLIGHTSYSTEMSTUBHAL_H_ */
