/*
 * SignalDistributer.cpp
 *
 *  Created on: 21.06.2017
 *      Author: aca619
 */

#include "SignalDistributer.h"

SignalDistributer::SignalDistributer(PuckManager *puckManager, SortingSwichtControl *ssCntrl):
	 puckManager_(puckManager)
	,ssCntrl_(ssCntrl_)
{}

SignalDistributer::~SignalDistributer() {}

void SignalDistributer::process(rcv::msg_t msg){
	switch(msg.code){

	}
}

void SignalDistributer::interrupt(interrupts::interruptSignals signal){

}

void SignalDistributer::height(HeightMeasurement::signal_t signal){

}

void SignalDistributer::serial(Serial_n::ser_proto_msg){

}


