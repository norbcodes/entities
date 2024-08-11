// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/*
Energy!
*/

#include <cstdint>
#include <math.h>
#include <iostream>
#include <iomanip>

#include "constants.hpp"
#include "colors.hpp"
#include "entity.hpp"

double CalcEnergyCost(uint32_t move, uint32_t type)
{
    double cost = 0.0;
    double factor = 0.0;
    switch (type)
    {
        case ATTACK:
            // Get the (rng(8) + 1) portion
            factor = trunc( move / ATTACK_F );
            cost = factor * ATTACK_ENERGY_F;
            break;
        case HEAL:
            // Get the (rng(5) + 1)
            factor = trunc( move / HEAL_F );
            cost = factor * HEAL_ENERGY_F;
            break;
        case ARMOR:
            // Get the (rng(3) + 1)
            factor = trunc( move / ARM_F );
            cost = factor * ARMOR_ENERGY_F;
            break;
        case STATUS:
            switch (move)
            {
                case AUTO_HEAL:
                    cost = 8.0;
                    break;
                case INCR_CRIT:
                    cost = 20.0;
                    break;
                case INVIS:
                    cost = 16.0;
                    break;
                case POISON:
                    cost = 16.0;
                    break;
            }
    }
    return cost;
}

void PrintEnergyBar(const Entity& entity)
{
    // Do some funky shenanigans
    const auto default_precision = std::cout.precision();

    // Print the base
    std::cout << DARK_GRAY("[ ") + WHITE("          ") + DARK_GRAY(" ] ") << std::endl;
    
    // Move cursor up 1 line and to the beginning
    std::cout << "\x1b[1F";
    
    // Move cursor to the right twice
    std::cout << "\x1b[2C";
    
    // Now, print the motherfucking bar
    uint32_t columns = roundf((entity.GetEnergy() / MAX_ENERGY) * 10);
    std::cout << BLUE_IN("");
    for (int i = 0; i != columns; i++)
    {
        std::cout << "#";
    }
    std::cout << BLUE("");
    
    // Move cursor down 1 line and to the beginning, then up and 14 to the right
    std::cout << "\x1b[1E\x1b[1F\x1b[15C";
    
    // The extra data
    std::cout << BLUE(BOLD_IN("E: "));
    if (entity.GetEnergy() < 10)
    {
        std::cout << WHITE_IN("") << " " << std::fixed << std::setprecision(ENERGY_DECIMALS) << entity.GetEnergy() << WHITE("");
    }
    else
    {
        std::cout << WHITE_IN("") << std::fixed << std::setprecision(ENERGY_DECIMALS) << entity.GetEnergy() << WHITE("");
    }
    std::cout << WHITE("/50 ") + DARK_GRAY_IN("") << std::fixed << std::setprecision(ENERGY_DECIMALS) << (entity.GetEnergy() / MAX_ENERGY) * 100 << WHITE("%");
    
    // Restore precision
    std::cout << std::setprecision(default_precision);
    
    // And finally, move down.
    std::cout << "\x1b[1E";
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

double Entity::GetEnergy() const
{
    return this->energy;
}

void Entity::GiveEnergy(double val)
{
    if (this->energy + val >= MAX_ENERGY)
    {
        this->energy = MAX_ENERGY;
        return;
    }
    this->energy += val;
}

void Entity::TakeEnergy(double val)
{
    if (this->energy - val <= 0)
    {
        this->energy = 0;
        return;
    }
    this->energy -= val;
}