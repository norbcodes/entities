// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0

/**
 * \file pick_move.cpp
 * \author norbcodes
 * \brief Function that does stuff based on picked move.
 * \copyright entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0
 */

#include <cstdint>
#include <string>
#include <fmt/core.h>

#include "status_constants.hpp"
#include "move_constants.hpp"
#include "entity.hpp"
#include "colors.hpp"
#include "user_settings.hpp"
#include "translation_engine.hpp"
#include "game_string_formatter.hpp"

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
 * \param[in] user_settings User game settings.
 * \param[in] GameTranslation For localized strings.
 */
void PickMove(Entity* ent1, Entity* ent2, uint32_t picked_move, uint32_t* moves, uint32_t* move_types, double* energy_costs, bool enemy_turn, std::string& what_happened, UserSettingsClass& user_settings, const TranslationEngine& GameTranslation)
{
    std::string who = (!enemy_turn) ? fmt::format("{1}{2}{3}{0}", RESET, BLUE, BOLD, user_settings.GetUsername()) : fmt::format("{1}{2}{3}{0}", RESET, RED, BOLD, GameTranslation.GetTranslated("general.enemy"));
    std::string who_other = (enemy_turn) ? fmt::format("{1}{2}{3}{0}", RESET, BLUE, BOLD, user_settings.GetUsername()) : fmt::format("{1}{2}{3}{0}", RESET, RED, BOLD, GameTranslation.GetTranslated("general.enemy"));

    if (move_types[picked_move] == ATTACK)
    {
        EntityAttack(*ent1, *ent2, moves[picked_move], what_happened, enemy_turn, user_settings, GameTranslation);
        ent1->TakeEnergy(energy_costs[picked_move]);
    }
    else if (move_types[picked_move] == HEAL)
    {
        ent1->Heal(moves[picked_move]);
        what_happened += fmt::format("{2} {3}{5} {4}+{1}HP{0}", RESET, moves[picked_move], who, WHITE, PURPLE, GameTranslation.GetTranslated("general.healed"));
        ent1->TakeEnergy(energy_costs[picked_move]);
    }
    else if (move_types[picked_move] == ARMOR)
    {
        ent1->RegenArmor(moves[picked_move]);
        what_happened += fmt::format("{2} {3}{5} {4}+{1}AR{0}", RESET, moves[picked_move], who, WHITE, PURPLE, GameTranslation.GetTranslated("general.regenerated"));
        ent1->TakeEnergy(energy_costs[picked_move]);
    }
    else if (move_types[picked_move] == STATUS)
    {
        switch (moves[picked_move])
        {
            case AUTO_HEAL:
                ent1->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}{0}", RESET, MsgFormatterNoUser(GameTranslation.GetTranslated("game.applied.autoheal")), who);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case INCR_CRIT:
                ent1->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}{0}", RESET, MsgFormatterNoUser(GameTranslation.GetTranslated("game.applied.incr_crit")), who);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case INVIS:
                ent1->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}{0}", RESET, MsgFormatterNoUser(GameTranslation.GetTranslated("game.applied.invis")), who);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case POISON:
                ent2->GiveStatus(moves[picked_move]);
                what_happened += CustomMsgFormatterNoUser(GameTranslation.GetTranslated("game.applied.poison"), fmt::arg("who", who), fmt::arg("who2", who_other));
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case THORNS:
                ent1->GiveStatus(moves[picked_move]);
                what_happened += fmt::format("{2} {1}{0}", RESET, MsgFormatterNoUser(GameTranslation.GetTranslated("game.applied.thorns")), who);
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
            case WEAKNESS:
                ent2->GiveStatus(moves[picked_move]);
                what_happened += CustomMsgFormatterNoUser(GameTranslation.GetTranslated("game.applied.weakness"), fmt::arg("who", who), fmt::arg("who2", who_other));
                ent1->TakeEnergy(energy_costs[picked_move]);
                break;
        }
    }
}

// entities2 © 2025 by norbcodes is licensed under CC BY-NC 4.0