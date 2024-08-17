// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/*
Energy!
*/

#include <cstdint>
#include <math.h>
#include <fmt/core.h>

#include "energy_constants.hpp"
#include "move_constants.hpp"
#include "status_constants.hpp"
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
                case THORNS:
                    cost = 15.0;
                    break;
            }
    }
    return cost;
}

void PrintEnergyBar(const Entity& entity)
{
    uint32_t columns_count = roundf((entity.GetEnergy() / MAX_ENERGY) * 10);
    std::string columns = "";
    for (int i = 0; i != columns_count; i++)
    {
        columns += "#";
    }
    fmt::print("{1}[{0} {2}{3}{4:.<10}{0} {1}]{0} ", RESET, DARK_GRAY, BLUE, BOLD, columns);
    fmt::print("{4}E: {1: >5.2f}{3}/{2} {4}{5:.1f}{3}%{0}\n", RESET, entity.GetEnergy(), MAX_ENERGY, WHITE, BLUE, ((entity.GetEnergy() / MAX_ENERGY) * 100));
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