// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file energy.cpp
 * \author norbcodes
 * \brief The game's energy system!
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 * \details Each move has an energetical cost. This introduces another layer of<br>
 *          complexity and strategy to the game.
 */

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

/**
 * \brief Calculate energy cost.
 * \details Depending on the move and type of move, the higher the energetical cost can be.<br>
 *          This function calculates the energy cost.
 * \param[in] move Move data.
 * \param[in] type Move type.
 * \return The energetical cost, as a double.
 */
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
                    cost = 25.0;
                    break;
                case INCR_CRIT:
                    cost = 25.0;
                    break;
                case INVIS:
                    cost = 28.0;
                    break;
                case POISON:
                    cost = 30.0;
                    break;
                case THORNS:
                    cost = 28.0;
                    break;
                case WEAKNESS:
                    cost = 40.0;
                    break;
            }
    }
    return cost;
}

/**
 * \brief Prints out a nice looking energy bar for an entity.
 * \param[in] entity A constant entity reference to display it's energy bar.
 */
void PrintEnergyBar(const Entity& entity)
{
    uint32_t columns_count = roundf((entity.GetEnergy() / MAX_ENERGY) * 10);
    std::string columns = "";
    for (uint32_t i = 0; i != columns_count; i++)
    {
        columns += "#";
    }
    fmt::print("{1}[{0} {2}{3}{4:.<10}{0} {1}]{0} ", RESET, DARK_GRAY, BLUE, BOLD, columns);
    fmt::print("{4}E: {1: >5.1f}{3}/{2} {4}{5:.1f}{3}%{0}\n", RESET, entity.GetEnergy(), MAX_ENERGY, WHITE, BLUE, ((entity.GetEnergy() / MAX_ENERGY) * 100));
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get's the current Entity's energy.
 * \return Energy, as a double.
 */
double Entity::GetEnergy() const
{
    return this->energy;
}

/**
 * \brief Give energy to this Entity.
 * \param[in] val The amount of energy to give, as a double.
 */
void Entity::GiveEnergy(double val)
{
    // Give less if weakened
    if (this->StatusActive(WEAKNESS))
    {
        val *= 0.75;  // 75%
    }

    if (this->energy + val >= MAX_ENERGY)
    {
        this->energy = MAX_ENERGY;
        return;
    }
    this->energy += val;
}

/**
 * \brief Take energy from this Entity.
 * \param[in] val The amount of energy to take, as a double.
 */
void Entity::TakeEnergy(double val)
{
    if (this->energy - val <= 0)
    {
        this->energy = 0;
        return;
    }
    this->energy -= val;
}