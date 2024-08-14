// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/*
Generate the 4 moves to choose from.
*/

#include <cstdint>
#include <iostream>
#include <iomanip>

#include "constants.hpp"
#include "colors.hpp"
#include "rng.hpp"
#include "energy.hpp"

bool MoveExists(uint32_t* moves, uint32_t* move_types, uint32_t val, uint32_t type)
{
    for (int i = 0; i != 4; i++)
    {
        // Basically, if moves[i] == val and move_types[i] == type, then return true
        if (moves[i] == val && move_types[i] == type)
        {
            return true;
        }
    }
    return false;
}

static uint32_t GenAttackMove()
{
    return (ATTACK_F * rng(1, 9));
}

static uint32_t GenHealMove()
{
    return (HEAL_F * rng(1, 6));
}

static uint32_t GenRegenMove()
{
    return (ARM_F * rng(1, 4));
}

static void GenMove(uint32_t& type, uint32_t& move, double& energy)
{
    // Attack?
    if (rng(0, 100) >= 40)
    {
        // Attack.
        type = ATTACK;
        move = GenAttackMove();
        energy = CalcEnergyCost(move, type);
        return;
    }
    else
    {
        // Status?
        if (rng(0, 100) >= 45)
        {
            // Status.
            type = STATUS;
            move = rng(1, STATUS_C);
            energy = CalcEnergyCost(move, type);
            return;
        }
        else
        {
            // Heal or armor?
            if (rng(0, 100) >= 40)
            {
                type = HEAL;
                move = GenHealMove();
                energy = CalcEnergyCost(move, type);
                return;
            }
            else
            {
                type = ARMOR;
                move = GenRegenMove();
                energy = CalcEnergyCost(move, type);
                return;
            }
        }
    }
}

static void PrintMoves(uint32_t* moves, uint32_t* move_types, double* energies)
{
    for (int i = 0; i != 4; i++)
    {
        // Print index
        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("]");
        // Print energy cost
        std::cout << DARK_GRAY(" [") << BLUE_IN(BOLD_IN("")) << std::fixed << std::setprecision(2) << energies[i] << DARK_GRAY("] \t");
        // Print the other
        switch (move_types[i])
        {
            case ATTACK:
                std::cout << RED("Attack!") + WHITE(" Deal ") + PURPLE(std::to_string(moves[i]) ) + WHITE(" damage to opponent.") << std::endl;
                break;
            case HEAL:
                std::cout << GREEN("Heal! ") + WHITE("Gives you ") + PURPLE("+" + std::to_string(moves[i])) + WHITE(" HP") << std::endl;
                break;
            case ARMOR:
                std::cout << BLUE("Regen armor") + WHITE("! Give you ") + PURPLE("+" + std::to_string(moves[i])) + WHITE(" AR") << std::endl;
                break;
            case STATUS:
                switch (moves[i])
                {
                    case AUTO_HEAL:
                        std::cout << WHITE("Apply ") + GREEN("AutoHeal ") + WHITE("status! Gives you ") + PURPLE(std::to_string(AUTO_HEAL_AMOUNT)) + WHITE(" HP when it's your turn") << std::endl;
                        break;
                    case INCR_CRIT:
                        std::cout << WHITE("Apply ") + RED("IncreasedCrit") + WHITE(" status! Increased chance to deal a ") + RED("critical attack") << std::endl;
                        break;
                    case INVIS:
                        std::cout << WHITE("Apply ") + HOT_PINK("Invis ") + WHITE("status! Opponent has a chance to ") + HOT_PINK("miss") << std::endl;
                        break;
                    case POISON:
                        std::cout << WHITE("Give opponent ") + DARK_GREEN("Poison ") + WHITE("status! Deals ") + PURPLE(std::to_string(POISON_AMOUNT)) + WHITE(" poison damage ") << std::endl;
                        break;
                }
                break;
        }
    }
}

void GenerateMoves(uint32_t* moves, uint32_t* move_types, double* energies)
{
    // Yay!
    for (int i = 0; i != 4; i++)
    {
        while (true)
        {
            uint32_t type = 400;
            uint32_t move = 400;
            double energy_cost = 400.0;
            GenMove(type, move, energy_cost);
            // Safety
            if (MoveExists(moves, move_types, move, type))
            {
                continue;
            }
            else
            {
                moves[i] = move;
                move_types[i] = type;
                energies[i] = energy_cost;
                break;
            }
        }
    }
    PrintMoves(moves, move_types, energies);
}