/**
 *       @file  enum.h
 *      @brief  Define enums for module LightSystem
 *
 * Detailed description starts here.
 *
 *     @author  Stephan Jänecke <stephan.jaenecke@haw-hamburg.de>
 *
 *   @internal
 *     Created  05/06/2017
 *   Copyright  Copyright (c) 2017 Stephan Jänecke
 */

#ifndef LIGHTSYSTEMENUM_H
#define LIGHTSYSTEMENUM_H


/**
 * Define warning levels
 */
enum Level {
    OPERATING, /**< @brief Unit is operating, green light is on constantly */
    NOT_OPERATING, /**< @brief Unit is not operating, all lights are out */
    WARNING_OCCURED, /**< @brief Warning has occurred, yellow light is blinking */
    CLEAR_WARNING,  /**< @brief  Warning has been cleared, yellow light is off */
    CLEAR_ERROR, /**< @brief Error has been cleared, red light is off */
    ERROR_OCCURED, /**< @brief Error occurred, red light blinks quickly */
    ERROR_ACKNOWLEDGED, /**< @brief Error has been acknowledged, red light is on constantly */
    ERROR_GONE_UNACKNOWLEDGED, /**< @brief Error has gone unacknowledged, red light blinks slowly */
    CLEAR_ALL  /**< @brief Clear everything, all lights are out */
};
/**
 * Define available colors
 */
enum Color {
    GREEN,
    YELLOW,
    RED,
    ALL_COLORS /**< @brief Manipulate all lights at once */
};
/**
 * Define frequencies in Milliseconds
 */
enum Frequency {
    ALWAYS_ON,  /**< @brief Turn off light */
    ALWAYS_OFF, /**< @brief Turn on light constantly */
    FAST_BLINKING = 500,
    SLOW_BLINKING = 1000
};

/**
 * Define module spaces for pulse messages
 */
/* FIXME: Define globally */
enum pulseIds { LIGHT_SYSTEM = 80 };

#endif
