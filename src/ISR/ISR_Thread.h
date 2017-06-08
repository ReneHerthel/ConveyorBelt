/*
 * Name        :ISR
 * Author      : abt674
 * Version     : 0.2
 *  Copyright   : none
 */

#ifndef ISR_THREAD_H_
#define ISR_THREAD_H_

#include <stdint.h>
#include "ConveyorBelt-devel/src/HWaccess.h"
#include "Control.h"



class ISR_Thread{


    // Methoden deklarationen
    public:
	 	ISR_Thread(Control * control); ///< Standard Konstruktor. Offentlich Aufrufbar.
        virtual ~ISR_Thread();      ///< Standard Dekonstruktor.
        void execute();
};

#endif


