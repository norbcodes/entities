// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

#include <cstdint>

#include "constants.hpp"
#include "entity.hpp"
#include "utils.hpp"
#include "rng.hpp"

uint32_t AiChoose(uint32_t* picks_list, uint32_t* types_list, double* energies, const Entity& player, const Entity& enemy)
{
    // Basically, heal if health < 40 if posslbe
    // Attack if health > 80 if possible
    // Cast poison (50% chance) if possible
    // (middle zone 40 < health < 80, choose a random status if possible)
    // If armor < 50, take RegenArmor if possible

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
        return 5;
    }

    // Can we armor?
    
    if (enemy.GetArmor() <= 50)
    {
        uint32_t max_armor_amount = 0;
        for (int i = 0; i != 4; i++)
        {
            // Is of type armor
            if (types_list[i] == ARMOR && available[i])
            {
                // Get the highest armor amount
                if (picks_list[i] > max_armor_amount)
                {
                    max_armor_amount = picks_list[i];
                }
            }
        }
        // If max_armor_amount is not 0
        if (max_armor_amount != 0)
        {
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == max_armor_amount)
                {
                    return i;
                }
            }
        } // else just continue.
    }

    // Can we heal?
    if (enemy.GetHealth() <= 40)
    {
        uint32_t max_heal_amount = 0;
        for (int i = 0; i != 4; i++)
        {
            // Is of type heal
            if (types_list[i] == HEAL && available[i])
            {
                // Get the highest heal amount
                if (picks_list[i] > max_heal_amount)
                {
                    max_heal_amount = picks_list[i];
                }
            }
        }
        // If max_heal_amount is not 0
        if (max_heal_amount != 0)
        {
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == max_heal_amount)
                {
                    return i;
                }
            }
        } // else just continue.
    }

    // Cast poison if possible
    for (int i = 0; i != 4; i++)
    {
        if (picks_list[i] == POISON && types_list[i] == STATUS && available[i])
        {
            if (rng(0, 100) >= 50)
            {
                return i;
            }
        } 
    }

    // Attack
    if (enemy.GetHealth() >= 80)
    {
        uint32_t max_dmg_amount = 0;
        for (int i = 0; i != 4; i++)
        {
            // Is of type heal
            if (types_list[i] == ATTACK && available[i])
            {
                // Get the highest heal amount
                if (picks_list[i] > max_dmg_amount)
                {
                    max_dmg_amount = picks_list[i];
                }
            }
        }
        // If max_dmg_amount is not 0
        if (max_dmg_amount != 0)
        {
            for (int i = 0; i != 4; i++)
            {
                if (picks_list[i] == max_dmg_amount)
                {
                    return i;
                }
            }
        } // else just continue.
    }

    // Choose a status
    if (40 < enemy.GetHealth() && enemy.GetHealth() < 80)
    {
        uint32_t count = 0;
        for (int i = 0; i != 4; i++)
        {
            if (types_list[i] == STATUS && available[i])
            {
                count++;
            }
        }
        uint32_t pick = rng(0, count);
        uint32_t index = 0;
        // The loop of doom
        while (pick != 0)
        {
            if (picks_list[index] == STATUS)
            {
                pick--;
            }
            if (pick == 0)
            {
                return index;
            }
            if (index == 3)
            {
                return index;
            }
            index++;
        }
    }

    // If literally nothing get picked
    return 5;
}