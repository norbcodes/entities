// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file energy_constants.hpp
 * \author norbcodes
 * \brief Useful macros for energy based code.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

// ENERGY
/**
 * \def STARTING_ENERGY
 * \brief Starting energy of each Entity.
 */
#define STARTING_ENERGY     8

/**
 * \def ENERGY_INC
 * \brief Energy increase per round.
 */
#define ENERGY_INC          2.5

/**
 * \def ENERGY_DECIMALS
 * \brief Used for printing only, how many decimals points to round to.
 */
#define ENERGY_DECIMALS     2

/**
 * \def MAX_ENERGY
 * \brief Maximum allowed energy for an Entity.
 */
#define MAX_ENERGY          50

/**
 * \def ATTACK_ENERGY_F
 * \brief Used to calculate energy cost for attack moves. See energy.cpp
 */
#define ATTACK_ENERGY_F     2

/**
 * \def HEAL_ENERGY_F
 * \brief Used to calculate energy cost for heal moves. See energy.cpp
 */
#define HEAL_ENERGY_F       2.5

/**
 * \def ARMOR_ENERGY_F
 * \brief Used to calculate energy cost for armor moves. See energy.cpp
 */
#define ARMOR_ENERGY_F      2.5