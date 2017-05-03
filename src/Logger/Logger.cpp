/*
 * Logger.cpp
 *
 *  Created on: 23.04.2017
 *      Author: jonasfuhrmann
 */

#include "Logger.h"

Logger::Logger()
	: logginglevel_(DEBUG) { // set default level
	logfile_.open("/logging.txt",ios::trunc);
	logfile_<<"LOGFILE. Build: "<<__DATE__<<", "<<__TIME__<<endl;
}

Logger::~Logger() {
	logfile_<<"END OF LOGFILE"<<endl;
	logfile_.close();
}

Logger& Logger::getLogger() { // Meyers Singleton.
	static Logger Instance; // Will be deleted at the end.
	return Instance;
}

ofstream& Logger::log(string s) {
	logfile_<<time(NULL)<<" "<<s<<" "; // time ticks in seconds. Check OS for more accurate timer.
	return logfile_;
}

void Logger::setLoggingLevel(LEVEL level) {
	logfile_<<"setting output level to "<<level<<endl;
	logginglevel_ = level;
}

LEVEL Logger::getLoggingLevel() {
	return logginglevel_;
}

