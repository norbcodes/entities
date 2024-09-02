// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file gen_moves.cpp
 * \author norbcodes
 * \brief Generates moves... using RNG!
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

/*
Generate the 4 moves to choose from.
*/

#include <cstdint>
#include <fmt/core.h>

#include "move_constants.hpp"
#include "status_constants.hpp"
#include "colors.hpp"
#include "rng.hpp"
#include "energy.hpp"

/**
 * \brief Checks if a move exists in the moves lists.
 * \param[in] moves Array of moves.
 * \param[in] move_types Array of types of each move.
 * \param[in] val The move data, checked against <i>moves</i> array.
 * \param[in] type The move type, checked against <i>move_types</i> array.
 * \return True if move exists, else False.
 */
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
            move = rng(0, STATUS_C - 1);
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
        // This looks funny lmao
        fmt::print("{2}[{3}{4}{1}{0}{2}]{0} ", RESET, i + 1, DARK_GRAY, GOLD, BOLD);
        // Print energy cost
        fmt::print("{2}[{3}{4}{1: >5.2f}{0}{2}]{0}\t", RESET, energies[i], DARK_GRAY, BLUE, BOLD);
        // Print the other
        switch (move_types[i])
        {
            case ATTACK:
                fmt::print("{3}Attack! {2}Deal {4}{1} {2}damage to opponent.{0}\n", RESET, moves[i], WHITE, RED, PURPLE);
                break;
            case HEAL:
                fmt::print("{2}Heal! {3}Gives you {4}+{1} {3}HP{0}\n", RESET, moves[i], GREEN, WHITE, PURPLE);
                break;
            case ARMOR:
                fmt::print("{2}Regen armor{3}! Gives you {4}+{1} {3}AR{0}\n", RESET, moves[i], BLUE, WHITE, PURPLE);
                break;
            case STATUS:
                switch (moves[i])
                {
                    case AUTO_HEAL:
                        fmt::print("{2}Apply {3}AutoHeal {2}status! Gives you {4}{1} {2}HP when it's your turn{0}\n", RESET, AUTO_HEAL_AMOUNT, WHITE, GREEN, PURPLE);
                        break;
                    case INCR_CRIT:
                        fmt::print("{1}Apply {2}IncreasedCrit {1}status! Increased {2}critical attack chance{0}\n", RESET, WHITE, RED);
                        break;
                    case INVIS:
                        fmt::print("{1}Apply {2}Invis {1}status! Opponent has a chance to {2}miss{0}\n", RESET, WHITE, HOT_PINK);
                        break;
                    case POISON:
                        fmt::print("{2}Give opponent {3}Poison {2}status! Deals {4}{1} {2}poison damage{0}\n", RESET, POISON_AMOUNT, WHITE, DARK_GREEN, PURPLE);
                        break;
                    case THORNS:
                        fmt::print("{2}Apply {1}Thorns {2}status! Opponent will {3}take damage too on attack{0}\n", RESET, TEAL, WHITE, BOLD);
                        break;
                }
                break;
        }
    }
}

/**
 * \brief Generate moves list.
 * \param[out] moves Array of moves.
 * \param[out] move_types Array of types of each move.
 * \param[out] energies Array of energy costs of each move.
 */
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