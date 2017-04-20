// =============================================================================
// enum.h : Defines enums in module LightSystem
// 
//    Copyright (C) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
//
// =============================================================================

#ifndef ENUM_H
#define ENUM_H

/**
 *	in Millisec
 */
enum Frequency { ALWAYS_ON, ALWAYS_OFF, FAST_BLINKING = 500, SLOW_BLINKING = 1000};
enum Color { GREEN, YELLOW, RED, ALL };
enum Level { OPERATING, NOT_OPERATING, WARNING, CLEAR_WARNING, CLEAR_ERROR, ERROR_OCCURED, ERROR_ACKNOWLEDGED, ERROR_GONE_UNACKNOWLEDGED, CLEAR_ALL };

#endif
