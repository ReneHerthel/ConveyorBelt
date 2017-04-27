/*
 * LightSystemController_new.cpp
 *
 *  Created on: 24.04.2017
 *      Author: Matthis Keppner
 */

#include "LightSystemController.h"

class Context {
	private:
		struct State {//top-level state
			virtual void green(){
				boundary->lightOff(Color::ALL);
				new (this) Green;// change to state Green
			}
			virtual void yellow(){
				boundary->lightOff(Color::ALL);
				new (this) Yellow_slow;// change to state Green
			}
			virtual void red(){
				boundary->lightOff(Color::ALL);
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

			BLightSystem* boundary;
			ITimer* timer;
		} *statePtr;   // a pointer to current state. Used for polymorphism.

		struct Init : public State { //start state
		};
		struct Green : public State {
			virtual void always_on(){
				boundary->lightOn(Color::GREEN);
			}
			virtual void always_off(){
				boundary->lightOff(Color::GREEN);
			}
		};

		struct Yellow_slow : public State {
			virtual void always_on(){   //unsure if necessary
				boundary->lightOn(Color::YELLOW);
			}
			virtual void always_off(){
				boundary->lightOff(Color::YELLOW);
			}

			virtual void slow_blinking(){
				boundary->lightOn(Color::YELLOW);
				timer->setAlarm(SLOW, YELLOW_SLOW); //123 is a bad message FIXME real message
				new (this) Yellow_on;
			}

		};
		struct Yellow_on : public State {
				virtual void Timer_sig(){   //unsure if necessary
					if(msg==YELLOW_SLOW) {
						boundary->LightOff(Color::YELLOW);
						timer->setAlarm(SLOW,YELLOW_SLOW);
						new (this) Yellow_off;
					}
				}
		};
		struct Yellow_off : public State {
					virtual void Timer_sig(){   //unsure if necessary
						if(msg==YELLOW_SLOW){
							boundary->LightOn(Color::YELLOW);
							timer->setAlarm(SLOW,YELLOW_SLOW);
							new (this) Yellow_on;
						}
					}
		};

		struct Red : public State {
				virtual void always_on(){   //unsure if necessary
					boundary->lightOn(Color::RED);
				}
				virtual void always_off(){
					boundary->lightOff(Color::RED);
				}

				virtual void slow_blinking(){
					boundary->lightOn(Color::RED);
					timer->setAlarm(SLOW,RED_SLOW); //123 is a bad message. FIXME: real message
					new (this) Red_slow_on;
				}
				virtual void fast_blinking(){
					boundary->lightOn(Color::RED);
					timer->setAlarm(FAST,RED_FAST); //123 is a bad message. FIXME: real message
					new (this) Red_fast_on;
				}

		};
		struct Red_slow_on : public State {
			virtual void Timer_sig(){   //unsure if necessary
				if(msg==RED_SLOW) {
					boundary->LightOff(Color::RED);
					timer->setAlarm(SLOW,RED_SLOW);
					new (this) Red_slow_off;
				}
			}
		};
		struct Red_slow_off : public State {
			virtual void Timer_sig(){   //unsure if necessary
				if(msg==RED_SLOW){
					boundary->LightOn(Color::RED);
					timer->setAlarm(SLOW,RED_SLOW);
					new (this) Red_slow_on;
				}
			}
		};
		struct Red_fast_on : public State {
			virtual void Timer_sig(){   //unsure if necessary
				if(msg==RED_FAST) {
					boundary->LightOff(Color::RED);
					timer->setAlarm(FAST,RED_FAST);
					new (this) Red_fast_off;
				}
			}
		};
		struct Red_fast_off : public State {
			virtual void Timer_sig(){   //unsure if necessary
				if(msg==RED_FAST){
					boundary->LightOn(Color::RED);
					timer->setAlarm(FAST,RED_FAST);
					new (this) Red_fast_on;
				}
			}
		};

		Init StateMember;
		BLightSystem* boundary;

	public:
		Context(BLightSystem* boundary, ITimer* timer)
			: statePtr(&StateMember) // assigning start state
			, boundary(boundary)
			, timer(timer)
		{
			statePtr->boundary = boundary;
			statePtr->timer = timer;
		}

		enum Signal{
			GREEN,
			YELLOW,
			RED,
			ALL,
			ALWAYS_ON,
			ALWAYS_OFF,
			SLOW_BLINKING,
			FAST_BLINKING,
			YELLOW_SLOW,  //timermsg
			RED_SLOW,	  //timermsg
			RED_FAST	  //timermsg
		};

		void process(Signal s){
			cout<<typeid(*statePtr).name()<<"(signal="<<s<<") => ";
			(funcArray[s])(); // here is the transformation from the integer signal to the function call
			cout << typeid(*statePtr).name() <<endl;
		}

		vector<function<void(void)>> funcArray = { // initializer list for funcArray
				 [&] ( ) { statePtr->green();}, // context delegates signals to state
				 [&] ( ) { statePtr->yellow();},
				 [&] ( ) { statePtr->red();},
				 [&] ( ) { statePtr->all();},	//Colors
				 [&] ( ) { statePtr->always_on();},
				 [&] ( ) { statePtr->always_off();},
				 [&] ( ) { statePtr->slow_blinking();},
				 [&] ( ) { statePtr->fast_blinking();},	//frequencies
				 [&] ( ) { statePtr->timer_sig();},
				 [&] ( ) { statePtr->timer_sig();},
				 [&] ( ) { statePtr->timer_sig();}	//Timermsg
		};
};

LightSystemController :: LightSystemController(int chid, ITimer* timer, BLightSystem* boundary)
	: chid(chid)
	, timer(timer)
	, boundary(boundary)
	, isRunning(true) // FIXME: Lookup setting default values in constructor
{
	 std::thread controller(task);
}


int LightSystemController::task(){
	// trying to get right access to the I/O hardware
	if (ThreadCtl(_NTO_TCTL_IO_PRIV, 0) == -1) {
		std::cout << "Can't get Hardware access, therefore can't do anything." << std::endl;
		return EXIT_FAILURE;
	}

	Context c(boundary, timer);

	while(isRunning){
		struct _pulse pulse;

		int msg = MsgReceive_r(chid, &pulse, sizeof(_pulse),NULL);
			if(msg < 0) {
				// TODO error handling
				std::cout << "client MsgReceive_r failed" << std::endl;
			}
		c.process(pulse.value);
	}

	return 1;
}







