/*
* Copyright (C) 2017 Rene Herthel
*
* This file is subject to the terms and conditions of the MIT License.
* See the file LICENSE in the top level directory for more details.
*/

/**
* @ingroup    led
* @{
*
* @brief      Function declaration of the LED component
*
* @author     Rene Herthel <rene.herthel@haw-hamburg.de>
*/

#ifndef BLED_H_
#define BLED_H_

class BLED {
public:
	virtual void on() = 0;
	virtual void off() = 0;
};

#endif /* BLED_H_ */
/** @} */
