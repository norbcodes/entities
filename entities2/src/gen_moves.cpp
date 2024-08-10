// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/*
Generate the 4 moves to choose from.
*/

#include <cstdint>
#include <iostream>

#include "constants.hpp"
#include "colors.hpp"
#include "rng.hpp"

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
    return (ATTACK_F * (rng(8) + 1));
}

static uint32_t GenHealMove()
{
    return (HEAL_F * (rng(5) + 1));
}

static uint32_t GenRegenMove()
{
    return (ARM_F * (rng(3) + 1));
}

static void GenMove(uint32_t& type, uint32_t& move)
{
    // Attack?
    if (rng(100) >= 40)
    {
        // Attack.
        type = ATTACK;
        move = GenAttackMove();
        return;
    }
    else
    {
        // Status?
        if (rng(100) >= 45)
        {
            // Status.
            type = STATUS;
            move = rng(STATUS_C);
            return;
        }
        else
        {
            // Heal or armor?
            if (rng(100) >= 40)
            {
                type = HEAL;
                move = GenHealMove();
                return;
            }
            else
            {
                type = ARMOR;
                move = GenRegenMove();
                return;
            }
        }
    }
}

static void PrintMoves(uint32_t* moves, uint32_t* move_types)
{
    for (int i = 0; i != 4; i++)
    {
        switch (move_types[i])
        {
            case ATTACK:
                std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + RED("Attack!") + WHITE(" Deal ") + PURPLE(std::to_string(moves[i]) ) + WHITE(" damage to opponent.") << std::endl;
                break;
            case HEAL:
                std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + GREEN("Heal! ") + WHITE("Gives you ") + PURPLE("+" + std::to_string(moves[i])) + WHITE(" HP") << std::endl;
                break;
            case ARMOR:
                std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + BLUE("Regen armor") + WHITE("! Give you ") + PURPLE("+" + std::to_string(moves[i])) + WHITE(" AR") << std::endl;
                break;
            case STATUS:
                switch (moves[i])
                {
                    case AUTO_HEAL:
                        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + GREEN("AutoHeal ") + WHITE("status! Gives you ") + PURPLE(std::to_string(AUTO_HEAL_AMOUNT)) + WHITE(" HP when it's your turn") << std::endl;
                        break;
                    case INCR_CRIT:
                        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + RED("IncreasedCrit") + WHITE(" status! Increased chance to deal a ") + RED("critical attack") << std::endl;
                        break;
                    case INVIS:
                        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Apply ") + HOT_PINK("Invis ") + WHITE("status! Opponent has a chance to ") + HOT_PINK("miss") << std::endl;
                        break;
                    case POISON:
                        std::cout << DARK_GRAY("[") + GOLD(BOLD_IN(std::to_string(i + 1))) + DARK_GRAY("] ") + WHITE("Give opponent ") + DARK_GREEN("Poison ") + WHITE("status! Deals ") + PURPLE(std::to_string(POISON_AMOUNT)) + WHITE(" poison damage ") << std::endl;
                        break;
                }
                break;
        }
    }
}

void GenerateMoves(uint32_t* moves, uint32_t* move_types)
{
    // Yay!
    for (int i = 0; i != 4; i++)
    {
        while (true)
        {
            uint32_t type = 400;
            uint32_t move = 400;
            GenMove(type, move);
            // Safety
            if (MoveExists(moves, move_types, move, type))
            {
                continue;
            }
            else
            {
                moves[i] = move;
                move_types[i] = type;
                break;
            }
        }
    }
    PrintMoves(moves, move_types);
}