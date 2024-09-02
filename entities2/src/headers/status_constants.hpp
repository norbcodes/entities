// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file status_constants.hpp
 * \author norbcodes
 * \brief Useful macros for Status based code.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

// STATUSES
/**
 * \def STATUS_C
 * \brief Number of statuses.
 */
#define STATUS_C            5

/**
 * \def AUTO_HEAL
 * \brief AutoHeal id number. Basically an enum.
 */
#define AUTO_HEAL           0

/**
 * \def INCR_CRIT
 * \brief IncreasedCrit id number.
 */
#define INCR_CRIT           1

/**
 * \def INVIS
 * \brief Invis id number.
 */
#define INVIS               2

/**
 * \def POISON
 * \brief Poison id number.
 */
#define POISON              3

/**
 * \def THORNS
 * \brief Thorns id number.
 */
#define THORNS              4

// Data
/**
 * \def STATUS_TIME_LEFT
 * \brief Default value of how long Statuses last.
 */
#define STATUS_TIME_LEFT    4

/**
 * \def AUTO_HEAL_AMOUNT
 * \brief Amount of health AutoHeal regenerates.
 */
#define AUTO_HEAL_AMOUNT    10

/**
 * \def POISON_AMOUNT
 * \brief Amount of health AutoHeal takes.
 */
#define POISON_AMOUNT       10