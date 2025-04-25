// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file energy_constants.hpp
 * \author norbcodes
 * \brief Useful macros for energy based code.
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
 */

#pragma once

// ENERGY
/**
 * \def STARTING_ENERGY
 * \brief Starting energy of each Entity.
 */
#define STARTING_ENERGY     5.0

/**
 * \def ENERGY_INC
 * \brief Energy increase per round.
 */
#define ENERGY_INC          5.0

/**
 * \def MAX_ENERGY
 * \brief Maximum allowed energy for an Entity.
 */
#define MAX_ENERGY          50

/**
 * \def ATTACK_ENERGY_F
 * \brief Used to calculate energy cost for attack moves. See energy.cpp
 */
#define ATTACK_ENERGY_F     1.4

/**
 * \def HEAL_ENERGY_F
 * \brief Used to calculate energy cost for heal moves. See energy.cpp
 */
#define HEAL_ENERGY_F       2.8

/**
 * \def ARMOR_ENERGY_F
 * \brief Used to calculate energy cost for armor moves. See energy.cpp
 */
#define ARMOR_ENERGY_F      3.2

/**
 * \def REROLL_MOVE_COST
 * \brief How much energy to regenerate moves.
 */
#define REROLL_MOVE_COST    10.0

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0