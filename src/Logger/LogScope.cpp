/*
 * LogScope.cpp
 *
 *  Created on: 23.04.2017
 *      Author: jonasfuhrmann
 */

#include "LogScope.h"

#include "Logger.h"

LogScope::LogScope(const string& s)
	: logger_(Logger::getLogger()) , functionname_(s) {
	logger_.log("SCOPE")<<"entering "<<functionname_<<" \n";
}

LogScope::~LogScope() {
	logger_.log("SCOPE")<<"exiting "<<functionname_<<" \n";
}

