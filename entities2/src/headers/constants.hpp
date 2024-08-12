// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#pragma once

// Game version
#define ENTITIES2_VER       "v1.5.0"
// Cap
#define MAX_STAT_CAP        200
// Stuff
#define PLAYER_START_HP     100
#define PLAYER_START_AR     100
#define ENEMY_START_HP      100
#define ENEMY_START_AR      100
#define HEALTH_F            5
#define ARMOR_F             2
// OPTION TYPES
#define ATTACK              0
#define HEAL                1
#define ARMOR               2
#define STATUS              3
// FACTORS
#define ATTACK_F            5
#define HEAL_F              5
#define ARM_F               5
// STATUSES
#define STATUS_C            4
#define AUTO_HEAL           0
#define INCR_CRIT           1
#define INVIS               2
#define POISON              3
#define STATUS_TIME_LEFT    4
#define AUTO_HEAL_AMOUNT    10
#define POISON_AMOUNT       10
// ENERGY
#define STARTING_ENERGY     8
#define ENERGY_INC          2.5       // Energy increase per round
#define ENERGY_DECIMALS     2
#define MAX_ENERGY          50
#define ATTACK_ENERGY_F     2
#define HEAL_ENERGY_F       2.5
#define ARMOR_ENERGY_F      2.5