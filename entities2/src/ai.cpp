// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file ai.cpp
 * \author norbcodes
 * \brief The AI, the antagonist of entities2!
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
 * \details This file contains one huge function, which uses black magic (not really)<br>
 *          that returns a number - the chosen move.
 */

#include <cstdint>

#include "move_constants.hpp"
#include "status_constants.hpp"
#include "entity.hpp"
#include "utils.hpp"
#include "rng.hpp"

/**
 * \def SKIP
 * \brief A smol little define, 4 means the Ai chose to skip the round.
 */
#define SKIP 4

/**
 * \brief The actual brain of the AI.
 * \details This is a very long function of intricate code, that carefully picks out<br>
 *          an appropriate move to select.
 * \param[in] picks_list Array of moves to choose from.
 * \param[in] types_list Array of types of each move.
 * \param[in] energies The energy costs of each move.
 * \param[in] player A constant reference to an instance of Entity class.
 * \param[in] enemy A constant reference to an instance of Entity class. This is us!
 * \param[in] difficulty_scale The difficulty of the current battle. Affects the AI.
 * \return The chosen move.
 */
uint32_t AiChoose(uint32_t* picks_list, uint32_t* types_list, double* energies, const Entity& player, const Entity& enemy, uint32_t difficulty_scale)
{
    // The ai
    // I copy+pasted a lot of this shit

    // First, check if we can actually get any moves
    uint32_t _sum = 0;
    for (int i = 0; i != 4; i++)
    {
        if (energies[i] <= enemy.GetEnergy())
        {
            _sum += 1;
        }
    }

    // all falses
    if (_sum == 0)
    {
        return SKIP;
    }

    // FIRST AND FOREMOST, IF WEAKNESS EXISTS, GO FOR IT.
    for (int i = 0; i != 4; i++)
    {
        if (picks_list[i] == WEAKNESS && types_list[i] == STATUS && energies[i] <= enemy.GetEnergy())
        {
            return i;
        }
    }

    if ((static_cast<int32_t>(rng(0, 100))) > enemy.GetHealth())
    {
        /*
        Difficulty table:
        EASY               60
        MEDIUM             50
        HARD               40
        */
        if (rng(0, 100) > (60 - (difficulty_scale * 5)))
        {
            // Prioritize choosing poison
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == POISON && energies[i] <= enemy.GetEnergy() && types_list[i] == STATUS)
                {
                    return i;
                }
            }

            uint32_t highest_att = 0;
            // Get highest attack
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] > highest_att && energies[i] <= enemy.GetEnergy() && types_list[i] == ATTACK)
                {
                    highest_att = picks_list[i];
                }
            }
            // Choose said attack
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == highest_att && types_list[i] == ATTACK)
                {
                    return i;
                }
            }
        }
        else
        {
            /*
            Difficulty table:
            EASY               50
            MEDIUM             40
            HARD               30
            */
            if (rng(0, 100) > (50 - (difficulty_scale * 5)))
            {
                uint32_t status_count = 0;
                // Get status count
                for (int i = 0; i != 4; i++)
                {
                    if (types_list[i] == STATUS && energies[i] <= enemy.GetEnergy())
                    {
                        status_count++;
                    }
                }
                // Get the x-th status
                uint32_t which = rng(0, status_count - 1);
                // Now actually get it
                for (int i = 0; i != 4; i++)
                {
                    if (types_list[i] == STATUS && energies[i] <= enemy.GetEnergy())
                    {
                        if (which == 0)
                        {
                            return i;
                        }
                        else
                        {
                            which--;
                        }
                    }
                }
            }
            else
            {
                // Choose armor
                uint32_t highest_ar = 0;
                // Get highest armor
                for (int i = 0; i != 4; i++)
                {
                    if (picks_list[i] > highest_ar && energies[i] <= enemy.GetEnergy() && types_list[i] == ARMOR)
                    {
                        highest_ar = picks_list[i];
                    }
                }
                // Choose highest armor :3
                for (int i = 0; i != 4; i++)
                {
                    if (picks_list[i] == highest_ar && types_list[i] == ARMOR)
                    {
                        return i;
                    }
                }
            }
        }
    }
    else
    {
        uint32_t highest_att = 0;
        // Get highest attack
        for (int i = 0; i != 4; i++)
        {
            if (picks_list[i] > highest_att && energies[i] <= enemy.GetEnergy() && types_list[i] == ATTACK)
            {
                highest_att = picks_list[i];
            }
        }

        if (player.GetHealth() <= (static_cast<int32_t>(highest_att)))
        {
            // Attack!
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == highest_att && types_list[i] == ATTACK)
                {
                    return i;
                }
            }
        }
        else
        {
            // find autoheal and apply
            for (int i = 0; i != 4; i++)
            {
                if (types_list[i] == STATUS && picks_list[i] == AUTO_HEAL && energies[i] <= enemy.GetEnergy())
                {
                    return i;
                }
            }

            // Else find a health move
            uint32_t highest_heal = 0;
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] > highest_heal && types_list[i] == HEAL && energies[i] <= enemy.GetEnergy())
                {
                    highest_heal = picks_list[i];
                }
            }

            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == highest_heal && types_list[i] == HEAL)
                {
                    return i;
                }
            }
        }
    }

    // If we got to this point well uhhhhhh
    // Just pick the first move we have energy for
    for (int i = 0; i != 4; i++)
    {
        if (energies[i] <= enemy.GetEnergy())
        {
            return i;
        }
    }

    // Oh well, skip then.

    return SKIP;
}

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0