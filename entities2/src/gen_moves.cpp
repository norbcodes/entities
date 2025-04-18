// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file gen_moves.cpp
 * \author norbcodes
 * \brief Generates moves... using RNG!
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
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
#include "translation_engine.hpp"
#include "game_string_formatter.hpp"

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

static void PrintMoves(uint32_t* moves, uint32_t* move_types, double* energies, const TranslationEngine& GameTranslation)
{
    for (int i = 0; i != 4; i++)
    {
        // Print index
        // This looks funny lmao
        fmt::print("{2}[{3}{4}{1}{0}{2}]{0} ", RESET, i + 1, DARK_GRAY, GOLD, BOLD);
        // Print energy cost
        fmt::print("{2}[{3}{4}{1: >5.1f}{0}{2}]{0}\t", RESET, energies[i], DARK_GRAY, BLUE, BOLD);
        // Print the other
        switch (move_types[i])
        {
            case ATTACK:
                fmt::print("{0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.attack"), fmt::arg("value", moves[i])));
                break;
            case HEAL:
                fmt::print("{0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.heal"), fmt::arg("value", moves[i])));
                break;
            case ARMOR:
                fmt::print("{0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.regen"), fmt::arg("value", moves[i])));
                break;
            case STATUS:
                switch (moves[i])
                {
                    case AUTO_HEAL:
                        fmt::print("{0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.autoheal"), fmt::arg("value", AUTO_HEAL_AMOUNT)));
                        break;
                    case INCR_CRIT:
                        fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.icrit")));
                        break;
                    case INVIS:
                        fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.invis")));
                        break;
                    case POISON:
                        fmt::print("{0}\n", CustomMsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.poison"), fmt::arg("value", POISON_AMOUNT)));
                        break;
                    case THORNS:
                        fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.thorns")));
                        break;
                    case WEAKNESS:
                        fmt::print("{0}\n", MsgFormatterNoUser(GameTranslation.GetTranslated("game.moves.weakness")));
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
 * \param[in] GameTranslation Game Translation System used when printing moves.
 */
void GenerateMoves(uint32_t* moves, uint32_t* move_types, double* energies, const TranslationEngine& GameTranslation)
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
    PrintMoves(moves, move_types, energies, GameTranslation);
}

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0