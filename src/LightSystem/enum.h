// =============================================================================
// enum.h : Defines enums in module LightSystem
// 
//    Copyright (C) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
//
// =============================================================================

#ifndef ENUM_H
#define ENUM_H


enum Level { OPERATING, NOT_OPERATING, WARNING_OCCURED, CLEAR_WARNING, CLEAR_ERROR, ERROR_OCCURED, ERROR_ACKNOWLEDGED, ERROR_GONE_UNACKNOWLEDGED, CLEAR_ALL };
enum Color { GREEN , YELLOW, RED, ALL }; //0-3
enum Frequency { ALWAYS_ON , ALWAYS_OFF , FAST_BLINKING = 500, SLOW_BLINKING = 1000}; /** in Millisec */
enum pulseIds { LIGHT_SYSTEM = 80 };

#endif
