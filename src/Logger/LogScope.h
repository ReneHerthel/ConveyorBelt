/*
 * LogScope.h
 *
 *  Created on: 23.04.2017
 *      Author: jonasfuhrmann
 */

#ifndef SRC_LOGGER_LOGSCOPE_H_
#define SRC_LOGGER_LOGSCOPE_H_

class LogScope {
public:
	LogScope(const string& s);
	~LogScope();
private:
	Logger& logger_;
	string functionname_;
};

#endif /* SRC_LOGGER_LOGSCOPE_H_ */
