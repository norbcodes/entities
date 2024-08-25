// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <cstdint>

#include "move_constants.hpp"
#include "status_constants.hpp"
#include "entity.hpp"
#include "utils.hpp"
#include "rng.hpp"

#define SKIP 4

uint32_t AiChoose(uint32_t* picks_list, uint32_t* types_list, double* energies, const Entity& player, const Entity& enemy, uint32_t difficulty_scale)
{
    // The ai
    // I copy+pasted a lot of this shit

    // First, check if we can actually get any moves
    bool available[4] = {false, false, false, false};
    uint32_t _sum = 0;
    for (int i = 0; i != 4; i++)
    {
        if (energies[i] <= enemy.GetEnergy())
        {
            available[i] = true;
            _sum += 1;
        }
    }

    // all falses
    if (_sum == 0)
    {
        return SKIP;
    }

    if (rng(0, 100) > enemy.GetHealth())
    {
        /*
        Difficulty table:
        EASY               60
        MEDIUM             70
        HARD               60
        */
        if (rng(0, 100) > (60 - (difficulty_scale * 5)))
        {
            // Prioritize choosing poison
            bool poison_available = false;
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == POISON && energies[i] <= enemy.GetEnergy() && types_list[i] == STATUS)
                {
                    poison_available = true;
                }
            }

            if (poison_available)
            {
                for (int i = 0; i != 4; i++)
                {
                    if (picks_list[i] == POISON && types_list[i] == STATUS)
                    {
                        return i;
                    }
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

        if (player.GetHealth() <= highest_att)
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
            bool autoheal_available = false;
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
    return SKIP;
}