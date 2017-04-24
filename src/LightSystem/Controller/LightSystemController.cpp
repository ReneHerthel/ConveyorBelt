/*
 * LightSystemController_new.cpp
 *
 *  Created on: 24.04.2017
 *      Author: Matthis Keppner
 */

#include "LightSystemController.h"
#include "ITimer.h"

LightSystemController :: LightSystemController(int chid
		//, ITimer* timer
		, BLightSystem* boundary)
	: chid(chid)
	, timer(timer)
	, boundary(boundary)
{}


int LightSystemController::task(){
	// trying to get right access to the I/O hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
		std::cout << "Can't get Hardware access, therefore can't do anything."
				<< std::endl;
		return EXIT_FAILURE;
	}


return 1;
}



class Context {
private:
	struct State {//top-level state
		//virtual void signalA(){}//put code here for signalA in superstate
		virtual void green(){
			boundary.lightOff(ALL);
			new (this) Green;// change to state Green
		}
		virtual void yellow(){
			boundary.lightOff(ALL);
			new (this) Yellow_slow;// change to state Green
		}
		virtual void red(){
			boundary.lightOff(ALL);
			new (this) RED_on;
		}
		virtual void all(){
			new (this) all;
		}
		virtual void always_on(){}
		virtual void always_off(){}
		virtual void slow_blinking(){}
		virtual void fast_blinking(){}
		virtual void timer_sig(){}

	} *statePtr;   // a pointer to current state. Used for polymorphism.

	struct INIT : public State { //start state
	};
	struct Green : public State {
		virtual void always_on(){
			boundary.lightOn(GREEN);
		}
		virtual void always_off(){
			boundary.lightOff(GREEN);
		}
	};

	struct Yellow_slow : public State {
		virtual void always_on(){   //unsure if necessary
			boundary.lightOn(YELLOW);
		}
		virtual void always_off(){
			boundary.lightOff(YELLOW);
		}

		virtual void slow_blinking(){
			boundary.lightOn(YELLOW);
			setTimer(1000,123); //123 is a bad message FIXME real message
			new (this) Yellow_on;
		}

	};
	struct Yellow_on : public State {
			virtual void Timer_sig(){   //unsure if necessary
				if(msg)
				boundary.LightOff(YELLOW);
				setTimer(1000,)
			}
	};

	StateA stateMember;//The memory for the state is part of context object
	Data contextdata;  //Data is also kept inside the context object

	public:
	Context()
	: statePtr(&stateMember) // assigning start state
	, contextdata(0)         // initializing data
	{
		statePtr->data = &contextdata; // connecting state->data with the context data
	}

	void green(){statePtr->signalA();} // context delegates signals to state
	void yellow(){statePtr->signalA();}
	void red(){statePtr->signalA();}
	void all(){statePtr->signalA();} 	//Colors
	void always_on(){statePtr->signalA();}
	void always_off(){statePtr->signalA();}
	void slow_blinking(){statePtr->signalA();}
	void fast_blinking(){statePtr->signalA();}	//frequencies
	void timer_sig(){statePtr->signalA();}


};



