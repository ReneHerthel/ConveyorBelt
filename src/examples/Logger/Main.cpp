/*
 * Main.cpp
 *
 *  Created on: 23.04.2017
 *      Author: jonasfuhrmann
 */

#include "src/Logger/Logger.h"
#include "src/Logger/LogScope.h"

int main(void) {
	LOG_SCOPE; // Log scope for function - log enter, exit
	LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG << "Hello main\n";
}



