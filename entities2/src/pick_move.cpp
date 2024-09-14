// entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file pick_move.cpp
 * \author norbcodes
 * \brief Function that does stuff based on picked move.
 * \copyright entities2 © 2024 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <string>
#include <fmt/core.h>

#include "status_constants.hpp"
#include "move_constants.hpp"
#include "entity.hpp"
#include "colors.hpp"

/**
 * \brief When you pick a move, this function carries out the move.
 * \param[in] ent1 The Entity that picked the move.
 * \param[in] ent2 The other Entity.
 * \param[in] picked_move The picked move.
 * \param[in] moves Array of moves.
 * \param[in] move_types Array of move types.
 * \param[in] energy_costs Array of energy costs of each move.
 * \param[in] enemy_turn True = Enemy's turn, False = Player's turn
 * \param[out] what_happened The "What happened:" text, which is why it's string&,<br>
 *                           because we write into it.
 */
void PickMove(Entity* ent1, Entity* ent2, uint32_t picked_move, uint32_t* moves, uint32_t* move_types, double* energy_costs, bool enemy_turn, std::string& what_happened)
{
    std::string who = (!enemy_turn) ? fmt::format("{1}{2}Player{0}", RESET, BLUE, BOLD) : fmt::format("{1}{2}Enemy{0}", RESET, RED, BOLD);
    std::string who_other = (enemy_turn) ? fmt::format("{1}{2}Player{0}", RESET, BLUE, BOLD) : fmt::format("{1}{2}Enemy{0}", RESET, RED, BOLD);

    if (move_types[picked_move] == ATTACK)
    {
        EntityAttack(*ent1, *ent2, moves[picked_move], what_happened, enemy_turn);
        ent1->TakeEnergy(energy_costs[picked_move]);
    }
    else if (move_types[picked_move] == HEAL)
    {
        ent1->Heal(moves[picked_move]);
        what_happened += fmt::format("{2} {3}healed {4}+{1}HP{0}", RESET, moves[picked_move], who, WHITE, PURPLE);
        ent1->TakeEnergy(energy_costs[picked_move]);
    }
    else if (move_types[picked_move] == ARMOR)
    {
        ent1->RegenArmor(moves[picked_move]);
        what_happened += fmt::format("{2} {3}regen'd {4}+{1}AR{0}", RESET, moves[picked_move], who, WHITE, PURPLE);
        ent1->TakeEnergy(energy_costs[picked_move]);
    }
    else if (move_types[picked_move] == STATUS)
    {
        switch (moves[picked_move])
        {
            case AUTO_HEAL:
                ent1->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}has applied {3}Autoheal{1}.{0}", RESET, WHITE, who, GREEN);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case INCR_CRIT:
                ent1->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}has applied {3}IncreasedCrit{1}.{0}", RESET, WHITE, who, RED);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case INVIS:
                ent1->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}has applied {3}Invis{1}.{0}", RESET, WHITE, who, HOT_PINK);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case POISON:
                ent2->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}has given {4}Poison{1} to {3}{1}.{0}", RESET, WHITE, who, who_other, DARK_GREEN);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case THORNS:
                ent1->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}has applied {3}Thorns{1}.{0}", RESET, WHITE, who, TEAL);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case WEAKNESS:
                ent2->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}has given {4}Weakness{1} to {3}{1}.{0}", RESET, WHITE, who, who_other, BROWN);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
        }
    }
}