/*
 * Name        :ISR
 * Author      : abt674
 * Version     : 0.2
 *  Copyright   : none
 */

#ifndef ISR_THREAD_H_
#define ISR_THREAD_H_

#include <stdint.h>
#include "HWaccess.h"
#include "Control.h"

class ISR {
// Methoden deklarationen
public:
	 	ISR(Control * control); ///< Standard Konstruktor. Offentlich Aufrufbar.
    virtual ~ISR();      ///< Standard Dekonstruktor.
    void operator()();
};

#endif
