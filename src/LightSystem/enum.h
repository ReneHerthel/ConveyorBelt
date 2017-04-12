// =============================================================================
// enum.h : Defines enums in module LightSystem
// 
//    Copyright (C) 2017 Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
//
// =============================================================================

#ifndef ENUM_H
#define ENUM_H

// TODO: Put all enums in a single place
enum Frequency { AlwaysOn, AlwaysOff, FastBlinking, SlowBlinking };
enum Color { Green, Yellow, Red };
enum Level { operating, notOperating, warning, clearWarning, clearError, errorOccured, errorAcknowledged, errorGoneUnacknowledged, clearAll };

#endif
