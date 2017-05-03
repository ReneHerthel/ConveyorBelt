/*
 * Logger.h
 *
 *  Created on: 23.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_LOGGER_LOGGER_H_
#define SRC_LOGGER_LOGGER_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#define LOG_DEBUG \
    if(Logger::getLogger().getLoggingLevel() < DEBUG); \
	else Logger::getLogger().log("DEBUG")
#define LOG_WARNING \
	if(Logger::getLogger().getLoggingLevel() < WARNING); \
	else Logger::getLogger().log("WARNING")
#define LOG_ERROR \
	if(Logger::getLogger().getLoggingLevel() < ERROR); \
	else Logger::getLogger().log("ERROR")

#define LOG_SET_LEVEL(value) Logger::getLogger().setLoggingLevel(value);
#define LOG_SCOPE LogScope logscope(__FUNCTION__);

using namespace std;

enum LEVEL {ERROR,WARNING,DEBUG};

class Logger {
public:
	static Logger& getLogger();
	ofstream& log(string s);
	void setLoggingLevel(LEVEL level);
	LEVEL getLoggingLevel();
private:
	Logger();
	~Logger();
	LEVEL logginglevel_;
	ofstream logfile_;
};

#endif /* SRC_LOGGER_LOGGER_H_ */
